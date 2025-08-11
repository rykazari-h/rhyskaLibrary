# bucket_set
## このクラスについて
k番目に小さい要素を取得することを目的としたデータ構造。参考はtatyam氏の[SortedSet](https://github.com/tatyam-prime/SortedSet/tree/main)  
std::setで使える機能はだいたい使える。  
計算量はだいたいO(root(n))
## constructor
```cpp
bucket_set s()
bucket_set s(std::vector<T> z)
```
* 
* O(n logn) (zがソート済みのときO(n))
## iteator::operator+/-
* operator+/-が用意されている
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
