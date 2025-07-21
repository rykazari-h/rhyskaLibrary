# Segment tree
## 実装について
内部では、配列長を2ベキにしている。  
区間の積は非再帰で実装している。
## constructor
```cpp
segtree<Tp, mul, base> s(int n)
segtree<Tp, mul, base> s(std::vector<Tp> v)
```
* segtree(int n)はsegtree(std::vector<Tp>(n, base())を呼ぶ
* O(n)
## set
```cpp
void s.set(int t, Tp x)
```
* s[t]にxを代入する
* O(logn)
## operator[]
```cpp
Tp s[int t]
```
* O(1)
## operator()
```cpp
Tp s(int l, int r)
```
* [l, r)の積を返す
* O(logn)
## get_all
```cpp
Tp s.get_all()
```
* 全要素の積を返す
* O(1)
## right_bound
```cpp
int s.right_bound(F f, int l)
```
* l以上のインデックスのうち、nもしくはrを1増やしたときfがtrueからfalseとなるrの値のうちいずれか一つを返す。特にfが単調であるとき、mul[l, r)がtrueとなる最大のrを返す。
* O(logn)
## left_bound
```cpp
int s.left_bound(F f, int r)
```
* r以下のインデックスのうち、0もしくはlを1減らしたときfがtrueからfalseとなるlの値のうちいずれか一つを返す。特にfが単調であるとき、mul[l, r)がtrueとなる最小のlを返す。
* O(logn)

