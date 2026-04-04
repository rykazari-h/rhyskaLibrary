# rhyskaLibrary
主に競プロで使うためのもの  
ひまつぶしでもある
## 実装されているもの-cpp
**現在cppコードの整備はされていません**
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
|BIT|[bit.cr](crystal/src/data/bit.cr)|[bit.md](crystal/docs/data/bit.md)|
|Segtree|[segtree.cr](crystal/src/data/segtree.cr)|[segtree.md](crystal/docs/data/segtree.md)|
|LazySegtree|[lazysegtree.cr](crystal/src/data/lazysegtree.cr)|[lazysegtree.md](crystal/docs/data/lazysegtree.md)|
|heap|[heap.cr](crystal/src/data/heap.cr)|[heap.md](crystal/docs/data/heap.md)|
|unionfind|[dsu.cr](crystal/src/data/dsu.cr)|[dsu.md](crystal/docs/data/dsu.md)|
|順序付き集合|[sortedset.cr](crystal/src/data/sortedset.cr)|[sortedset.md](crystal/docs/data/sortedset.md)|
|順序付き多重集合|[sortedlist.cr](crystal/src/data/sortedlist.cr)|[sortedlist.md](crystal/docs/data/sortedlist.md)|
|連想配列|[treapmap.cr](crystal/src/data/treapmap.cr)|[map.md](crystal/docs/data/treapmap.md)|
|LCA|[lca.cr](crystal/src/data/lca.cr)|[lca.md](crystal/docs/data/lca.md)|
|MaxFlow|[maxflow.cr](crystal/src/data/maxflow.cr)|[maxflow.md](crystal/docs/data/maxflow.md)|
|木ィ木ィ|[trie.cr](crystal/src/data/trie.cr)|[trie.md](crystal/docs/data/trie.md)|
|modint|[modint.cr](crystal/src/data/modint.cr)|[modint.md](crystal/docs/data/modint.md)|
|動的modint|[dynamicmodint.cr](crystal/src/data/dynamicmodint.cr)|[dynamicmodint.md](crystal/docs/data/dynamicmodint.md)|
|ロリハ|[rollinghash.cr](crystal/src/data/rollinghash.cr)|[rollinghash.md](crystal/docs/data/rollinghash.md)|
|xorshift|[xorshift.cr](crystal/src/data/xorshift.cr)|[xorshift.md](crystal/docs/data/xorshift.md)|
### math
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|ラグランジュの補完多項式|[LagrangeInterpolation.cr](crystal/src/math/LagrangeInterpolation.cr)|[LagrangeInterpolation.md](crystal/docs/math/LagrangeInterpolation.md)|
|偏角比較|[atan2_cmp.cr](crystal/src/math/atan2_cmp.cr)|[atan2_cmp.md](crystal/docs/math/atan2_cmp.md)|
|NT関数|[math_ext.cr](crystal/src/math/math_ext.cr)|[math_ext.md](crystal/docs/math/math_ext.md)|
|素数篩|[primesieve.cr](crystal/src/math/primesieve.cr)|[primesieve.md](crystal/docs/math/primesieve.md)|
### algo
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|座圧|[cc.cr](crystal/src/algo/cc.cr)|[cc.md](crystal/docs/algo/cc.md)|
|上位集合|[shortage.cr](crystal/src/algo/shortage.cr)|[shortage.md](crystal/docs/algo/shortage.md)|
### etc
|機能|コード|ドキュメント|
|:--|:--:|:--:|
|header|[header.cr](crystal/src/header.cr)|[header.md](crystal/docs/header.md)|
|array|[array_ext.cr](crystal/src/array_ext.cr)|[array_ext.md](crystal/docs/array_ext.md)|
|入出力|[ioset.cr](crystal/src/ioset.cr)|[ioset.md](crystal/docs/ioset.md)|
|template|[template.cr](crystal/src/template.cr)|_|
