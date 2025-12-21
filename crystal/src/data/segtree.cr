class Segtree(T)
  getter n
  def initialize(@n : Int32, @e : Proc(T), @d : Array(T), &@op : T, T -> T);end
  def initialize(@n : Int32, @e : Proc(T), &@op : T, T -> T);@d = Array(T).new 2 * @n, @e.call;end
  def initialize(z : Array(T), @e : Proc(T), &@op : T, T -> T)
    @n = x = z.size
    @d = Array(T).new(n, @e.call) + z
    while 0 < (x -= 1)
      @d[x] = @op.call @d[x << 1], @d[x << 1 | 1]
    end
  end
  def clone
    Segtree(T).new n, @e, @d.clone, &@op
  end
  def to_a;@d[n..];end
  def [](k : Int32);@d[k + n];end
  def []=(k : Int32, x : T)
    @d[k += n] = x
    while 0 < (k >>= 1)
      @d[k] = @op.call @d[k << 1], @d[k << 1 | 1]
    end
    x
  end
  def [](range : Range)
    l = range.begin || 0
    r = range.exclusive? ? (range.end || n) : (range.end || n - 1) + 1
    l += n; r += n
    x = y = @e.call
    while l < r
      x, l = @op.call(x, @d[l]), l + 1 if l & 1 != 0
      y = @op.call(@d[r -= 1], y) if r & 1 != 0
      l >>= 1
      r >>= 1
    end
    @op.call x, y
  end
  def right_bound(k : Int32, &f : T -> Bool)
    r = n + n
    x = @e.call
    h = 0
    k += n
    bsearch = ->(v : Int32) do
      while v < n
        v <<= 1
        (x = @op.call x, @d[v]; v += 1) if f.call @op.call x, @d[v]
      end
      v - n
    end
    while k < r
      if k & 1 != 0
        return bsearch.call k if !f.call @op.call x, @d[k]
        x = @op.call x, @d[k]
        k += 1
      end
      r -= 1 if r & 1 != 0
      k >>= 1; r >>= 1; h += 1
    end
    while (r <<= 1; 0 < (h -= 1))
      if (r + 1) << h <= n + n
        return bsearch.call r if !f.call @op.call x, @d[r]
        x = @op.call x, @d[r]
        r += 1
      end
    end
    n
  end
  def left_bound(k : Int32, &f : T -> Bool)
    l = n
    x = @e.call
    h = 0
    k += n
    bsearch = ->(v : Int32) do
      while v < n
        v = v << 1 | 1
        (x = @op.call @d[v], x; v -= 1) if f.call @op.call @d[v], x
      end
      v - n
    end
    while l < k
      if k & 1 != 0
        k -= 1
        return bsearch.call k if !f.call @op.call @d[k], x
        x = @op.call @d[k], x
      end
      l += 1 if l & 1 != 0
      l >>= 1; k >>= 1; h += 1
    end
    while (l <<= 1; 0 < (h -= 1))
      if n <= (l - 1) << h
        l -= 1
        return bsearch.call l if !f.call @op.call @d[l], x
        x = @op.call @d[l], x
      end
    end
    n
  end
end
