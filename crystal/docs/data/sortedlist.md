# Sortedlist
## このクラスについて
ランダムアクセスが可能であるmultiset。参考はtatyam氏の[SortedSet](https://github.com/tatyam-prime/SortedSet/tree/main)  
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
set.insert(x)
set.erase(x : Iterator | T) # 消したならその要素を、そうでないならnilを返す
set.delete(x) # set.erase(x)
set.erase_all(x) # xを全部消す
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
