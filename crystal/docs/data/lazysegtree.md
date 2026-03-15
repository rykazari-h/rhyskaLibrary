# Lazy segment tree
```crystal
z = LazySettree(S, F).new(z or n, e, op, mapping, composition)
# Sの配列に対して、Fによって作用する
# z: 初期配列、nは初期配列長
# e: Sの単位元
# op: Sの二項演算 S, S -> S
# mapping: Sに対する作用 F, S -> S
# composition: f, g -> f⚪︎g
z.clone
z.to_a # 外から触れる部分だけを返す z.to_a.size == n
z[k] # k番目の値を返す。代入可能
z[l, len] # 区間積を返す。
z[l...r]
z.apply k, f # 作用
z.apply l, len, f
z.apply l...r, f
z.right_bound k, &f # k以上のインデックスのうち、f z[k...r]がtrueとなる最大のrを返す
z.left_bound k, &f # k以下のインデックスのうち、f z[l...k]がtrueとなる最小のlを返す
```
