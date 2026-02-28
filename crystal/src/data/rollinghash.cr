class Rollinghash
  MOD = 0x1fffffffffffffffu64
  @@b : UInt64 = (Random.rand(999) + 1000).to_u64
  @@p : Array(UInt64) = [1u64]
  @h : Array(UInt64)
  getter n : Int32
  @[AlwaysInline]
  private def normalize(t : Int128)
    t = (t >> 61) + (t & MOD)
    (MOD <= t ? t - MOD : t).to_u64
  end
  def initialize(s : Array(Int))
    if @@p.size < s.size + 1
      t = @@p.size
      @@p.concat [1u64]*(s.size - t + 1)
      t.upto(s.size) do |i|
        @@p[i] = normalize @@p[i - 1].to_i128 * @@b
      end
    end
    @n = s.size
    @h = [0u64]*(n + 1)
    n.times do |i|
      @h[i + 1] = normalize @h[i].to_i128 * @@b + s[i]
    end
  end
  def [](range : Range)
    l = range.begin || 0
    r = range.exclusive? ? (range.end || n) : (range.end || n - 1) + 1
    t = @h[r] + MOD - normalize @h[l].to_i128 * @@p[r - l]
    (MOD <= t ? t - MOD : t).to_u64
  end
  def [](l, len)
    r = l + len
    t = @h[r] + MOD - normalize @h[l].to_i128 * @@p[r - l]
    (MOD <= t ? t - MOD : t).to_u64
  end
  def concat(h1, h2, l2)
    normalize @@p[l2].to_i128 * h1 + h2
  end
end
