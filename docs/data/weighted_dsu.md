# Weighted dsu
## constructor
```cpp
weighted_dsu<Tp> uf(int n, Tp e=0)
``` 
* ポテンシャルをeにする
* O(n)
## merge
```cpp
bool uf.merge(int u, int v, Tp w=0)
```
* 新規に併合できたときtrueを返す
* u -> vの重みがwとなるように併合する
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
## weight
```cpp
Tp uf.weight(int u)
```
* ノードのポテンシャルを返す
* ならしO(α(n))
## diff
```cpp
Tp uf.diff(int u, int v)
```
* u -> vのポテンシャルの差分を返す
* !same(u,b)のときの動作は未定義
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
