# bucket_set
[Code](../../src/data/kthset.h)
## このクラスについて
ランダムアクセスが可能であるset。参考はtatyam氏の[SortedSet](https://github.com/tatyam-prime/SortedSet/tree/main)  
std::setで使える機能はだいたい使える。また、変更を伴う操作はbool値を返す。  
計算量はだいたいO(root(n))で、二分探索などの集合の走査を必要とするメソッドはstd::setよりも高速に動作する。
## constructor
```cpp
bucket_set<T> s()
bucket_set<T> s(std::vector<T> z)
```
* O(n logn) (zがソート済みのときO(n))
## iteator::operator+/-
* ランダムアクセス可能⇔operator+/-が用意されている
## pop
```cpp
T s.pop(int k=-1)
```
* k番目に小さい要素を削除し、それを返す
## operator[]
```cpp
T s[int k]
```
* k番目に小さい要素を返す
## insert/erase
```cpp
bool s.insert(T x)
bool s.erase(T x)
```
* 操作に成功したときtrueを返す
## toggle
```cpp
bool s.toggle(T x)
```
* xが存在するとき削除し、しないときには挿入する
* 返り値はinsertに等しい

