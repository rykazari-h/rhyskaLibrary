# bucket_multiset
## このクラスについて
ランダムアクセスが可能であるmultiset。参考はtatyam氏の[SortedMultiset](https://github.com/tatyam-prime/SortedSet/tree/main)  
std::multisetで使える機能はだいたい使える。  
計算量はだいたいO(root(n))で、二分探索などの集合の走査を必要とするメソッドはstd::multisetよりも高速に動作する。
## constructor
```cpp
bucket_multiset<T> s()
bucket_multiset<T> s(std::vector<T> z)
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
void s.insert(T x)
bool s.erase(T x)
bool s.erase_all(T x)
```
* eraseは要素を一つしか削除しない
* 代わりに、要素をすべて削除する関数erase_allが用意されている
