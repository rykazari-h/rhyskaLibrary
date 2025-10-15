# header
気持ちよくコーディングするためのもの  
```crystal
# pt(s) means pointerof(s)
# Bool has def to_i(self?1:0)
vgen(*v);
rvgen(type,*v);
# Arrayを生成する。
#いずれも、v[-1]には元を置くこと
putv(a);#c++のio_helper::printにおなじ
outl(a);#これも同様 sepは"\n",endはputvに依存
max(*a);min(*a); #crystalは配列に対してしか持ってないので
chmax(a : T, b : T);chmin();#c++と同じ挙動だぜー。参照使えないから仕方なくマクロ
copy(obj);#多次元Arrayをdeepcopyする
```
