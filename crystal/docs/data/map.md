# map
## このクラスについて
c++のstd::map,pythonのdefaultdictを模倣したもの  
内部配列はSortedset(Tuple(Key,Value))
## constructor
```crystal
Map(K,V).new(->{default_value});
# 例えば
Map(Int32, Int32).new ->{0}
```
## method
* `clone` deepcopy
* `head` begin
* `tail` end
* `empty?` empty?
* `size` size
* `clear` clear
* `[]` keyがないとき、keyにdefaule_valueを設定する
* `erase` erase
* `count/find/contains` count
* `lower/upper_bound` iteratorを返す
* `to_a` 配列にして返す
* `keys` keyの列挙
* `values` valueの列挙
