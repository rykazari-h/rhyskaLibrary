# Disjoint set union
## constructor
```crystal
Dsu(T).new(size : Int32)
```
## method
* `merge` マージできたときtrue
* `size` 連結成分の数
* `size(x)` xの連結成分の大きさ
* `same` 同じ連結成分に属するか
* `root` その連結成分の代表
* `groups` 森
