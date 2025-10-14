# Sortedlist
## このクラスについて
ランダムアクセスが可能であるmultiset。参考はtatyam氏の[SortedMultiset](https://github.com/tatyam-prime/SortedSet/tree/main)  
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
* `insert of <<` insert
* `erase` erase one element
* `erase_all` erase all element
* `pop` erase and return maximam element
* `count` count of the element
* `find or contains` self has the element?
* `[Int32]`,`[Tuple(Int32,Int32)]` Tupleによるアクセスは`@container[first][last]`を表す
* `[]=` Tupleのみを引数とする
* `a` 内部配列をそのまま返す
* `lower_bound`,`upper_bound` Tuple(outer,inner)を返す
* `index`,`index_rg` intを返す
