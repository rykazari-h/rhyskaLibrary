def inv_gcd(a : Int64, m : Int64)
  b = m
  # track M = |u t| such that M * |a| = |gcd(a b)| => au + bt = gcd(a b)
  #           |v _|               |b|   |0       |

  # identity matrix
  u, v = 1i64, 0i64
  while b != 0
    q = a // b
    # r = a - q * b = a % b
    # |0  1| * |a| = |b|
    # |1 -q|   |b|   |r|
    a, b = b, a - q * b
    # |0  1| * |u _| = |v    _|
    # |1 -q|   |v _|   |u-vq _|
    u, v = v, u - v * q
  end
  {u % m, a}
end

def modinv(a : Int64, m : Int64)
  u, d = inv_gcd(a, m)
  d == 1 ? u : 0
end

#     x = m0*k + r0
#     x = r1 mod m1
# <=> m0*k + r0 = r1 mod m1
# <=> m0*k = r1 - r0 mod m1
# <=> m0/d*k = (r1- r0)/d mod m1/d where d = gcd(m0 m1), require d | r1 - r0
# <=> k = (r1 - r0)/d*(m0/d)^-1 mod m1/d
def crt(r : Array(Int64), m : Array(Int64))
  r0, m0 = 0i64, 1i64
  r.each_with_index do |r1, i|
    m1 = m[i]
    r1 %= m1
    if m0 < m1
      r0, r1 = r1, r0
      m0, m1 = m1, m0
    end
    if m0 % m1 == 0
      return {0i64, 0i64} if r0 % m1 != r1
      next
    end
    u, d = inv_gcd m0, m1
    return {0i64, 0i64} if (r1 - r0) % d != 0
    ms = m1 // d
    k = (r1 - r0) // d * u % ms
    r0 += m0 * k
    m0 *= ms
    r0 %= m0
  end
  {r0, m0}
end

def modpow(a : Int64, p : Int64, m : Int64 = 998244353)
  res = 1i64
  a %= m
  while p != 0
    res = res * a % m if p & 1 != 0
    p >>= 1
    a = a * a % m
  end
  res
end

# for prime numbers
# return minimum number g such that i!=j => g^i!=g^j
def primitive_root(n : Int64) : Int64
  return 1i64 if n == 2
  p = n - 1
  d = StaticArray(Int64, 20).new 0
  d[0] = 2
  c = 1
  x = p
  while x & 1 == 0;x >>= 1;end
  i = 3i64
  loop do
    break if x < i * i
    (i += 2;next) if x % i != 0
    d[c] = i
    c += 1
    while x % i == 0;x //= i;end
    i += 2
  end
  (d[c] = x;c += 1) if 1 < x
  (2i64..p).each do |g|
    f = true
    c.times do |i|
      # i!=j => g^i!=g^j && g^p=1
      if modpow(g, p // d[i], n) == 1
        f = false
        break
      end
    end
    return g if f
  end
  -1i64
end

# return x such that g^x = b mod m
#     g^x = b mod m && iu-j = x
# <=> g^{iu-j}=b mod m
# <=> g^{iu}=bg^j mod m
# require gcd(g m) = 1
def discrete_log(g : Int64, b : Int64, m : Int64)
  g %= m
  b %= m
  return 1i64 if m == 1 || g == b
  if g == 0
    if b == 0
      return 1i64
    else
      return -1i64
    end
  end
  return -1 if g == 1
  u = Math.isqrt m + 1
  map = Hash(Int64, Int64).new
  current = b
  (0i64..u).each do |j|
    map[current] = j
    current = current * g % m
  end
  base = current = modpow g, u, m
  (1i64..u).each do |i|
    if j = map[current]?
      ans = i * u - j
      return ans if 0 < ans
    end
    current = current * base % m
  end
  -1i64
end
