# mappingはarg2に対するarg1による写像
# compositionはarg2に対するarg1の合成
class LazySegtree(S, F)
  def initialize(@n : Int32, @e : Proc(S), @d : Array(S), @op : Proc(S, S, S), @mapping : Proc(F, S, S),
  @composition : Proc(F, F, F), @lazy : Array(F), @has_lazy : Array(Bool));end
  def initialize(@n : Int32, @e : Proc(S), @op : Proc(S, S, S), @mapping : Proc(F, S, S), @composition : Proc(F, F, F))
    @d = Array(S).new(@n + @n) { @e.call }
    @lazy = Array(F).build(@n + @n) { @n + @n }
    @has_lazy = Array(Bool).new @n + @n, false
  end
  def initialize(z : Array(S), @e : Proc(S), @op : Proc(S, S, S), @mapping : Proc(F, S, S), @composition : Proc(F, F, F))
    @n = x = z.size
    @d = Array(S).new(@n) { @e.call } + z
    @lazy = Array(F).build(@n + @n) { @n + @n }
    @has_lazy = Array(Bool).new @n + @n, false
    while 0 < (x -= 1)
      @d[x] = @op.call @d[x << 1], @d[x << 1 | 1]
    end
  end
  @[AlwaysInline]
  private def _apply(k : Int, f : F) : Nil
    @d[k] = @mapping.call f, @d[k]
    if k < @n
      if @has_lazy[k]
        @lazy[k] = @composition.call f, @lazy[k]
      else
        @has_lazy[k] = true
        @lazy[k] = f
      end
    end
  end
  @[AlwaysInline]
  private def propagate(k : Int) : Nil
    if @has_lazy[k]
      _apply k << 1, @lazy[k]
      _apply k << 1 | 1, @lazy[k]
      @has_lazy[k] = false
    end
  end
  @[AlwaysInline]
  private def propagate_p(k : Int) : Nil
    (k.bit_length - 1).downto(1) do |i|
      propagate k >> i
    end
  end
  def clone
    LazySegtree(S).new @n, @e, @d.clone, @op, @mapping, @composition, @lazy.clone, @has_lazy.clone
  end
  def to_a;@d[@n..];end
  def [](k : Int)
    k += @n
    propagate_p k
    @d[k]
  end
  def []=(k : Int, x : S)
    k += @n
    propagate_p k
    @d[k] = x
    while 0 < (k >>= 1)
      @d[k] = @op.call @d[k << 1], @d[k << 1 | 1]
    end
    x
  end
  def apply(range : Range, f : F) : Nil
    l = range.begin || 0
    r = range.exclusive? ? (range.end || @n) : (range.end || @n - 1) + 1
    return if r <= l || @n <= l || r <= 0
    l += @n; r += @n
    l0, r0 = l >> l.trailing_zeros_count, (r >> r.trailing_zeros_count) - 1
    propagate_p l0
    propagate_p r0
    while l < r
      (_apply(l, f); l += 1) if l & 1 == 1
      _apply (r -= 1), f if r & 1 == 1
      l >>= 1; r >>= 1
    end
    l, r = l0, r0
    while 0 < (l >>= 1)
      @d[l] = @op.call @d[l << 1], @d[l << 1 | 1]
    end
    while 0 < (r >>= 1)
      @d[r] = @op.call @d[r << 1], @d[r << 1 | 1]
    end
  end
  def apply(l : Int, len : Int, f : F) : Nil
    apply l...(l + len), f
  end
  def apply(k : Int, f : F)
    k += @n
    propagate_p k
    res = @d[k] = @mapping.call f, @d[k]
    while 0 < (k >>= 1)
      @d[k] = @op.call @d[k << 1], @d[k << 1 | 1]
    end
    res
  end
  def [](range : Range)
    l = range.begin || 0
    r = range.exclusive? ? (range.end || @n) : (range.end || @n - 1) + 1
    if r <= l || @n <= l || r <= 0
      return @e.call
    end
    l += @n; r += @n
    propagate_p l >> l.trailing_zeros_count
    propagate_p (r >> r.trailing_zeros_count) - 1
    x = y = @e.call
    while l < r
      x, l = @op.call(x, @d[l]), l + 1 if l & 1 == 1
      y = @op.call(@d[r -= 1], y) if r & 1 == 1
      l >>= 1; r >>= 1
    end
    @op.call x, y
  end
  def [](l : Int, len : Int)
    self[l...(l + len)]
  end
  def right_bound(k : Int32, &f : S -> Bool)
    r = @n + @n
    x = @e.call
    h = 0
    k += @n
    propagate_p l >> l.trailing_zeros_count
    propagate_p (r >> r.trailing_zeros_count) - 1
    bsearch = ->(v : Int32) do
      while v < @n
        propagate v
        v <<= 1
        (x = @op.call x, @d[v]; v += 1) if f.call @op.call x, @d[v]
      end
      v - @n
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
    while (r <<= 1; 0 <= (h -= 1))
      if r + 1 << h <= @n + @n
        propagate r
        return bsearch.call r if !f.call @op.call x, @d[r]
        x = @op.call x, @d[r]
        r += 1
      end
    end
    @n
  end
  def left_bound(k : Int32, &f : S -> Bool)
    l = @n
    x = @e.call
    h = 0
    k += @n
    propagate_p l >> l.trailing_zeros_count
    propagate_p (r >> r.trailing_zeros_count) - 1
    bsearch = ->(v : Int32) do
      while v < @n
        propagate v
        v = v << 1 | 1
        (x = @op.call @d[v], x; v -= 1) if f.call @op.call @d[v], x
      end
      v - @n
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
    while (l <<= 1; 0 <= (h -= 1))
      if @n <= l - 1 << h
        l -= 1
        propagate l
        return bsearch.call l if !f.call @op.call @d[l], x
        x = @op.call @d[l], x
      end
    end
    0
  end
end
