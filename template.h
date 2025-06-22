#ifdef RHYSKA_LOCAL
#include "all.h"
#else
#include <bits/stdc++.h>
#endif
using namespace std;
//typedef
using ll=long long;
using ld=long double;
using ull=unsigned long long;
template<class T>using V=vector<T>;
template<class T>using gpq=priority_queue<T,V<T>,greater<T>>;
template<class T>using lpq=priority_queue<T>;
#define CALL5(a,b,c,d,e,...) e
#define rep4(i,a,b,s) for(ll i=(a),i##emacro=(ll)(b),i##smacro=(ll)(s);i<i##emacro;i+=i##smacro)
#define rep3(i,a,b) for(ll i=(a),i##emacro=(ll)(b);i<i##emacro;i++)
#define rep2(i,b) rep3(i,0,b)
#define rep1(b) rep3(imacro_##__COUNTER__,0,b)
#define rep(...) CALL5(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define rrep3(i,a,b,s) for(ll i=(a),i##emacro=(ll)(b),i##smacro=(ll)(s);i>=i##emacro;i-=i##smacro)
#define rrep2(i,a,b) for(ll i=(a),i##emacro=(ll)(b);i>=i##emacro;i--)
#define rrep1(i,b) rrep2(i,b,0)
#define rrep(...) CALL5(__VA_ARGS__,rrep3,rrep2,rrep1,rep)(__VA_ARGS__)
//judge
#define YES {cout<<"Yes\n";return;}
#define NO {cout<<"No\n";return;}
#define Yn(a) cout<<((a)?"Yes\n":"No\n");
#define unless(a) if(!(a))
//iterator/vec
#define All(a) begin(a),end(a)
#define rAll(a) (a).rbegin(),(a).rend()
#define Sort(a) sort(All(a))
#define rSort(a) sort(rAll(a))
#define Rev(a) reverse(All(a))
#define Uniq(a) Sort(a),a.erase(unique(All(a)),end(a))
#define eb emplace_back
//declare/IO
#define INT(...) int __VA_ARGS__;in(__VA_ARGS__)
#define LL(...) ll __VA_ARGS__;in(__VA_ARGS__)
#define ULL(...) ull __VA_ARGS__;in(__VA_ARGS__)
#define LD(...) ld __VA_ARGS__;in(__VA_ARGS__)
#define STR(...) string __VA_ARGS__;in(__VA_ARGS__)
#define CHR(...) char __VA_ARGS__;in(__VA_ARGS__)
#define VEC(T,a,s) V<T>a(s);in(a)
#define VV(T,a,h,w) V<V<T>>a(h,V<T>(w));in(a)
namespace io_helper{
	//stdin
	template<class T>void scan(T&a){cin>>a;}
	template<class S,class T>void scan(pair<S,T>&p){scan(p.first);scan(p.second);}
	template<class T>void scan(vector<T>&a){for(auto&&x:a)scan(x);}
	//stdout
	template<class T>void print(const T&a){cout<<a;}
	template<class S,class T>void print(const pair<S,T>&p){print(p.first);print(' ');print(p.second);}
	template<class T>void print(const vector<T>&a){if(a.size()){print(a[0]);for(auto i=a.begin();++i!=a.end();){print(' ');print(*i)}}}
}
void in(){}
template<class S,class... B>void in(S&s,B&... b){io_helper::scan(s);in(b...);}
void out(){io_helper::print('\n');}
template<class T>void out(const T&a){io_helper::print(a);io_helper::print('\n');}
template<class S,class... B>void out(const S&s,const B&... b){io_helper::print(s);io_helper::print(' ');out(b...);}
//util
template<class S,class T>inline bool chmin(S&a,T b){return(a>b?a=b,1:0);}
template<class S,class T>inline bool chmax(S&a,T b){return(a<b?a=b,1:0);}
template<class... T>constexpr auto min(T... a){return min(initializer_list<common_type_t<T...>>{a...});}
template<class... T>constexpr auto max(T... a){return max(initializer_list<common_type_t<T...>>{a...});}
template<class T> string LZ(T s,int l){//fix leading zero
	string res;if(s==0)res="0";
	while(s)res+=char(s%10+48);
	while((int)res.size()<l)res+='0';
	Rev(res);return res;
}
template<class T=ll>T geti(){T s;cin>>s;return s;}
template<class T=string>T gets(){T s;cin>>s;return s;}
void _main();int main(){cin.tie(0);ios::sync_with_stdio(0);cout<<fixed<<setprecision(12);
//rep(geti())
_main();}
using pp=pair<ll,ll>;
void _main(){
