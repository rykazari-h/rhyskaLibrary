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
  raise "Argument error on crt" if r.size != m.size
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
