class BIT(T)
  @d : Pointer(T)
  def initialize(@n : Int) : Nil
    @d = Pointer(T).malloc @n + 1, T.zero
  end
  def initialize(z : Array(T)) : Nil
    @n = z.size
    @d = Pointer(T).malloc @n + 1, T.zero
    1.upto(@n) { |i| @d[i] = z.unsafe_fetch(i - 1) }
    1.upto(@n) do |i|
      j = i + (i & -i)
      @d[j] += @d[i] if j <= @n
    end
  end
  def add(i : Int, x : T) : Nil
    i += 1
    while i <= @n
      @d[i] += x
      i += i & -i
    end
  end
  def sum(i : Int)
    i += 1
    s = T.zero
    while 0 < i
      s += @d[i]
      i -= i & -i
    end
    s
  end
  def sum(l : Int, len : Int)
    r = l + len
    s = T.zero
    while l < r
      s += @d[r]
      r -= r & -r
    end
    while r < l
      s -= @d[l]
      l -= l & -l
    end
    s
  end
  def [](l : Int, len : Int); sum l, len; end
  def [](range : Range)
    l = range.begin || 0
    r = range.exclusive? ? (range.end || @n) : (range.end || @n - 1) + 1
    sum l, r - l
  end
  def [](i : Int)
    i += 1; j = 1
    s = @d[i]
    while i & j == 0
      s -= @d[i - j]
      j <<= 1
    end
    s
  end
  def lower_bound(x : T)
    i = 0; k = 1 << @n.bit_length - 1
    while 0 < k
      if i + k <= @n && @d[i + k] < x
        x -= @d[i + k]; i += k
      end
      k >>= 1
    end
    i
  end
  def upper_bound(x : T)
    i = 0; k = 1 << @n.bit_length - 1
    while 0 < k
      if i + k <= @n && @d[i + k] <= x
        x -= @d[i + k]; i += k
      end
      k >>= 1
    end
    i
  end
end
