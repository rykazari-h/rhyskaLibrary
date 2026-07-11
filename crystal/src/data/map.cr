class Map(K, V)
  include Enumerable({K, V})
  include Iterable({K, V})
  BOUND = 20
  getter size
  def self.zip(z1 : Array(K), z2 : Array(V), default : V) : Map(K, V)
    n = z1.size < z2.size ? z1.size : z2.size
    return Map(K, V).new(default) if n == 0
    idx = Array(Int32).new(n) { |i| i }
    idx.unstable_sort! do |i, j|
      cmp = z1.unsafe_fetch(i) <=> z1.unsafe_fetch(j)
      cmp == 0 ? j <=> i : cmp # uniqueのために逆転
    end
    fi = 0
    last = idx.unsafe_fetch(0)
    1.upto(n - 1) do |i|
      if z1.unsafe_fetch(last) != z1.unsafe_fetch(idx.unsafe_fetch(i))
        idx.unsafe_put(fi, last)
        fi += 1
        last = idx.unsafe_fetch(i)
      end
    end
    idx[fi] = last; fi += 1
    rate = 8
    sz = {1, Math.sqrt(fi / rate).ceil.to_i}.max
    ks = Array(Array(K)).new sz
    vs = Array(Array(V)).new sz
    sz.times do |i|
      l = fi * i // sz
      r = fi * (i + 1) // sz
      ks << Array(K).new(r - l) { |j| z1.unsafe_fetch(idx.unsafe_fetch(l + j)) }
      vs << Array(V).new(r - l) { |j| z2.unsafe_fetch(idx.unsafe_fetch(l + j)) }
    end
    Map(K, V).new(fi, ks, vs, default)
  end
  def initialize(@default : V)
    @size = 0
    @key = [] of Array(K)
    @val = [] of Array(V)
  end
  def initialize(@size : Int32, @key : Array(Array(K)), @val : Array(Array(V)), @default : V); end
  def ==(other : Map(K, V)) : Bool
    key, val = other.data
    @size == other.size && @key == key && @val == val
  end
  def empty? : Bool; @size == 0; end
  def clear : Nil; @size = 0; @key.clear; @val.clear; end
  def clone : Map(K, V); Map(K, V).new(@size, @key.clone, @val.clone, @default.clone); end
  def dup; Map(K, V).new(@size, @key.dup, @val.dup, @default.clone); end
  def _position(x : K) : {Int32, Int32}
    sz = @key.size
    sz.times do |i|
      z = @key.unsafe_fetch(i)
      return {i, bsearch_lower(z, x)} if x <= z.unsafe_fetch(z.size - 1)
    end
    {sz - 1, @key[-1].size}
  end
  def _pop(bi : Int32, i : Int32) : {K, V}
    zk = @key.unsafe_fetch(bi)
    zv = @val.unsafe_fetch(bi)
    k = zk.delete_at(i)
    v = zv.delete_at(i)
    (@key.delete_at(bi); @val.delete_at(bi)) if zk.empty?
    @size -= 1
    {k, v}
  end
  def []=(k : K, v : V) : V
    (@key = [[k]]; @val = [[v]]; @size = 1; return v) if empty?
    bi, i = _position(k)
    zk = @key.unsafe_fetch(bi)
    zv = @val.unsafe_fetch(bi)
    (zv.unsafe_put(i, v); return v) if i != zk.size && zk.unsafe_fetch(i) == k
    zk.insert(i, k)
    zv.insert(i, v)
    @size += 1
    if zk.size > @key.size*BOUND
      mid = zk.size >> 1
      len = zk.size - mid

      nb = zk[mid, len]
      zk.delete_at mid, len
      @key.insert(bi + 1, nb)

      nb1 = zv[mid, len]
      zv.delete_at mid, len
      @val.insert(bi + 1, nb1)
    end
    v
  end
  def [](k : K) : V
    (@key = [[k]]; @val = [[@default]]; @size = 1; return @default) if empty?
    bi, i = _position(k)
    zk = @key.unsafe_fetch(bi)
    zv = @val.unsafe_fetch(bi)
    return zv.unsafe_fetch(i) if i != zk.size && zk.unsafe_fetch(i) == k
    zk.insert(i, k)
    zv.insert(i, @default)
    @size += 1
    if zk.size > @key.size*BOUND
      mid = zk.size >> 1
      len = zk.size - mid

      nb = zk[mid, len]
      zk.delete_at mid, len
      @key.insert(bi + 1, nb)

      nb1 = zv[mid, len]
      zv.delete_at mid, len
      @val.insert(bi + 1, nb1)
    end
    @default
  end
  def []?(k : K) : V?
    return nil if empty?
    bi, i = _position(k)
    zk = @key.unsafe_fetch(bi)
    zv = @val.unsafe_fetch(bi)
    i != zk.size && zk.unsafe_fetch(i) == k ? zv.unsafe_fetch(i) : nil
  end
  def delete(x); erase(x); end
  def delete(x, &) : Nil; yield erase(x); end
  def erase(k : K) : V?
    return nil if empty?
    bi, i = _position(k)
    zk = @key.unsafe_fetch(bi)
    return nil if i == zk.size || zk.unsafe_fetch(i) != k
    res = @val.unsafe_fetch(bi).unsafe_fetch(i)
    _pop(bi, i)[1]
  end
  def erase(it : MapIterator(K, V)) : {K, V}?
    bi, i = it.pos
    return nil if bi == @key.size
    _pop(bi, i)
  end
  def each : MapIterator(K, V); head; end
  def each(& : {K, V} ->) : Nil
    @key.size.times do |i|
      zk = @key.unsafe_fetch(i)
      zv = @val.unsafe_fetch(i)
      zk.size.times do |j|
        yield({zk.unsafe_fetch(j), zv.unsafe_fetch(j)})
      end
    end
  end
  def each_key(& : K ->) : Nil
    @key.size.times do |i|
      zk = @key.unsafe_fetch(i)
      zk.size.times do |j|
        yield zk.unsafe_fetch(j)
      end
    end
  end
  def each_value(& : V ->) : Nil
    @val.size.times do |i|
      zv = @val.unsafe_fetch(i)
      zv.size.times do |j|
        yield zv.unsafe_fetch(j)
      end
    end
  end
  def count(k : K) : Bool; has_key?(k); end
  def has_key?(k : K) : Bool
    return false if empty?
    bi, i = _position(k)
    i != @key.unsafe_fetch(bi).size && @key.unsafe_fetch(bi).unsafe_fetch(i) == k
  end
  def keys : Array(K); @key.flatten; end
  def values : Array(V); @val.flatten; end
  def data : {Array(Array(K)), Array(Array(V))}; {@key, @val}; end
  def to_a : Array({K, V})
    Array.build(@size) do |buf|
      i = 0
      self.each do |x|
        buf[i] = x
        i += 1
      end
      @size
    end
  end
  def pop(i : Int = -1) : {K, V}
    if i >= 0
      @key.size.times do |b|
        return _pop(b, i) if i < @key.unsafe_fetch(b).size
        i -= @key.unsafe_fetch(b).size
      end
    else
      (@key.size - 1).downto(0) do |b|
        i += @key.unsafe_fetch(b).size
        return _pop(b, i) if i >= 0
      end
    end
    raise IndexError.new
  end
  def kth(i : Int) : {K, V}
    if i >= 0
      @key.size.times do |b|
        return {@key.unsafe_fetch(b).unsafe_fetch(i), @val.unsafe_fetch(b).unsafe_fetch(i)} if i < @key.unsafe_fetch(b).size
        i -= @key.unsafe_fetch(b).size
      end
    else
      (@key.size - 1).downto(0) do |b|
        i += @key.unsafe_fetch(b).size
        return {@key.unsafe_fetch(b).unsafe_fetch(i), @val.unsafe_fetch(b).unsafe_fetch(i)} if i >= 0
      end
    end
    raise IndexError.new
  end
  def lower_bound(x : K) : MapIterator(K, V)
    @key.size.times do |i|
      z = @key.unsafe_fetch(i)
      return MapIterator(K, V).new(i, bsearch_lower(z, x), @key, @val) if !z.empty? && z.unsafe_fetch(z.size - 1) >= x
    end
    tail
  end
  def upper_bound(x : K) : MapIterator(K, V)
    @key.size.times do |i|
      z = @key.unsafe_fetch(i)
      return MapIterator(K, V).new(i, bsearch_upper(z, x), @key, @val) if !z.empty? && z.unsafe_fetch(z.size - 1) > x
    end
    tail
  end
  def index(x : K) : Int32
    res = 0
    @key.each { |z| return res + bsearch_lower(z, x) if z.unsafe_fetch(z.size - 1) >= x; res += z.size }
    res
  end
  def index_rg(x : K) : Int32
    res = 0
    @key.each { |z| return res + bsearch_upper(z, x) if z.unsafe_fetch(z.size - 1) > x; res += z.size }
    res
  end
  private def bsearch_lower(z : Array(K), k : K) : Int32
    l = -1
    r = z.size
    while l + 1 < r
      m = l + (r - l >> 1)
      if z.unsafe_fetch(m) < k
        l = m
      else
        r = m
      end
    end
    r
  end
  private def bsearch_upper(z : Array(K), k : K) : Int32
    l = -1
    r = z.size
    while l + 1 < r
      m = l + (r - l >> 1)
      if z.unsafe_fetch(m) <= k
        l = m
      else
        r = m
      end
    end
    r
  end
  struct MapIterator(K, V)
    include ::Iterator({K, V})
    include Comparable(MapIterator(K, V))
    def initialize(@outer : Int32, @inner : Int32, @key : Array(Array(K)), @val : Array(Array(V))); end
    def pos : {Int32, Int32}; {@outer, @inner}; end
    def key : K; @key.unsafe_fetch(@outer).unsafe_fetch(@inner); end
    def key=(x : K) : K; @key.unsafe_fetch(@outer).unsafe_put(@inner, x); end
    def val : V; @val.unsafe_fetch(@outer).unsafe_fetch(@inner); end
    def val=(x : V) : V; @val.unsafe_fetch(@outer).unsafe_put(@inner, x); end
    def value : {K, V}; {key, val}; end
    def value=(x : {K, V}) : {K, V}
      self.key = x[0]
      self.val = x[1]
      x
    end
    def advance(n : Int = 1) : self
      outer = @outer
      inner = @inner
      if n >= 0
        while outer < @key.size && @key.unsafe_fetch(outer).size - inner <= n
          n -= @key.unsafe_fetch(outer).size - inner; inner = 0; outer += 1
        end
        inner += n
        inner, outer = 0, @key.size if @key.size <= outer
      else
        n = -n
        while 0 <= outer && inner < n
          n -= inner + 1; inner = 0 <= (outer -= 1) ? @key.unsafe_fetch(outer).size - 1 : 0
        end
        inner -= n
        inner = outer = 0 if outer < 0
      end
      @outer = outer
      @inner = inner
      self
    end
    def next
      if @outer >= @key.size
        stop
      else
        res = self.value
        advance(1)
        res
      end
    end
    def +(n : Int) : self; MapIterator(K, V).new(@outer, @inner, @key, @val).advance(n); end
    def -(n : Int) : self; self + -n; end
    def -(b : MapIterator(K, V)) : Int32
      dist, sign = 0, 1
      ain, aout = @inner, @outer
      bout, bin = b.pos
      if aout < bout || (aout == bout && ain < bin)
        ain, bin = bin, ain
        aout, bout = bout, aout
        sign = -1
      end
      while aout > bout
        dist += @key.unsafe_fetch(bout).size - bin; bin = 0; bout += 1
      end
      dist += ain - bin
      dist * sign
    end
    def <=>(other : MapIterator(K, V))
      outer, inner = other.pos
      cmp = @outer <=> outer
      cmp != 0 ? cmp : @inner <=> inner
    end
  end
  def head; MapIterator(K, V).new(0, 0, @key, @val); end
  def tail; MapIterator(K, V).new(@key.size, 0, @key, @val); end
end
