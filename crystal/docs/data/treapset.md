# TreapSet
## このクラスについて
ランダムアクセスが可能であるset。  
大体の操作がO(logN)になっているので、定数倍に注意が必要である。  
挿入等の操作はBoolを返す
## constructor
```crystal
# Procは、例えば総和を取得したいとき->(a:T,b:T){a+b}とする
# 渡さないことも可能である
Treap(T).new(Proc(T,T,T))
```
## method
* `head` begin(O(logN))
* `tail` end(O(1))
* `Iterator::v` value(読み取り専用)
* `empty?` empty?
* `size` size
* `clear` clear
* `clone` O(N)
* `insert or <<` insert
* `erase` 高々1つの要素を削除する
* `toggle` 挿入できたときtrueを、そうでないときfalseを返す
* `pop` k番目の要素を削除する
* `[]` k番目の要素にアクセスする
* `[l,r]` l...rの総積を取得する
* `count` 要素数をカウントする
* `find` 存在するならtrueを返す
* `to_a` flattenして返す(O(N))
* `lower_bound`,`upper_bound` Iteratorを返す
* `index`,`index_rg` intを返す
* `split` [<x],[x<=]に分割する
* `splitl` [<=x],[x<]に分割する
* `spliti` [...k],[k..]に分割する
