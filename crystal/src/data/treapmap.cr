require "data/xorshift.cr"
class Map(K, V)
  macro nnl(x)
    {{x}}.not_nil!
  end
  class Node(K, V)
    property l : Node(K, V)?
    property r : Node(K, V)?
    property key : K
    property pri : UInt32
    property size : Int32
    property prod : K
    property val : V
    def initialize(@key : K, @pri : UInt32, @val : V)
      @l = @r = nil
      @size = 1
      @prod = @key
    end
    def self.clone(t : Node(K, V)) : Node(K, V)
      n=Node(K, V).new t.key, t.pri, t.val
      n.size = t.size
      n.prod = t.prod
      n
    end
    def self.clone_tree(t : Node(K, V)?) : Node(K, V)?
      return nil if !t
      t = t.not_nil!
      n = clone t
      n.l = clone_tree t.l
      n.r = clone_tree t.r
      n
    end
  end
  struct Iterator(K, V)
    property map : Map(K, V)
    property root : Node(K, V)?
    property node : Node(K, V)?
    property idx : Int32
    def initialize(@map : Map(K, V), @root : Node(K, V)?, @node : Node(K, V)?, @idx : Int32);end
    def v;{@node.try(&.key).not_nil!, @node.try(&.val).not_nil!};end
    def +(n : Int32)
      k = @idx + n
      Iterator(K, V).new @map, @root, @map.kth(@root, k), k
    end
    def -(n : Int32);self + (-n);end
    def -(b : Iterator(K, V));@idx - b.@idx;end
    include Comparable(Iterator(K, V))
    def <=>(other : Iterator(K, V));@idx <=> other.@idx;end
  end
  def head;Iterator(K, V).new self, @root, kth(@root, 0), 0;end
  def tail;Iterator(K, V).new self, @root, nil, size;end
  property root : Node(K, V)?
  property f : Proc(V)
  def initialize(@f : Proc(V));@root = nil;@rnd = Xorshift32.new(Random.rand(1u32..UInt32::MAX));end
  def size;sz @root;end
  def empty?;!@root ? true : false;end
  def clear;@root = nil;end
  def clone
    t = Map(K, V).new @f
    t.root = Node.clone_tree @root
    t
  end
  def [](key : K) : V
    t = @root
    while t
      if key == t.try &.key
        return nnl(nnl(t).val)
      elsif key < t.try &.key
        t = t.try &.l
      else
        t = t.try &.r
      end
    end
    val = @f.call
    node = Node(K, V).new key, @rnd.urandom, val
    @root, _ = insert @root, node
    val
  end
  def []=(key : K, val : V)
    t = @root
    node = Node(K, V).new key, @rnd.urandom, val
    @root, res = set @root, node
    res.val = val if res.val != val
    val
  end
  def erase(key : K) : Nil
    @root, _ = erase @root, key
  end
  def count(x : K) : Bool;find x;end
  def find(x : K) : Bool
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
      Iterator(K, V).new self, @root, best, best_idx
    end
  end
  def lower_bound(x : K);bound_def :<=;end
  def upper_bound(x : K);bound_def :<;end
  def split(x : K) : {Map(K, V), Map(K, V)}
    a, b = split @root, x
    l = Map(K, V).new @f
    r = Map(K, V).new @f
    l.root = a
    r.root = b
    {l, r}
  end
  def splitl(x : K) : {Map(K,V), Map(K,V)}
    a, b = splitl @root, x
    l = Map(K, V).new @f
    r = Map(K, V).new @f
    l.root = a
    r.root = b
    {l, r}
  end
  def spliti(k : Int32) : {Map(K, V), Map(K, V)}
    a, b = split_by_index @root, k
    l = Map(K, V).new @f
    r = Map(K, V).new @f
    l.root = a
    r.root = b
    {l, r}
  end
  def to_a : Array({K, V})
    Array({K, V}).build(size) do |pt|
      fill_inorder @root, pt, 0
      size
    end
  end
  def keys;to_a.map(&.[0]);end
  def values;to_a.map(&.[1]);end
  private def fill_inorder(t : Node(K, V)?, arr : Pointer({K, V}), i : Int32)
    return i if !t
    t = t.not_nil!
    j = fill_inorder t.l, arr, i
    arr[j] = {t.key, t.val}
    fill_inorder t.r, arr, (j + 1)
  end
  protected def kth(t : Node(K, V)?, k : Int32) : Node(K, V)?
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
  private def sz(t : Node(K, V)?) : Int32;!t ? 0 : t.try(&.size);end
  private def update(t : Node(K, V)?) : Node(K, V)?
    nnl(t).size = 1 + sz(t.try(&.l)) + sz t.try &.r
    t
  end
  private def merge(a : Node(K, V)?, b : Node(K, V)?) : Node(K, V)?
    return !a ? b : a if !a || !b
    if a.try(&.pri) > b.try(&.pri)
      nnl(a).r = merge a.try(&.r), b
      update a
    else
      nnl(b).l = merge a, b.try &.l
      update b
    end
  end
  private def split(t : Node(K, V)?, x : K) : {Node(K, V)?, Node(K, V)?} # [<x],[x<=]
    return {nil, nil} if !t
    if x <= t.try &.key
      l, nnl(t).l = split t.try(&.l), x
      {l, update(t)}
    else
      nnl(t).r, r = split t.try(&.r), x
      {update(t), r}
    end
  end
  private def splitl(t : Node(K, V)?, x : K) : {Node(K, V)?, Node(K, V)?} # [<=x],[x<]
    return {nil, nil} if !t
    if x < t.try &.key
      l, nnl(t).l = splitl t.try(&.l), x
      {l, update(t)}
    else
      nnl(t).r, r = splitl t.try(&.r), x
      {update(t), r}
    end
  end
  private def split_by_index(t : Node(K, V)?, k : Int32) : {Node(K, V)?, Node(K, V)?} # [...k],[k..]
    return {nil, nil} if !t
    if k <= sz t.try &.l
      l, nnl(t).l = split_by_index t.try(&.l), k
      {l, update(t)}
    else
      nnl(t).r, r = split_by_index t.try(&.r), k - sz(t.try(&.l)) - 1
      {update(t), r}
    end
  end
  private def insert(t : Node(K, V)?, node : Node(K, V)) : {Node(K, V)?, Bool}
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
  private def set(t : Node(K, V)?, node : Node(K, V)) : {Node(K, V)?, Node(K, V)}
    return {node, node} if !t
    if node.key == t.try &.key
      {t, nnl(t)}
    elsif node.pri > t.try &.pri
      node.l, node.r = split t, node.key
      {update(node),node}
    elsif node.key < t.try &.key
      nnl(t).l, res = set t.try(&.l), node
      {update(t),res}
    else
      nnl(t).r, res = set t.try(&.r), node
      {update(t),res}
    end
  end
  private def erase(t : Node(K, V)?, x : K) : {Node(K, V)?, Bool}
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
  private def erase_by_rank(t : Node(K, V)?, k : Int32) : {Node(K, V)?, K}
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

