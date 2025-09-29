# barrett-reduction modint
[Code](../../src/data/fmodint.h)  
乗算はbarret-reductionで実装されています。
## constructor
```cpp
fmodint<id> x()
fmodint<id> x(unsigned x_)
```
* idをつけることで、複数modを同時に使うことができる。
## utility
```cpp
static unsigned mod()
static setmod(unsigned x)
unsigned x.val()
```
* setmodについて、x<=1e9。
## else
```cpp
mint x.inv()
mint x.pow(U y)
```
* O(log mod, y)  
その他演算は、除算のみO(log mod)  
その他は定数時間
