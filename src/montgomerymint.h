#pragma once
#include <type_traits>
template<auto P_>class montgomerymint{
	using S=std::make_signed_t<decltype(P_)>;using U=std::conditional_t<sizeof(S)<=4,unsigned,unsigned long long>;using D=std::conditional_t<sizeof(U)==4,unsigned long long,__uint128_t>;
	inline constexpr static U uinv(U x){U y=x;for(int i=6;i--;)y*=2-x*y;return y;}
	constexpr static U P=P_,P2=P<<1,R=-uinv(P),R2=-(D)P%P;U v;
	inline constexpr static U reduce(D x){return (x+(U)x*R*(D)P)>>(sizeof(U)*8);}
	inline constexpr montgomerymint(U x,int):v(x){} 
	public:
	inline constexpr static S mod(){return P;}
	inline constexpr static U umod(){return (U)P;}
	inline constexpr montgomerymint():v(0){}
	inline constexpr montgomerymint(const montgomerymint&x):v(x.v){}
	template<class T>inline constexpr montgomerymint(T x):v(reduce((D)(x%P+P)*R2)){}
	inline constexpr S val()const{U x=reduce(v);return (x-P)>>(sizeof(U)*8-1)?x:x-P;}
	template<class T>inline constexpr operator T()const{return val();}
	inline constexpr friend bool operator==(const montgomerymint&x,const montgomerymint&y){return x.val()==y.val();}
	inline constexpr friend bool operator!=(const montgomerymint&x,const montgomerymint&y){return x.val()!=y.val();}
	inline constexpr montgomerymint&operator=(const montgomerymint&x){v=x.v;return *this;}
	inline constexpr montgomerymint&operator++(){return *this+=1;}
	inline constexpr montgomerymint operator++(int){montgomerymint x=*this;++*this;return x;}
	inline constexpr montgomerymint&operator--(){return *this-=1;}
	inline constexpr montgomerymint operator--(int){montgomerymint x=*this;--*this;return x;}
	inline constexpr montgomerymint operator-()const{return montgomerymint(v?P2-v:0,0);}
	inline constexpr montgomerymint&operator+=(const montgomerymint&x){v+=x.v,(v-P2)>>(sizeof(U)*8-1)||(v-=P2);return*this;}
	inline constexpr montgomerymint&operator-=(const montgomerymint&x){v-=x.v,v>>(sizeof(U)*8-1)&&(v+=P2);return*this;}
	inline constexpr montgomerymint&operator*=(const montgomerymint&x){v=reduce((D)v*x.v);return*this;}
	inline constexpr montgomerymint&operator/=(const montgomerymint&x){return*this*=x.inv();}
	inline constexpr friend montgomerymint operator+(montgomerymint x,const montgomerymint&y){return x+=y;}
	inline constexpr friend montgomerymint operator-(montgomerymint x,const montgomerymint&y){return x-=y;}
	inline constexpr friend montgomerymint operator*(montgomerymint x,const montgomerymint&y){return x*=y;}
	inline constexpr friend montgomerymint operator/(montgomerymint x,const montgomerymint&y){return x/=y;}
	template<class T>inline constexpr montgomerymint pow(T y)const{montgomerymint x=*this,z=1;while(y){if(y&1)z*=x;if(y>>= 1)x*= x;}return z;}
	template<class T>inline constexpr friend montgomerymint pow(const montgomerymint&x,T y){return x.pow(y);}
	inline constexpr montgomerymint inv()const{U a=val(),b=P;using T=std::make_signed_t<U>;T x=1,y=0;while(b){U q=a/b,t=a-q*b;a=b;b=t;T t1=x-(T)q*y;x=y;y=t1;}if(x<0)x+=(T)P;return montgomerymint((U)x);}
	inline constexpr friend montgomerymint inv(const montgomerymint&x){return x.inv();}
	inline friend std::istream&operator>>(std::istream &is,montgomerymint&x){S y;is>>y,x=y;return is;}
	inline friend std::ostream&operator<<(std::ostream &os,const montgomerymint&x){return os<<x.val();}
};
