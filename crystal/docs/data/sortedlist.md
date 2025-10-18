# Sortedlist
## このクラスについて
ランダムアクセスが可能であるmultiset。参考はtatyam氏の[SortedMultiset](https://github.com/tatyam-prime/SortedSet/tree/main)  
~~crystalはポインタに関して自由度が低く、機能は制限された。例えば、iteratorは実装されていない。~~  
いい感じにiteratorを実装することができた
## constructor
```crystal
Sortedlist(T).new;
Sortedlist(T).new(z : Array(T));
```
## method
* `head` begin
* `tail` end
* `Iterator::v/v=` value
* `empty?` empty?
* `size` size
* `clear` clear
* `insert or <<` insert
* `erase` erase one element
* `erase_all` erase all element
* `pop` erase and return maximam element
* `count` count of the element
* `find or contains` self has the element?
* `[]=` 中身を変える
* `a` 内部配列をそのまま返す
* `lower_bound`,`upper_bound` Iteratorを返す
* `index`,`index_rg` intを返す
