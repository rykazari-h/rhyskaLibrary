# BinaryHeap
二分ヒープ。Gpq(昇順に取り出す),Lpq(降順に取り出す)も同様に定義される。  
## constructor
```crystal
Lpq(T).new;
Gpq(T).new;
BinaryHeap(T).new(Proc(T,T,Bool));
```
## method
* `copy` ... deep copy
* `empty?` ... empty?
* `size` ... data size
* `a` ... data container(Array(T))
* `push or <<` ... add element
* `pop` ... discard and return top
* `top` ...top
* popはO(logN),pushは最悪O(logN)
