# Disjoint set union
dsu
## method
```crystal
dsu = Dsu.new(n : Int32)
dsu.reset # 辺を消去する
dsu.merge(u, v) # u, vに辺をはる
dsu.root(u) # uが属す連結成分の根
dsu.same(u, v) # uとvが同じ連結成分に属しているか
dsu.size(u) # uが属す連結成分の大きさ
dsu.size # 森の大きさ
dsu.roots # 根の集合
dsu.groups # 森。各成分の列は、頂点番号について昇順
```
