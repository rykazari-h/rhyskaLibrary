#include<vector>
#include<algorithm>

#if __cplusplus>=201703L
template<class T,auto mul,T base>
#else
template<class T,T (*mul)(T,T),T base>
#endif
class segtree{
public:
	explicit segtree(int n=0):segtree(std::vector<T> (n,base)){}
	explicit segtree(const std::vector<T> &v):n(1){
		int sz=v.size();
		for(;n<sz;n<<=1);
		d=std::vector<T>(n<<1,base);
		for(int i=0;i<sz;i++)d[i+n]=v[i];
		for(int i=n-1;i;i--)d[i]=mul(d[i<<1],d[i<<1|1]);
	}

	//tにxを代入します
	void set(int t,T x){
		d[t+=n]=x;
		for(;t>>=1;)d[t]=mul(d[t<<1],d[t<<1|1]);
	}

	//tの値を取得します
	T operator[](int t)const{
		return d[t+n];
	}
	//[l,r)の積を取得します
	T operator()(int l,int r)const{
		if(l==0&&r==n)return get_all();
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
private:
	//d.size/2
	int n;
	//1-indexed
	std::vector<T>d;
};
