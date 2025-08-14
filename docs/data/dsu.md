# Disjoint set union
## constructor
```cpp
dsu uf(int n)
``` 
* O(n)
## merge
```cpp
bool uf.merge(int u, int v)
```
* 新規に併合できたときtrueを返す
* ならしO(α(n))
## same
```cpp
bool uf.same(int u, int v)
```
* 連結ならtrueを返す
* ならしO(α(n))
## root
```cpp
int uf.root(int u)
```
* 連結成分の根を返す
* ならしO(α(n))
## size
```cpp
int uf.size(int u)
```
* 連結成分の要素数を返す
* ならしO(α(n))
## size
```cpp
int uf.size()
```
* 連結成分の個数を返す
* groups().size()に等しい
* O(n)
## groups
```cpp
std::vector<std::vector<int>> uf.groups()
```
* グラフを連結成分ごとに分けて返す
* O(n)
