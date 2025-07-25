#include<type_traits>
#include<iostream>
template<auto P_>class mint{
	using S=decltype(P_);
	using T=std::conditional_t<std::is_same_v<S,int>,unsigned,unsigned long long>;
	using U=std::conditional_t<std::is_same_v<S,int>,unsigned long long,__uint128_t>;
	static constexpr T uinv(T x){
		T y=x;
		for(int i=0;i<6;++i)y*=2-x*y;
		return y;
	}
	static constexpr T P=P_,P2=P_<<1,R=-uinv(P_),R2=-(U)P_%P_;
	T v;
	static constexpr T reduce(U x){return (x+(T)x*R*(U)P)>>(sizeof(T)*8);}
	constexpr mint(T x,int):v(x){}
	public:
	constexpr mint():v(0){}
	constexpr mint(const mint&x):v(x.v){}
	template<class D>constexpr mint(D x):v(reduce((U)(sizeof(D)>sizeof(T)?x%P:x)*R2)){}
	static constexpr S mod(){return P_;}
	static constexpr T umod(){return P;}
	constexpr S val()const{T x=reduce(v);return x<P?x:x-P;}
	T& raw(){return v;}
	template<class D>constexpr operator D()const{return val();}
	constexpr mint& operator=(const mint&x){v=x.v;return *this;}
	constexpr mint& operator+=(const mint&x){
		v+=x.v;
		if(!((v-P2)>>(sizeof(T)*8-1)))v-=P2;
		return *this;
	}
	constexpr mint& operator-=(const mint&x){
		v-=x.v;
		if(v>>(sizeof(T)*8-1))v+=P2;
		return *this;
	}
	constexpr mint& operator*=(const mint&x){v=reduce((U)v*x.v);return *this;}
	constexpr mint& operator/=(const mint&x){return *this*=x.inv();}
	constexpr mint& operator++(){return *this+=1;}
	constexpr mint operator++(int){mint x=*this;++(*this);return x;}
	constexpr mint& operator--(){return *this-=1;}
	constexpr mint operator--(int){mint x=*this;--(*this);return x;}
	constexpr mint operator-()const{return mint(v?P2-v:0,0);}
	friend constexpr mint operator+(mint x,const mint&y) {return x+=y;}
	friend constexpr mint operator-(mint x,const mint&y) {return x-=y;}
	friend constexpr mint operator*(mint x,const mint&y) {return x*=y;}
	friend constexpr mint operator/(mint x,const mint&y) {return x/=y;}
	friend constexpr bool operator==(const mint&x,const mint&y){return x.val()==y.val();}
	friend constexpr bool operator!=(const mint&x,const mint&y){return x.val()!=y.val();}
	constexpr mint inv()const{
		T a=val(),b=P;
		using Sgn=std::make_signed_t<T>;
		Sgn x=1,y=0;
		while(b){
			T q=a/b;
			T t=a-q*b;
			a=b;b=t;
			Sgn t1=x-(Sgn)q*y;
			x=y;y=t1;
		}
		if(x<0)x+=(Sgn)P;
		return mint((T)x);
	}
	template<class D>constexpr mint mpow(D y)const{
		mint x=*this,z=1;
		for(;y;){
			if(y&1)z*=x;
			if(y>>=1)x*=x;
		}
		return z;
	}
	template<class D>friend constexpr mint mpow(const mint&x,D y){return x.mpow(y);}
	friend constexpr mint inv(const mint&x){return x.inv();}
	friend std::istream& operator>>(std::istream&is,mint&x){S y;is>>y,x=y;return is;}
	friend std::ostream& operator<<(std::ostream&os,const mint&x){return os<<x.val();}
};
