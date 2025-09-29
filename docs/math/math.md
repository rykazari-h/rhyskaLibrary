# math
[Code](../../src/dmath/math.h)  
数学っぽいもの。
namespace math。
## modinv
```cpp
i64 modinv(i64 a, i64 m)
```
* mod mにおけるaの逆元を返す
* assert a⊥m
* O(log(min(a, m)))
## modpow
```cpp
i64 modpow(i64 a, i64 b, i64 m=998244353)
```
* a^b mod mを返す
* O(log b)
## gcd
```cpp
i64 gcd(i64 a)
i64 gcd(i64 a, i64 b)
i64 gcd(i64 a, i64 b,i64 c...)
```
* 入力の最大公約数を返す
* O(log(min(a,b)))
## lcm
```cpp
i64 lcm(i64 a)
i64 lcm(i64 a, i64 b)
i64 lcm(i64 a, i64 b,i64 c...)
```
* 入力の最小公倍数を返す
* O(log(min(a,b)))
