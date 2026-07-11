# Sortedset
## このクラスについて
ランダムアクセスが可能であるset。参考はtatyam氏の[SortedSet](https://github.com/tatyam-prime/SortedSet/tree/main)  
included modules : Enumerable(T), Iterable(T)  
```crystal
set = Sortedlist(T).new
set = Sortedlist(T).new(z : Array(T))
set.empty?
set.size
set.clear
set.clone
set.dup
set == other
set | other
set & other
set - other
set ^ other
set.add(x) << x # 追加(selfを返す)
set.add?(x); set.insert(x) # boolを返す
set.erase(x : Iterator | T) # 消せたならtrueを返す
set.delete(x) # set.erase(x)
set.toggle(x) # insertできたならtrueを返す
set === x # set.includes?(x)に同じ
set.includes?(x)
set[k]
set[k] = x # sortedを壊さないように、使用者が責任を持って使用する
set.pop(k) # k番目を消去
set.each #headに同じ
set.each(& : T ->)
set.data # 内部配列
set.to_a # flatten
set.lower_bound # iterator
set.upper_bound
set.index # int
set.index_rg
it = set.head
it = set.tail
it.adbance(n) # n進める
it + n # n進めたもの
it.pos # {outer, inner}
it.value : T
it - other_it # 差分(負の値もとる)
it <=> other_it
```
