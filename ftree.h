#include <vector>
template<class T>struct ftree{
public:
	explicit ftree(int _n=0):n(_n),d(_n+1){}
	//加算
	void add(int i,T x){for(i++;i<=n;i+=i&-i)d[i]+=x;}
	//区間和[l,r)
	T sum(int l, int r){return sum(r-1)-sum(l-1);}
	//累積和
	T sum(int i){
		T s=0;
		for(i++;i;i-=i&-i)s+=d[i];
		return s;
	}
private:
	int n;
	std::vector<T> d;
};
