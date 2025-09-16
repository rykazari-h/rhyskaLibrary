# Coordinate compression
## constructor
```cpp
cc c(std::vector<Tp> v)
cc c(Tp* l, Tp* r)
cc c()
```
* 要素ひとつあたりO(1)
## push
```cpp
void c.push(Tp x)
void c.push(std::vector<Tp> v)
void c.push(Tp* l, Tp* r)
```
* 要素ひとつあたりO(1)
## operator[]
```cpp
Tp c[int t]
```
* indexから実座標を返す
* ならしO(1)
## operator()
```cpp
int c(Tp t)
```
* 実座標からindexを返す
* ならしO(logn)
## press
```cpp
std::vector<int> c(std::vector<Tp> v)
std::vector<int> c(Tp* l, Tp* r)
```
* 処理済みの座標に対して、引数の要素のindexの配列を返す。
* ならしO(n logn)
