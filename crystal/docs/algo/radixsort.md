# radixsort
radixソートを提供するmodule  
bigintは使えない  
```crystal
z = array()
include RadixSort
sort!(z : Array(Int))
sort z
sort_by!(z) { |v| -v }
sort_by z
```
