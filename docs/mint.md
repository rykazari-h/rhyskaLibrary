# modint
S : modの型  
T : 内部の型(unsigned)
## constructor
```cpp
mint<mod> x()
mint<mod> x(U x_)
```
* O(1)
## utility
```cpp
static S mod()
static T umod()
S x.val()
```
* O(1)
## else
```cpp
mint x.inv()
mint x.mpow(U y)
```
* O(log mod, y)  
その他演算は、除算のみO(log mod)  
その他は定数時間
