# array_ext
快適にarrayを扱うためのもの
```crystal
arr.reserve(cap) # 要領をcap以上にする
arr.unsafe_reserve(size) # 長さをsizeにする。拡張された部分はuninitialzied
arr.reserve(size, val) # 拡張部分はvalで埋められる
arr.unique! # c++のuniqueと同じ挙動
arr.reverse!(l : Int | Pointer(T), r) # [l, r)をreverse
arr.next_permutation(l = 0, r = size) : Bool # 破壊的
arr.prev_permutation(l = 0, r = size) : Bool # 破壊的
```
