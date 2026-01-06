def modinv(a : Int64, m : Int64)
  b = m
  #track M = |u x| such that M * |a| = |gcd(a b)|
  #          |v _|               |b|   |0       |
  #=> au + bx = gcd(a b)

  #identity matrix
  u, v = 1i64, 0i64
  while 0 < b
    q = a // b
    #r = a - q * b = a % b
    #|0  1| * |a| = |b|
    #|1 -q|   |b|   |r|
    a, b = b, a - q * b
    #|0  1| * |u _| = |v    _|
    #|1 -q|   |v _|   |u-vq _|
    u, v = v, u - v * q
  end
  u % m
end
