#pragma once
#include <type_traits>
#include<iostream>
template<int id>class rmodint{
	using S=long long;using U=unsigned long long;using D=__uint128_t;
	inline static U uinv(U x){U y=x;for(int i=6;i--;)y*=2-x*y;return y;}
	inline static U P,P2,R,R2;
	inline static U reduce(D x){return (x+(U)x*R*(D)P)>>(sizeof(U)*8);}
	public:
	static void setmod(S x){P=x,P2=P<<1,R=-uinv(P),R2=-(D)P%P;}
	inline rmodint(U x,int):v(x){} 
	U v;
	inline static S mod(){return P;}
	inline static U umod(){return (U)P;}
	inline rmodint():v(0){}
	inline rmodint(const rmodint&x):v(x.v){}
	template<class T>inline rmodint(T x):v(reduce((D)(x%P+P)*R2)){}
	inline S val()const{U x=reduce(v);return (x-P)>>(sizeof(U)*8-1)?x:x-P;}
	template<class T>inline operator T()const{return val();}
	inline friend bool operator==(const rmodint&x,const rmodint&y){return x.val()==y.val();}
	inline friend bool operator!=(const rmodint&x,const rmodint&y){return x.val()!=y.val();}
	inline rmodint&operator=(const rmodint&x){v=x.v;return *this;}
	inline rmodint&operator++(){return *this+=1;}
	inline rmodint operator++(int){rmodint x=*this;++*this;return x;}
	inline rmodint&operator--(){return *this-=1;}
	inline rmodint operator--(int){rmodint x=*this;--*this;return x;}
	inline rmodint operator-()const{return rmodint(v?P2-v:0,0);}
	inline rmodint&operator+=(const rmodint&x){v+=x.v,(v-P2)>>(sizeof(U)*8-1)||(v-=P2);return*this;}
	inline rmodint&operator-=(const rmodint&x){v-=x.v,v>>(sizeof(U)*8-1)&&(v+=P2);return*this;}
	inline rmodint&operator*=(const rmodint&x){v=reduce((D)v*x.v);return*this;}
	inline rmodint&operator/=(const rmodint&x){return*this*=x.inv();}
	inline rmodint operator+(const rmodint&y){return rmodint(*this)+=y;}
	inline rmodint operator-(const rmodint&y){return rmodint(*this)-=y;}
	inline rmodint operator*(const rmodint&y){return rmodint(*this)*=y;}
	inline rmodint operator/(const rmodint&y){return rmodint(*this)/=y;}
	template<class T>inline friend rmodint operator+(const T&x,const rmodint&y){return y+x;}
	template<class T>inline friend rmodint operator-(const T&x,const rmodint&y){return rmodint(x)-y;}
	template<class T>inline friend rmodint operator*(const T&x,const rmodint&y){return y*x;}
	template<class T>inline friend rmodint operator/(const T&x,const rmodint&y){return rmodint(x)/y;}
	template<class T>inline rmodint pow(T y)const{rmodint x=*this,z=1;while(y){if(y&1)z*=x;if(y>>= 1)x*= x;}return z;}
	template<class T>inline friend rmodint pow(const rmodint&x,T y){return x.pow(y);}
	inline rmodint inv()const{U a=val(),b=P;using T=std::make_signed_t<U>;T x=1,y=0;while(b){U q=a/b,t=a-q*b;a=b;b=t;T t1=x-(T)q*y;x=y;y=t1;}if(x<0)x+=(T)P;return rmodint((U)x);}
	inline friend rmodint inv(const rmodint&x){return x.inv();}
	inline friend std::istream&operator>>(std::istream &is,rmodint&x){S y;is>>y,x=y;return is;}
	inline friend std::ostream&operator<<(std::ostream &os,const rmodint&x){return os<<x.val();}
};
