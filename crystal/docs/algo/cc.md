# CC
座圧ライブラリ  
```crystal
cc = CC(T).new(d = [] of T, did = false) # did = trueならuniqをかけない
cc.clear # clear
cc.push(x : T | Array(T)) # selfを返す
cc << x # pushに同じ
cc.idx(x) # xのidxを返す。厳密にはlower_bound(x)
cc[i] # i番目の座標
cc.size # 要素数
```
