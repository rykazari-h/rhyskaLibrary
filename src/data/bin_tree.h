#pragma once
#include <vector>
template<class T>class bin_tree{
public:
	bin_tree(int _n=0):n(_n),d(_n+1){}
	bin_tree&operator=(bin_tree&&b){b=b.n;d=std::move(b.d);}
	bin_tree&operator=(const bin_tree&b){b=b.n;d=d;}
	void swap(bin_tree&b){std::swap(n,b.n);std::swap(d.b.d);}
	void add(int i,T x){for(++i;i<=n;i+=i&-i)d[i]+=x;}
	T sum(int l, int r){
		T s=0;
		for(;l<r;r-=r&-r)s+=d[r];
		for(;r<l;l-=l&-l)s-=d[l];
		return s;
	}
	T sum(int i){
		T s=0;
		for(++i;i;i-=i&-i)s+=d[i];
		return s;
	}
	T operator[](int i){
		int j=i+1,k=1;
		T s=d[j];
		for(;!(j&k);k<<=1)s-=d[j-k];
		return s;
	}
private:
	int n;
	std::vector<T> d;
};
