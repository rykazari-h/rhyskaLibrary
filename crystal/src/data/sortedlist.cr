class Sortedlist(T)
  include Enumerable(T)
  include Iterable(T)
  getter size
  BOUND = 20
  def self.from_sorted(z : Array(T)) : Sortedlist(T)
    sz = z.size
    return Sortedlist(T).new if sz == 0
    s = Math.sqrt(sz.to_f / 8).ceil.to_i
    list = Array(Array(T)).new(s) { [] of T }
    s.times { |i| list[i] = z[(sz * i // s)...(sz * (i + 1) // s)] }
    Sortedlist(T).new(sz, list)
  end
  def initialize; @size = 0; @list = [] of Array(T); end
  def initialize(@size : Int32, @list : Array(Array(T))); end
  def initialize(p : Array(T))
    z = p.unstable_sort
    @size = z.size
    s = Math.sqrt(@size.to_f / 8).ceil.to_i
    @list = Array(Array(T)).new(s) { [] of T }
    s.times { |i| @list[i] = z[(@size * i // s)...(@size * (i + 1) // s)] }
  end
  def empty?; @size == 0; end
  def clear : Nil; @size = 0; @list.clear; end
  def dup : Sortedlist(T); Sortedlist(T).new(@size, @list.map &.dup); end
  def clone : Sortedlist(T); Sortedlist(T).new(@size, @list.clone); end
  def |(other : Sortedlist(T)) : Sortedlist(T)
    a, b = self.to_a, other.to_a
    res = Array(T).new(a.size + b.size)
    i = j = 0
    while i < a.size && j < b.size
      if a[i] < b[j]
        res << a[i]; i += 1
      elsif a[i] > b[j]
        res << b[j]; j += 1
      else
        res << a[i]; i += 1; j += 1
      end
    end
    while i < a.size; res << a[i]; i += 1; end
    while j < b.size; res << b[j]; j += 1; end
    Sortedlist(T).from_sorted(res)
  end
  def +(other : Sortedlist(T)) : Sortedlist(T); self | other; end
  def &(other : Sortedlist(T)) : Sortedlist(T)
    a, b = self.to_a, other.to_a
    res = [] of T
    i = j = 0
    while i < a.size && j < b.size
      if a[i] < b[j]
        i += 1
      elsif a[i] > b[j]
        j += 1
      else
        res << a[i]; i += 1; j += 1
      end
    end
    Sortedlist(T).from_sorted(res)
  end
  def -(other : Sortedlist(T)) : Sortedlist(T)
    a, b = self.to_a, other.to_a
    res = [] of T
    i = j = 0
    while i < a.size && j < b.size
      if a[i] < b[j]
        res << a[i]; i += 1
      elsif a[i] > b[j]
        j += 1
      else
        i += 1; j += 1
      end
    end
    while i < a.size; res << a[i]; i += 1; end
    Sortedlist(T).from_sorted(res)
  end
  def ^(other : Sortedlist(T)) : Sortedlist(T)
    a, b = self.to_a, other.to_a
    res = Array(T).new(a.size + b.size)
    i = j = 0
    while i < a.size && j < b.size
      if a[i] < b[j]
        res << a[i]; i += 1
      elsif a[i] > b[j]
        res << b[j]; j += 1
      else
        i += 1; j += 1
      end
    end
    while i < a.size; res << a[i]; i += 1; end
    while j < b.size; res << b[j]; j += 1; end
    Sortedlist(T).from_sorted(res)
  end
  def ==(other : Sortedlist(T)) : Bool; @size == other.size && @list == other.data; end
  def _position(x : T) : {Int32, Int32}
    sz = @list.size
    sz.times do |i|
      z = @list.unsafe_fetch(i)
      return {i, bsearch_lower(z, x)} if x <= z.unsafe_fetch(z.size - 1)
    end
    {sz - 1, @list.unsafe_fetch(sz - 1).size}
  end
  def _pop(bi, i) : T
    z = @list.unsafe_fetch(bi)
    v = z.unsafe_fetch(i)
    z.delete_at(i)
    @size -= 1
    @list.delete_at(bi) if z.empty?
    v
  end
  def <<(x : T) : self; insert(x); self; end
  def add(x : T) : self; insert(x); self; end
  def insert(x : T) : Nil
    (@list = [[x]]; @size = 1; return) if empty?
    bi, i = _position(x)
    z = @list.unsafe_fetch(bi)
    z.insert(i, x)
    @size += 1
    return if z.size <= @list.size*BOUND
    mid = z.size >> 1
    len = z.size - mid
    nb = z[mid, len]
    z.delete_at(mid, len)
    @list.insert(bi + 1, nb)
  end
  def delete(x) : T?; erase(x); end
  def erase(x : T) : T?
    return nil if empty?
    bi, i = _position(x)
    return nil if i == @list.unsafe_fetch(bi).size || @list.unsafe_fetch(bi).unsafe_fetch(i) != x
    _pop(bi, i)
    x
  end
  def erase(it : SetIterator(T)) : T?
    bi, i = it.pos
    return nil if bi == @list.size
    res = @list.unsafe_fetch(bi).unsafe_fetch(i)
    _pop(bi, i)
    res
  end
  def erase_all(x : T) : Nil
    return if empty?
    bi, i = _position(x)
    return if i == @list.unsafe_fetch(bi).size || @list.unsafe_fetch(bi).unsafe_fetch(i) != x
    loop do
      @size -= @list.unsafe_fetch(bi).count(x)
      @list.unsafe_fetch(bi).delete(x)
      if @list.unsafe_fetch(bi).empty?
        @list.delete_at(bi)
      else
        bi += 1
      end
      break if bi == @list.size || @list.unsafe_fetch(bi).unsafe_fetch(0) != x
    end
    return
  end
  def pop(i : Int = -1) : T
    if i >= 0
      @list.size.times do |b|
        return _pop(b, i) if i < @list.unsafe_fetch(b).size
        i -= @list.unsafe_fetch(b).size
      end
    else
      (@list.size - 1).downto(0) do |b|
        i += @list.unsafe_fetch(b).size
        return _pop(b, i) if i >= 0
      end
    end
    raise IndexError.new
  end
  def ===(x : T) : Bool; includes?(x); end
  def includes?(x : T) : Bool
    return false if empty?
    bi, i = _position(x)
    i != @list[bi].size && @list[bi][i] == x
  end
  def [](i : Int) : T
    if i >= 0
      @list.size.times do |b|
        return @list.unsafe_fetch(b).unsafe_fetch(i) if i < @list.unsafe_fetch(b).size
        i -= @list.unsafe_fetch(b).size
      end
    else
      (@list.size - 1).downto(0) do |b|
        i += @list.unsafe_fetch(b).size
        return @list.unsafe_fetch(b).unsafe_fetch(i) if i >= 0
      end
    end
    raise IndexError.new
  end
  def []=(i : Int, x : T) : T
    if i >= 0
      @list.size.times do |b|
        return @list.unsafe_fetch(b).unsafe_put(i, x) if i < @list.unsafe_fetch(b).size
        i -= @list.unsafe_fetch(b).size
      end
    else
      (@list.size - 1).downto(0) do |b|
        i += @list.unsafe_fetch(b).size
        return @list.unsafe_fetch(b).unsafe_put(i, x) if i >= 0
      end
    end
    raise IndexError.new
  end
  def each : SetIterator(T); head; end
  def each(& : T ->) : Nil
    @list.size.times do |i|
      z = @list.unsafe_fetch(i)
      z.size.times do |j|
        yield z.unsafe_fetch(j)
      end
    end
  end

  def data : Array(Array(T)); @list; end
  def to_a : Array(T); @list.flatten; end
  def lower_bound(x : T) : SetIterator(T)
    @list.size.times do |i|
      z = @list[i]
      return SetIterator(T).new(i, bsearch_lower(z, x), @list) if !z.empty? && z.unsafe_fetch(z.size - 1) >= x
    end
    tail
  end
  def upper_bound(x : T) : SetIterator(T)
    @list.size.times do |i|
      z = @list[i]
      return SetIterator(T).new(i, bsearch_upper(z, x), @list) if !z.empty? && z.unsafe_fetch(z.size - 1) > x
    end
    tail
  end
  def index(x : T) : Int32
    res = 0
    @list.each { |z| return res + bsearch_lower(z, x) if z.unsafe_fetch(z.size - 1) >= x; res += z.size }
    res
  end
  def index_rg(x : T) : Int32
    res = 0
    @list.each { |z| return res + bsearch_upper(z, x) if z.unsafe_fetch(z.size - 1) > x; res += z.size }
    res
  end
  private def bsearch_lower(z : Array(T), x : T) : Int32
    l = -1
    r = z.size
    while l + 1 < r
      m = l + (r - l >> 1)
      if z.unsafe_fetch(m) < x
        l = m
      else
        r = m
      end
    end
    r
  end
  private def bsearch_upper(z : Array(T), x : T) : Int32
    l = -1
    r = z.size
    while l + 1 < r
      m = l + (r - l >> 1)
      if z.unsafe_fetch(m) <= x
        l = m
      else
        r = m
      end
    end
    r
  end
  struct SetIterator(T)
    include Comparable(SetIterator(T))
    include ::Iterator(T)
    def initialize(@outer : Int32, @inner : Int32, @bag : Array(Array(T))); end
    def pos : {Int32, Int32}; {@outer, @inner}; end
    def value : T; @bag.unsafe_fetch(@outer).unsafe_fetch(@inner); end
    def value=(x : T) : T; @bag.unsafe_fetch(@outer).unsafe_put(@inner, x); end
    def advance(n : Int = 1) : self
      outer = @outer
      inner = @inner
      if n >= 0
        while outer < @bag.size && @bag.unsafe_fetch(outer).size - inner <= n
          n -= @bag.unsafe_fetch(outer).size - inner; inner = 0; outer += 1
        end
        inner += n
        inner, outer = 0, @bag.size if @bag.size <= outer
      else
        n = -n
        while 0 <= outer && inner < n
          n -= inner + 1; inner = 0 <= (outer -= 1) ? @bag.unsafe_fetch(outer).size - 1 : 0
        end
        inner -= n
        inner = outer = 0 if outer < 0
      end
      @outer = outer
      @inner = inner
      self
    end
    def next
      if @outer >= @bag.size
        stop
      else
        res = self.value
        advance(1)
        res
      end
    end
    def +(n : Int) : self; SetIterator(T).new(@outer, @inner, @bag).advance(n); end
    def -(n : Int) : self; self + -n; end
    def -(b : SetIterator(T)) : Int32
      dist, sign = 0, 1
      ain, aout = @inner, @outer
      bout, bin = b.pos
      if aout < bout || (aout == bout && ain < bin)
        ain, bin = bin, ain
        aout, bout = bout, aout
        sign = -1
      end
      while aout > bout
        dist += @bag.unsafe_fetch(bout).size - bin; bin = 0; bout += 1
      end
      dist += ain - bin
      dist * sign
    end
    def <=>(other : SetIterator(T))
      cmp = @outer <=> other.@outer
      cmp != 0 ? cmp : @inner <=> other.@inner
    end
  end
  def head; SetIterator(T).new(0, 0, @list); end
  def tail; SetIterator(T).new(@list.size, 0, @list); end
end
