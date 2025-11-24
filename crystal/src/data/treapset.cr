require "data/xorshift.cr"
class TreapSet(T)
  macro nnl(x)
    {{x}}.not_nil!
  end
  class Node(T)
    property l : Node(T)?
    property r : Node(T)?
    property key : T
    property pri : UInt32
    property size : Int32
    property prod : T
    def initialize(@key : T, @pri : UInt32)
      @l = @r = nil
      @size = 1
      @prod = @key
    end
    def self.clone(t : Node(T)) : Node(T)
      n=Node(T).new t.key, t.pri
      n.size = t.size
      n.prod = t.prod
      n
    end
    def self.clone_tree(t : Node(T)?) : Node(T)?
      return nil if !t
      t = t.not_nil!
      n = clone t
      n.l = clone_tree t.l
      n.r = clone_tree t.r
      n
    end
  end
  struct Iterator(T)
    property treap : TreapSet(T)
    property root : Node(T)?
    property node : Node(T)?
    property idx : Int32
    def initialize(@treap : TreapSet(T), @root : Node(T)?, @node : Node(T)?, @idx : Int32);end
    def v;@node.try(&.key).not_nil!;end
    def +(n : Int32)
      k = @idx + n
      Iterator(T).new @treap, @root, @treap.kth(@root, k), k
    end
    def -(n : Int32);self + (-n);end
    def -(b : Iterator(T));@idx - b.@idx;end
    include Comparable(Iterator(T))
    def <=>(other : Iterator(T));@idx <=> other.@idx;end
  end
  def head;Iterator(T).new self, @root, kth(@root, 0), 0;end
  def tail;Iterator(T).new self, @root, nil, size;end
  property root : Node(T)?
  property f : Proc(T, T, T)
  def initialize(@f : Proc(T, T, T));@root = nil;@rnd = Xorshift32.new(Random.rand(1u32..UInt32::MAX));end
  def initialize;@f = ->(a : T, b : T){ a }; @root = nil;@rnd = Xorshift32.new(Random.rand(1u32..UInt32::MAX));end
  def size;sz @root;end
  def empty?;!@root ? true : false;end
  def clear;@root = nil;end
  def clone
    t = TreapSet.new(@f)
    t.root = Node.clone_tree @root
    t
  end
  def insert(x : T)
    node = Node(T).new x, @rnd.urandom
    @root, res = insert @root, node
    res
  end
  def <<(x : T);insert x;end
  def erase(x : T) : Bool;@root, res = erase @root, x;res;end
  def toggle(x : T) : Bool;erase(x) ? false : insert(x);end
  def pop(k : Int32 = -1) : T
    k += size if k < 0
    @root, v = erase_by_rank @root, k
    v
  end
  def [](k : Int32) : T
    k += size if k < 0
    nnl(kth(@root, k).try(&.key))
  end
  def count(x : T) : Bool;find x;end
  def find(x : T) : Bool
    t = @root
    return false if !t
    while t
      if x == t.try &.key
        return true
      elsif x < t.try &.key
        t = t.try &.l
      else
        t = t.try &.r
      end
    end
    false
  end
  macro index_def(name, cmp)
    def {{name}}(t : Node(T)?, x : T) : Int32
      return 0 if !t
      if x {{cmp.id}} t.try &.key
        {{name}} t.try(&.l), x
      else
        1 + sz(t.try(&.l)) + {{name}} t.try(&.r), x
      end
    end
  end
  macro bound_def(cmp)
    t = @root
    idx = 0
    best = nil
    best_idx = 0
    while t
      if x {{cmp.id}} t.try &.key
        best = t
        best_idx = idx + sz t.try &.l
        t = t.l
      else
        idx += 1 + sz t.try &.l
        t = t.r
      end
    end
    if !best
      tail
    else
      Iterator(T).new self, @root, best, best_idx
    end
  end
  index_def index, :<=
  index_def index_rg, :<
  def lower_bound(x : T);bound_def :<=;end
  def upper_bound(x : T);bound_def :<;end
  def [](l : Int32, r : Int32) : T?
    return nil if l >= r || !@root
    a, mr = split_by_index @root, l
    m, b = split_by_index mr, r - l
    res = m ? m.prod : nil
    @root = merge a, merge m, b
    res
  end
  def split(x : T) : {TreapSet(T), TreapSet(T)}
    a, b = split @root, x
    l = TreapSet.new @f
    r = TreapSet.new @f
    l.root = a
    r.root = b
    {l, r}
  end
  def splitl(x : T) : {TreapSet(T), TreapSet(T)}
    a, b = splitl @root, x
    l = TreapSet.new @f
    r = TreapSet.new @f
    l.root = a
    r.root = b
    {l, r}
  end
  def spliti(k : T) : {TreapSet(T), TreapSet(T)}
    a, b = split_by_index @root, k
    l = TreapSet.new @f
    r = TreapSet.new @f
    l.root = a
    r.root = b
    {l, r}
  end
  def to_a : Array(T)
    Array(T).build(size) do |pt|
      fill_inorder @root, pt, 0
      size
    end
  end
  private def fill_inorder(t : Node(T)?, arr : Pointer(T), i : Int32)
    return i if !t
    t = t.not_nil!
    j = fill_inorder t.l, arr, i
    arr[j] = t.key
    fill_inorder t.r, arr, (j + 1)
  end
  protected def kth(t : Node(T)?, k : Int32) : Node(T)?
    return nil if !t
    ls = sz t.try &.l
    if k < ls
      kth t.try(&.l), k
    elsif k == ls
      t
    else
      kth t.try(&.r), k - ls - 1
    end
  end
  private def sz(t : Node(T)?) : Int32;!t ? 0 : t.try(&.size);end
  private def update(t : Node(T)?) : Node(T)?
    nnl(t).size = 1 + sz(t.try(&.l)) + sz t.try &.r
    ls = t.try(&.l) ? t.try(&.l).try(&.prod) : nil
    rs = t.try(&.r) ? t.try(&.r).try(&.prod) : nil
    nnl(t).prod = if ls && rs
                    @f.call(@f.call(nnl(ls), nnl(t.try(&.key))), nnl(rs))
                  elsif ls
                    @f.call(nnl(ls), nnl(t.try(&.key)))
                  elsif rs
                    @f.call(nnl(t.try(&.key)), nnl(rs))
                  else
                    nnl t.try &.key
                  end
    t
  end
  private def merge(a : Node(T)?, b : Node(T)?) : Node(T)?
    return !a ? b : a if !a || !b
    if a.try(&.pri) > b.try(&.pri)
      nnl(a).r = merge a.try(&.r), b
      update a
    else
      nnl(b).l = merge a, b.try &.l
      update b
    end
  end
  private def split(t : Node(T)?, x : T) : {Node(T)?, Node(T)?} # [<x],[x<=]
    return {nil, nil} if !t
    if x <= t.try &.key
      l, nnl(t).l = split t.try(&.l), x
      {l, update(t)}
    else
      nnl(t).r, r = split t.try(&.r), x
      {update(t), r}
    end
  end
  private def splitl(t : Node(T)?, x : T) : {Node(T)?, Node(T)?} # [<=x],[x<]
    return {nil, nil} if !t
    if x < t.try &.key
      l, nnl(t).l = splitl t.try(&.l), x
      {l, update(t)}
    else
      nnl(t).r, r = splitl t.try(&.r), x
      {update(t), r}
    end
  end
  private def split_by_index(t : Node(T)?, k : Int32) : {Node(T)?, Node(T)?} # [...k],[k..]
    return {nil, nil} if !t
    if k <= sz t.try &.l
      l, nnl(t).l = split_by_index t.try(&.l), k
      {l, update(t)}
    else
      nnl(t).r, r = split_by_index t.try(&.r), k - sz(t.try(&.l)) - 1
      {update(t), r}
    end
  end
  private def insert(t : Node(T)?, node : Node(T)) : {Node(T)?, Bool}
    return {node, true} if !t
    if node.key == t.try &.key
      {t, false}
    elsif node.pri > t.try &.pri
      node.l, node.r = split t, node.key
      {update(node),true}
    elsif node.key < t.try &.key
      nnl(t).l, res = insert t.try(&.l), node
      {update(t),res}
    else
      nnl(t).r, res = insert t.try(&.r), node
      {update(t),res}
    end
  end
  private def erase(t : Node(T)?, x : T) : {Node(T)?, Bool}
    return {nil, false} if !t
    if x == t.try &.key
      {merge(t.try(&.l), t.try(&.r)), true}
    elsif x < t.try &.key
      nnl(t).l, res = erase t.try(&.l), x
      {update(t), res}
    else
      nnl(t).r, res = erase t.try(&.r), x
      {update(t), res}
    end
  end
  # コンテナが空でないことを前提とする
  private def erase_by_rank(t : Node(T)?, k : Int32) : {Node(T)?, T}
    ls = sz t.try &.l
    if k < ls
      nnl(t).l, val = erase_by_rank(t.try(&.l), k)
      {update(t), val}
    elsif k == ls
      val = nnl t.try &.key
      {merge(t.try(&.l), t.try(&.r)), val}
    else
      nnl(t).r, val = erase_by_rank(t.try(&.r), k - ls - 1)
      {update(t), val}
    end
  end
end

