#include<vector>
#include<algorithm>

template<class T,auto mul,T base>class segtree{
public:
	explicit segtree(int n=0):segtree(std::vector<T> (n,base)){}
	explicit segtree(const std::vector<T> &v):n(1),sz(v.size()){
		for(;n<sz;n<<=1);
		d=std::vector<T>(n<<1,base);
		for(int i=0;i<sz;i++)d[i+n]=v[i];
		for(int i=n-1;i;i--)d[i]=mul(d[i<<1],d[i<<1|1]);
	}

	//tにxを代入します
	void set(int t,T x){
		for(d[t+=n]=x;t>>=1;)d[t]=mul(d[t<<1],d[t<<1|1]);
	}

	//tの値を取得します
	T operator[](int t)const{
		return d[t+n];
	}
	//mul[l,r)を取得します
	T operator()(int l,int r)const{
		if(l==0&&r==sz)return get_all();
		T x=base,y=base;
		for(l+=n,r+=n;l<r;l>>=1,r>>=1){
			if(l&1)x=mul(x,d[l++]);
			if(r&1)y=mul(d[--r],y);
		}
		return mul(x,y);
	}
	//全要素の積を取得します
	T get_all()const{
		return d[1];
	}

	//l以上のインデックスのうち、
	//fが単調のときmul[l,r)がtrueとなる最大のrを返します
	//そうでないときN,もしくはrを1増やした時fがtrueからfalseとなるrの値のうちいずれか一つを返します
	template<class F>
	int find_right(F f,int l=0)const{
		if(l==sz)return sz;
		l+=n;
		T x=base;
		for(;;){
			for(;!(l&1);l>>=1);
			if(!f(mul(x,d[l]))){
				for(;l<n;)if(f(mul(x,d[l<<=1])))x=mul(x,d[l++]);
				return l-n;
			}
			x=mul(x,d[l++]);
			if((l&-l)==l)return sz;
		}
	}

	//r以下のインデックスのうち、
	//fが単調のときmul[l,r)がtrueとなる最小のlを返します
	//そうでないとき0,もしくはlを1へらした時fがtrueからfalseとなるlの値のうちいずれか一つを返します
	template<class F>
	int find_left(F f,int r)const{
		if(r==0)return 0;
		r+=n;
		T x=base;
		for(;;){
			for(r--;r>1&&(r&1);r>>=1);
			if(!f(mul(d[r],x))){
				for(;r<n;)if(f(mul(d[r=r<<1|1],x)))x=mul(d[r--],x);
				return r+1-n;
			}
			x=mul(d[r],x);
			if((r&-r)==r)return 0;
		}
	}
private:
	//2ベキの仮要素数
	int n;
	//要素数(N)
	int sz;
	//1-indexed
	std::vector<T>d;
};
