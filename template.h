#ifdef RHYSKA_LOCAL
#include"all.h"
#define dbg(a) {out<' '>("line",__LINE__,':',#a,'=',a);}
#define TIME Timer __timer
#define TIME_END __timer.show()
#else
#include<bits/stdc++.h>
#define dbg(a) 0
#define TIME 0
#define TIME_END 0
#endif
using
namespace
std;
using ll=long long;
using ld=long double;
using ull=unsigned long long;
template<class T>using V=vector<T>;
template<class T>using gpq=priority_queue<T,V<T>,greater<T>>;
template<class T>using lpq=priority_queue<T>;
#define CH5(a,b,c,d,e,...) e
#define rep4(i,a,b,s) for(ll i=(a),i##REPEND=(ll)(b),i##REPSTEP=(ll)(s);i<i##REPEND;i+=i##REPSTEP)
#define rep3(i,a,b) for(ll i=(a),i##REPEND=(ll)(b);i<i##REPEND;i++)
#define rep2(i,b) rep3(i,0,b)
#define rep1(b) rep3(REPCNT_##__COUNTER__,0,b)
#define rep(...) CH5(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define rrep3(i,a,b,s) for(ll i=(a),i##REPEND=(ll)(b),i##REPSTEP=(ll)(s);i>=i##REPEND;i-=i##REPSTEP)
#define rrep2(i,a,b) for(ll i=(a),i##REPEND=(ll)(b);i>=i##REPEND;i--)
#define rrep1(i,b) rrep2(i,b,0)
#define rrep(...) CH5(__VA_ARGS__,rrep3,rrep2,rrep1,rep)(__VA_ARGS__)
#define YES {cout<<"Yes\n";return;}
#define NO {cout<<"No\n";return;}
#define drop(...) {out(__VA_ARGS__);return;}
#define Yn(a) cout<<((a)?"Yes\n":"No\n")
#define unless(a) if(!(a))
#define All(a) begin(a),end(a)
#define rAll(a) (a).rbegin(),(a).rend()
#define Sort(a) sort(All(a))
#define rSort(a) sort(rAll(a))
#define Rev(a) reverse(All(a))
#define Uniq(a) Sort(a),a.erase(unique(All(a)),end(a))
#define eb emplace_back
#define INT(...) int __VA_ARGS__;in(__VA_ARGS__)
#define LL(...) ll __VA_ARGS__;in(__VA_ARGS__)
#define ULL(...) ull __VA_ARGS__;in(__VA_ARGS__)
#define LD(...) ld __VA_ARGS__;in(__VA_ARGS__)
#define STR(...) string __VA_ARGS__;in(__VA_ARGS__)
#define CHR(...) char __VA_ARGS__;in(__VA_ARGS__)
#define VEC(T,a,s) V<T>a(s);in(a)
#define VVEC(T,a,h,w) V<V<T>>a(h,V<T>(w));in(a)
#define VV(T,a,h,...) V<V<T>>a(h,V<T>(__VA_ARGS__))
namespace io_helper{
	template<class T>void scan(T&a){cin>>a;}
	template<class S,class T>void scan(pair<S,T>&p){scan(p.first);scan(p.second);}
	template<class T>void scan(V<T>&a){for(auto&&x:a)scan(x);}
	template<class T>void print(const T&a){cout<<a;}
	template<class S,class T>void print(const pair<S,T>&p){print(p.first);print(' ');print(p.second);}
	template<class T>void print(const V<T>&a){if(a.size()){print(a[0]);for(auto i=a.begin();++i!=a.end();){print(' ');print(*i);}}}
	template<class T>void print(const V<V<T>>&a){if(a.size()){print(a[0]);for(auto i=a.begin();++i!=a.end();){print('\n');print(*i);}}}
}
void in(){}
template<class S,class... B>void in(S&s,B&... b){io_helper::scan(s);in(b...);}
template<char c='\n'>void out(){io_helper::print('\n');}
template<char c='\n',class T>void out(const T&a){io_helper::print(a);io_helper::print('\n');}
template<char c='\n',class S,class... B>void out(const S&s,const B&... b){io_helper::print(s);io_helper::print(c);out<c>(b...);}
template<class S,class T>inline bool chmin(S&a,T b){return(a>b?a=b,1:0);}
template<class S,class T>inline bool chmax(S&a,T b){return(a<b?a=b,1:0);}
template<class... T>constexpr auto min(T... a){return min(initializer_list<common_type_t<T...>>{a...});}
template<class... T>constexpr auto max(T... a){return max(initializer_list<common_type_t<T...>>{a...});}
template<class T> string LZ(T s,int l){string res=to_string(s);Rev(res);while((int)res.size()<l){res+='0';}Rev(res);return res;}
template<class T=ll>T geti(){T s;cin>>s;return s;}
string gets(){return geti<string>();}
void _main();int main(){cin.tie(0);ios::sync_with_stdio(0);cout<<fixed<<setprecision(12);
//rep(geti())
_main();}
using pp=pair<ll,ll>;
void _main(){
