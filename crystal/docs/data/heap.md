# BinaryHeap
二分ヒープ。Gpq(昇順に取り出す),Lpq(降順に取り出す)も同様に定義される。  
## method
```crystal
pq = Lpq(T).new(z : Array(T) = [] of T)
pq = Heap(T).new(z : Array(T) = [] of T) { |a, b| a < b } # compがtrueのときaが上に行く
pq.empty?
pq.size
pq.data # 生配列
pq.to_a # data.dup
pq.clear
pq.reserve(cap)
pq.push(val)
pq << val
pq.top
pq.top?
pq.pop
pq.pop?
```
