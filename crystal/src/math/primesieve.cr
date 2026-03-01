class PrimeSieve
  def initialize(x : Int32)
    @bfactor = Array(Int32).new
    build x
  end
  def build(x : Int32)
    x += 1
    xd = x >> 1
    @bfactor = Array(Int32).build(xd) do |pt|
      xd.times { |i| pt[i] = i << 1 | 1 }
      xd
    end
    xr = (Math.sqrt(x) + 0.1).ceil.to_i >> 1
    i = 0
    loop do
      i += 1
      break if i == xr
      next if @bfactor[i] != i << 1 | 1
      k = i << 1 | 1
      (i * (i + 1) << 1).step(to: xd, by: k, exclusive: true) { |j| @bfactor[j] = k }
    end
  end
  def [](x : Int32)
    if x == 2
      true
    elsif x < 2
      false
    elsif x & 1 == 1
      @bfactor[x - 1 >> 1] == x
    else
      false
    end
  end
  def factorize(x : Int32)
    return [{0, 0}] if x == 0
    return [{1, 1}] if x == 1
    res = Array({Int32, Int32}).new
    cnt = 0
    while x & 1 == 0 && 1 < x
      cnt += 1
      x >>= 1
    end
    res = [{2, cnt}] if 0 < cnt
    pidx = x - 1 >> 1
    while 1 < x
      px, e = @bfactor[pidx], 0
      while x % px == 0
        x //= px
        e += 1
      end
      res << {px, e}
      pidx = x - 1 >> 1
    end
    res
  end
  def divisors(x : Int32)
    res = [1]
    factorize(x).each do |px|
      n = res.size
      n.times do |i|
        j, v = 0, 1
        while j < px[1]
          v *= px[0]
          res << res[i] * v
          j += 1
        end
      end
    end
    if res.size == 2 && res[0] == res[1]
      [1]
    else
      res
    end
  end
  def count
    res = 0
    1.upto(@bfactor.size - 1) do |i|
      res += @bfactor[i] == i << 1 | 1 ? 1 : 0
    end
    res
  end
  def primelist
    res = Array(Int32).new
    1.upto(@bfactor.size - 1) do |i|
      res << (i << 1 | 1) if @bfactor[i] == i << 1 | 1
    end
    res
  end
end
