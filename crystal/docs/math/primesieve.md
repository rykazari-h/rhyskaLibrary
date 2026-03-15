# primesieve
```crystal
# 初期化
PrimeSieve.new x : Int32
sieve.build x : Int32
# 素数かどうか
sieve[k : Int32]
# 素因数分解
sieve.factorize x : Int32
# 約数列挙
sieve.divisors x : Int32
# カウント、素数列挙
sieve.count; sieve.primelist
```
