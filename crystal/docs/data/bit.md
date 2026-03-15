# Binary Indexed Tree
```crystal
# 初期化
z = BIT(T).new(d = Array(T))
# [k] 平均計算量O(1)!!!
z[k]
# [k]にxを加算
z.add(k, x)
# [0, k]の和
z.sum k
# [l, l + len), [l, r)の和
z.sum l, len
z[l, len]
z[l...r]
z[l..r]
```
