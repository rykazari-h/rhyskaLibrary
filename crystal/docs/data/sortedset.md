# Sortedset
## このクラスについて
ランダムアクセスが可能であるset。参考はtatyam氏の[SortedSet](https://github.com/tatyam-prime/SortedSet/tree/main)  
crystalはポインタに関して自由度が低く、機能は制限された。例えば、iteratorは実装されていない。
## constructor
```crystal
Sortedlist(T).new;
Sortedlist(T).new(z : Array(T));
```
## method
* `empty?` empty?
* `size` size
* `clear` clear
* `insert or <<` 挿入できたらtrue
* `togle` 挿入できたらtrue
* `erase` 削除できたらtrue
* `pop` erase and return maximam element
* `count` boolをかえす(下と同様)
* `find or contains` self has the element?
* `[Int32]`,`[Tuple(Int32,Int32)]` Tupleによるアクセスは`@container[first][last]`を表す
* `[]=` 使用者が責任を持って、配列を直接変更する
* `a` 内部配列をそのまま返す
* `lower_bound`,`upper_bound` Tuple(outer,inner)を返す
* `index`,`index_rg` intを返す
