# rhyskaLibrary
主に競プロで使うためのもの  
ひまつぶしでもある
## 実装されているもの-cpp
### data
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|unionfind|[dsu.h](src/data/dsu.h)|[dsu.md](docs/data/dsu.md)|
|ポテンシャル付きunionfind|[weighted_dsu.h](src/data/weighted_dsu.h)|[weighted_dsu.md](docs/data/weighted_dsu.md)|
|binary indexed tree|[bin_tree.h](src/data/bin_tree.h)|[bin_tree.md](docs/data/bin_tree.md)|
|segment tree|[segtree.h](src/data/segtree.h)|[segtree.md](docs/data/segtree.md)|
|平方分割set|[kthset.h](src/data/kthset.h)|[kthset.md](docs/data/kthset.md)|
|平方分割multiset|[kthmultiset.h](src/data/kthmultiset.h)|[kthmultiset.md](docs/data/kthmultiset.md)|
|modint(montgomery)|[modint.h](src/data/modint.h)|[modint.md](docs/data/modint.md)|
|modint(barrett-reduction)|[fmodint.h](src/data/fmodint.h)|[fmodint.md](docs/data/fmodint.md)|
|多倍長整数|[Integer.h](src/data/Integer.h)|実装中...|
### math
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|素因数分解|[prime.h](src/math/prime.h)|[prime.md](docs/math/prime.md)|
|素数列挙|[fast_prime.h](src/math/fast_prime.h)|[fast_prime.md](docs/math/fast_prime.md)|
|math utility|[math.h](src/math/math.h)|[math.md](docs/math/math.md)|
### algorithm
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|座標圧縮|[cc.h](src/algo/cc.h)|[cc.md](docs/algo/cc.md)|
|線分交差判定|[intersect.h](src/algo/intersect.h)|[intersect.md](docs/algo/intersect.md)|
|lps|[lps.h](src/algo/lps.h)|[lps.md](docs/algo/lps.md)|
### etc
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|help|[all.h](src/all.h)|_|
|template|[template.h](src/template.h)|_|
|header|[header.h](src/header.h)|[header.md](docs/header.md)|
## crystal
### data
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|heap|[heap.cr](crystal/src/data/heap.cr)|[heap.md](crystal/docs/data/heap.md)|
|unionfind|[dsu.cr](crystal/src/data/dsu.cr)|[dsu.md](crystal/docs/data/dsu.md)|
|順序付き集合|[sortedset.cr](crystal/src/data/sortedset.cr)|[sortedset.md](crystal/docs/data/sortedset.md)|
|順序付き多重集合|[sortedlist.cr](crystal/src/data/sortedlist.cr)|[sortedlist.md](crystal/docs/data/sortedlist.md)|
|順序付き集合|[treapset.cr](crystal/src/data/treapset.cr)|[treapset.md](crystal/docs/data/treapset.md)|
|順序付き多重集合|[treap.cr](crystal/src/data/treap.cr)|[treap.md](crystal/docs/data/treap.md)|
|連想配列|[map.cr](crystal/src/data/map.cr)|[map.md](crystal/docs/data/map.md)|
### etc
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|header|[header.cr](crystal/src/header.cr)|[header.md](crystal/docs/header.md)|
|array|[array.cr](crystal/src/array_ext.cr)|[array.md](crystal/docs/array.md)|
|入出力|[ioset.cr](crystal/src/ioset.cr)|[ioset.md](crystal/docs/ioset.md)|
|template|[template.cr](crystal/src/template.cr)|_|
