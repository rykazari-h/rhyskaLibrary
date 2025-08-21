#pragma once
#include<vector>
#include<algorithm>
template<class T,auto mul,auto base>class segtree{
public:
	segtree(int n=0):segtree(std::vector<T> (n,base())){}
	segtree(const std::vector<T> &v):n(1),sz(v.size()){
		for(;n<sz;n<<=1);
		d=std::vector<T>(n<<1,base());
		for(int i=0;i<sz;++i)d[i+n]=v[i];
		for(int i=n-1;i;--i)d[i]=mul(d[i<<1],d[i<<1|1]);
	}
	void swap(segtree&b){std::swap(n,b.n);std::swap(sz,b.sz);std::swap(d,n.d);}
	segtree&operator=(segtree&&b){n=b.n;sz=b.sz;d=std::move(b.d);return*this;}
	segtree&operator=(const segtree&b){n=b.n;sz=b.sz;d=n.d;return*this;}
	void set(int t,T x){for(d[t+=n]=x;t>>=1;)d[t]=mul(d[t<<1],d[t<<1|1]);}
	T operator[](int t)const{return d[t+n];}
	T operator()(int l,int r)const{
		if(l==0&&r==sz)return get_all();
		T x=base(),y=base();
		for(l+=n,r+=n;l<r;l>>=1,r>>=1){
			if(l&1)x=mul(x,d[l++]);
			if(r&1)y=mul(d[--r],y);
		}
		return mul(x,y);
	}
	T get_all()const{return d[1];}
	template<class F>int right_bound(F f,int l=0)const{
		if(l==sz)return sz;
		l+=n;
		T x=base();
		for(;;){
			for(;!(l&1);l>>=1);
			if(!f(mul(x,d[l]))){
				for(;l<n;)if(f(mul(x,d[l<<=1])))x=mul(x,d[++l]);
				return l-n;
			}
			x=mul(x,d[++l]);
			if((l&-l)==l)return sz;
		}
	}
	template<class F>int left_bound(F f,int r)const{
		if(r==0)return 0;
		r+=n;
		T x=base();
		for(;;){
			for(--r;r>1&&(r&1);r>>=1);
			if(!f(mul(d[r],x))){
				for(;r<n;)if(f(mul(d[r=r<<1|1],x)))x=mul(d[r--],x);
				return r+1-n;
			}
			x=mul(d[r],x);
			if((r&-r)==r)return 0;
		}
	}
private:
	int n;
	int sz;
	std::vector<T>d;
};
