# treapmap
treapによるstd::mapの模倣  
```crystal
map = Map(K, V).new ->{V.new}
# 以下のメソッドはイテレータを返す
map.head; map.tail; map.lower_bound; map.upper_bound
map.keys
map.values
map.to_a
```
