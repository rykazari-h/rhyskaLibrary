# intersect
[Code](../../src/algo/intersect.h)  
線分の交差判定
```cpp
using P = pair<int, int>;
//firstがx,secondがy
bool intersect(P a, P b, P c, P d);
//線分abと線分cdの交差判定
```
* O(1)
* 備考:intersct::subが定義されている。
