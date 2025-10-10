#ifdef RHYSKA_LOCAL
#include<all.h>
#define dbg(a) outl<' '>("line",__LINE__,':',#a,'=',a)
#define TIME Timer __timer
#define TIME_END __timer.show()
#else
#include<bits/stdc++.h>
#define dbg(a)
#define TIME
#define TIME_END
#endif
using namespace std;
using ll=long long;using ld=long double;using ull=unsigned long long;
template<class T>using V=vector<T>;
template<class T>using gpq=priority_queue<T,V<T>,greater<T>>;
template<class T>using lpq=priority_queue<T>;
#define CH5(a,b,c,d,e,...) e
#define rep4(i,a,b,s) for(ll i=(a),i##REPEND=(ll)(b),i##REPSTEP=(ll)(s);i<i##REPEND;i+=i##REPSTEP)
#define rep3(i,a,b) for(ll i=(a),i##REPEND=(ll)(b);i<i##REPEND;++i)
#define rep2(i,b) rep3(i,0,b)
#define rep1(b) rep3(REPCNT_##__COUNTER__,0,b)
#define rep(...) CH5(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define rrep3(i,a,b,s) for(ll i=(a),i##REPEND=(ll)(b),i##REPSTEP=(ll)(s);i>=i##REPEND;i-=i##REPSTEP)
#define rrep2(i,a,b) for(ll i=(a),i##REPEND=(ll)(b);i>=i##REPEND;--i)
#define rrep1(i,b) rrep2(i,b,0)
#define rrep(...) CH5(__VA_ARGS__,rrep3,rrep2,rrep1,rep)(__VA_ARGS__)
#define YES {cout<<"Yes\n";return;}
#define NO {cout<<"No\n";return;}
#define drop(...) {outl(__VA_ARGS__);return;}
#define unless(a) if(!(a))
#define ever (;;)
#define All(a) begin(a),end(a)
#define rAll(a) (a).rbegin(),(a).rend()
#define Sort(a) sort(All(a))
#define rSort(a) sort(rAll(a))
#define Rev(a) reverse(All(a))
#define Uniq(a) Sort(a),a.erase(unique(All(a)),end(a))
#define eb emplace_back
#define VV(T,a,h,...) V<V<T>>a(h,V<T>(__VA_ARGS__))
namespace io_helper{
	template<class T>void scan(T&a){cin>>a;}
	template<class S,class T>void scan(pair<S,T>&p){scan(p.first);scan(p.second);}
	template<class... T>void scan(tuple<T...>&t){apply([](auto&...s){(scan(s),...);},t);}
	template<class T>void scan(V<T>&a){for(auto&&x:a)scan(x);}
	template<class T>void print(const T&a){cout<<a;}
	template<class S,class T>void print(const pair<S,T>&p){print(p.first);print(' ');print(p.second);}
	template<class... T>void print(const tuple<T...>&t){apply([](const auto&...s){bool f=1;((f?(void)(f=0):print(' '),print(s)),...);},t);}
	template<class T>void print(const V<T>&a){if(a.size()){print(a[0]);for(auto i=a.begin();++i!=a.end();){print(' ');print(*i);}}}
	template<class T>void print(const V<V<T>>&a){if(a.size()){print(a[0]);for(auto i=a.begin();++i!=a.end();){print('\n');print(*i);}}}
}
void in(){}
template<class S,class... B>void in(S&s,B&... b){io_helper::scan(s);in(b...);}
void put(){}
template<class T>void put(const T&a){io_helper::print(a);}
template<class S,class... B>void put(const S&s,const B&... b){io_helper::print(s);put(b...);}
void putl(){io_helper::print('\n');}
template<class T>void putl(const T&a){io_helper::print(a);io_helper::print('\n');}
template<class S,class... B>void putl(const S&s,const B&... b){io_helper::print(s);putl(b...);}
template<char c=' '>void out(){}
template<char c=' ',class T>void out(const T&a){io_helper::print(a);}
template<char c=' ',class S,class... B>void out(const S&s,const B&... b){io_helper::print(s);io_helper::print(c);out<c>(b...);}
template<char c='\n'>void outl(){io_helper::print('\n');}
template<char c='\n',class T>void outl(const T&a){io_helper::print(a);io_helper::print('\n');}
template<char c='\n',class S,class... B>void outl(const S&s,const B&... b){io_helper::print(s);io_helper::print(c);outl<c>(b...);}
template<class S,class T>inline bool chmin(S&a,T b){return(a>b?a=b,1:0);}
template<class S,class T>inline bool chmax(S&a,T b){return(a<b?a=b,1:0);}
template<class... T>constexpr auto min(T... a){return min(initializer_list<common_type_t<T...>>{a...});}
template<class... T>constexpr auto max(T... a){return max(initializer_list<common_type_t<T...>>{a...});}
template<class T>constexpr T sum(const V<T>&s){T a{};for(auto&&x:s)a+=x;return a;}
template<class T> string LZ(T s,int l){string res=to_string(s);Rev(res);while((int)res.size()<l){res+='0';}Rev(res);return res;}
template<class T> V<T> vgen(int n,const T&g){return V<T>(n,g);}
template<class... B>auto vgen(int n,const B&...v){auto g=vgen(v...);return V<decltype(g)>(n,move(g));}
template<class T> V<T> rvgen(int n){return V<T>(n);}
template<class T,class... B>auto rvgen(int n,const B&...v){auto g=rvgen<T>(v...);return V<decltype(g)>(n,move(g));}
template<class T=ll>T geti(){T s;cin>>s;return s;}
string gets(){return geti<string>();}
