# Binary indexed tree
[Code](../../src/data/bin_tree.h)
## constructor
```cpp
bin_tree<Tp> s(int n)
```
* O(n)
## add
```cpp
void s.add(int t, Tp x)
```
* s[t]にxを加算する
* O(logn)
## operator[]
```cpp
Tp s[int t]
```
* O(logn)
## sum
```cpp
Tp s(int l, int r)
```
* [l, r)の和を返す
* O(logn)
## sum
```cpp
Tp s.sum(int i)
```
* [0,i]の和を返す
* O(logn)
