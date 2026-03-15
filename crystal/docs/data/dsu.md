# Disjoint set union
## constructor
```crystal
Dsu(T).new(size : Int32)
```
## method
* `merge` マージできたときtrue
* `size` 連結成分の数 O(1)
* `size(x)` xの連結成分の大きさ
* `same` 同じ連結成分に属するか
* `root` その連結成分の代表
* `groups` 森 各連結成分について、頂点番号の昇順に並ぶ
