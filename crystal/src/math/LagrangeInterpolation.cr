struct LagrangeInterpolation(T)
  # y = [f(0), f(1), f(2), ..., f(k)]
  getter y : Array(T)
  getter k : Int32
  @ifact : Array(T)
  #普通にfをつくる
  def initialize(@y : Array(T));@k = y.size - 1;@ifact = [T.new 0]*(k + 1);set;end
  
  #fは関数の和になる
  #指数昇順に{係数,指数}
  #f(x)=sum z(i)
  #k^2logk
  def initialize(z : Array({T, Int32}))
    @k = z[-1][1] + 1
    sum = T.new 0
    @y = Array(T).new(k + 1) do |i|
      r = T.new 0
      w = T.new 1
      prev = 0
      z.each do |a, p|
        w *= qpow T.new(i), p - prev
        prev = p
        r += a * w
      end
      sum += r
    end
    @ifact = [T.new 0]*(k + 1)
    set
  end
  @[AlwaysInline]
  private def qpow(x : T, p : Int32)
    r = T.new 1
    while 0 < p
      r *= x if p & 1 == 1
      x *= x
      p >>= 1
    end
    r
  end
  @[AlwaysInline]
  private def set
    fact = T.new(1)
    (1..k).each { |v| fact *= v }
    @ifact[k] = T.new(1) / fact
    k.downto(1) { |i| @ifact[i - 1] = @ifact[i] * i }
  end
  def f(x : T)
    return y[x.to_i] if x.to_i == x && 0 <= x.to_i <= k
    prod = [T.new 1]*(k + 2)
    0.upto(k) { |i| prod[i + 1] = prod[i] * (x - i) }
    iprod = [T.new 1]*(k + 2)
    k.downto(0) { |i| iprod[i] = iprod[i + 1] * (x - i) }
    r = T.new 0
    0.upto(k) do |i|
      w = y[i] * prod[i] * iprod[i + 1] * @ifact[i] * @ifact[k - i]
      if k - i & 1 == 1
        r -= w
      else
        r += w
      end
    end
    r
  end
end
