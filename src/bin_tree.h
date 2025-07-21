#pragma once
#include <vector>
template<class T>class bin_tree{
public:
	bin_tree(int _n=0):n(_n),d(_n+1){}
	void add(int i,T x){for(i++;i<=n;i+=i&-i)d[i]+=x;}
	T sum(int l, int r){return sum(r-1)-sum(l-1);}
	T sum(int i){
		T s=0;
		for(++i;i;i-=i&-i)s+=d[i];
		return s;
	}
private:
	int n;
	std::vector<T> d;
};
