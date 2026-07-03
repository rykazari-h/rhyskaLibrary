# Binary Indexed Tree
```crystal
# 初期化
z = BIT(T).new(n : Int32) # O(n)
z = BIT(T).new(d : Array(T)) # O(n)
z[k] # アクセス
z.add(k, x) # z[k] += x
z.sum k #[0, k]の和
# [l, l + len), [l, r)の和
z.sum l, len
z[l, len]
z[l...r]
z[l..r]
#二分探索 z.all &.>= 0のときのみ
z.lower_bound(x)
z.upper_bound(x)
```
