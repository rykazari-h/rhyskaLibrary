# Prime
[Code](../../src/math/prime.h)
## constructor
```cpp
prime p(int n)
```
* build(n)を呼ぶ
* O(n loglogn)
## build
```cpp
void p.build(int n)
```
* n以下の自然数を篩う
* O(n loglogn)
## operator[]
```cpp
bool p[int x]
```
* xが素数かどうか返す
* O(1)
## count
```cpp
int p.count()
```
* 篩った範囲の素数の個数を返す
* O(n)
## primelist
```cpp
std::vector<int> p.primelist()
```
* 篩った範囲の素数を列挙する
* 返す配列は昇順であることが保証される
* O(n)
## factorize
```cpp
std::vector<std::pair<int,int>> p.factorize(int x)
```
* {素因数,指数}のペアの配列を返す
* O(log x)
## divisors
```cpp
std::vector<int> p.divisors(int x)
```
* xの約数の配列を返す（昇順とは限らない）
* O(σ(x)) (σ(x)をxの約数の個数とする, σ(x)は実用の範囲だと最大で1000ほど)
