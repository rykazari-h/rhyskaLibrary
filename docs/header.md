# header
機能の補足  
```cpp
using namespace std;//575
/* type alias
	ll->i64, ld->53bitfloat, ull->u64, V->vector, gpq->greater_heap, lpq->less_heap
*/

//-----macros-----
rep(time);rep(i,end);rep(i,start,end);rep(i,start,end,step);
rrep(i,start);rrep(i,start,end);rrep(i,start,end,step);
//rrepは[start,end]を降順に、repは[start,end)を昇順に走査
//rrep(i,start)=rrep(i,start,0)

//void _main()函数を使うので、return;を使用
#define YES {cout<<"Yes\n";return;}
#define NO {cout<<"No\n";return;}
#define drop(...) {outl(__VA_ARGS__);return;}
#define unless(a) if(!(a))
#define ever (;;)//for everのネタ用
#define All(a) begin(a),end(a)
#define rAll(a) (a).rbegin(),(a).rend()
#define Sort(a) sort(All(a))
#define rSort(a) sort(rAll(a))
#define Rev(a) reverse(All(a))
#define Uniq(a) Sort(a),a.erase(unique(All(a)),end(a))
#define eb emplace_back
#define VV(T,a,h,...) V<V<T>>a(h,V<T>(__VA_ARGS__))

//-----IO-----
namespace io_helper{
	//scan,print for {pair, tuple, vector, anytype}
}
in(args);//入力。引数は参照渡し
put(args),putl(args),out<' '>(args),outl<'\n'>(args);
//出力。outは間に文字を、*lは末尾に改行を置く。

//-----utility-----
bool chmin;bool chmax;//参照
min;max;sum;//vectorに対する函数
vgen(int sizes,T v);rvgen<int>(int sizes);//vector generator
geti();gets();//整数、文字列を受け取る函数
```
