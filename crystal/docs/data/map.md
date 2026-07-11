# map
tatyamsetによるstd::mapの模倣  
included module : Iterable({K, V}), Enumerable({K, V})  
```crystal
map = Map(K, V).new(default)
map = Map(K, V).zip(Array(K), Array(V))
map == other_map
map.empty?
map.clear
map.clone; map.dup
map[k] = v
map[k] # defaultを返す
map[k]? # nilを返す
map.delete(x) # erase(x)
map.erase(key : K) : V?
map.erase(it : Map(K, V)::MapIterator(K, V)) : {K, V}?
map.each # iter
map.each(& : {K, V} ->)
map.each_key(& : K ->)
map.each_value(& : V ->)
map.count(key : K) # has_key?(Key)
map.has_key?(key : K)
map.keys # array of keys
map.values # array of values
map.data # => {key, val} これは生データ(Array)
map.to_a # array of {K, V}
map.pop(idx = -1) : {K, V} # idx番目を消去
map.kth(idx) : {K, V}  # idx番目を返す
map.lower_bound(key : K) : Iter # lower_bound
map.upper_bound(key : K) : Iter # upper_bound
map.index(key : K) : Int32 # lower_bound
map.index_rg(key : K) : Int32 # upper_bound
it = map.each # map.headに同じ
it.pos : {Int32, Int32} # => {outer, inner}
it.key; it.val # key, val
it.value # {key, val}
it.advance(n) # n進める
it + n
it - other_it # ベクトル量
it <=> other_it
```
