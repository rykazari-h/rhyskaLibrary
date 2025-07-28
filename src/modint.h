#pragma once
template<auto P_>class modint{
	using S=decltype(P_);using U=std::conditional_t<std::is_same_v<S,int>,unsigned,unsigned long long>;using D=std::conditional_t<std::is_same_v<S,int>,unsigned long long,__uint128_t>;
	inline constexpr static U uinv(U x){U y=x;for(int i=6;i--;)y*=2-x*y;return y;}
	constexpr static U P=P_,P2=P<<1,R=-uinv(P),R2=-(D)P%P;U v;
	inline constexpr static U reduce(D x){return (x+(U)x*R*(D)P)>>(sizeof(U)*8);}
	inline constexpr modint(U x,int):v(x){} 
	public:
	inline constexpr static S mod(){return P;}
	inline constexpr static U umod(){return (U)P;}
	inline constexpr modint():v(0){}
	inline constexpr modint(const modint&x):v(x.v){}
	template<class T>inline constexpr modint(T x):v(reduce((D)(sizeof(T)>sizeof(U)?x%P:x)*R2)){}
	inline U&raw(){return v;}
	inline constexpr S val()const{U x=reduce(v);return (x-P)>>(sizeof(U)*8-1)?x:x-P;}
	template<class T>inline constexpr operator T()const{return val();}
	inline constexpr friend bool operator==(const modint&x,const modint&y){return x.val()==y.val();}
	inline constexpr friend bool operator!=(const modint&x,const modint&y){return x.val()!=y.val();}
	inline constexpr modint&operator=(const modint&x){v=x.v;return *this;}
	inline constexpr modint&operator++()return *this+=1;}
	inline constexpr modint operator++(int){modint x=*this;++*this;return x;}
	inline constexpr modint&operator--(){return *this-=1;}
	inline constexpr modint operator--(int){modint x=*this;--*this;return x;}
	inline constexpr modint operator-()const{return modint(v?P2-v:0,0);}
	inline constexpr modint&operator+=(const modint&x){v+=x.v,(v-P2)>>(sizeof(U)*8-1)||(v-=P2);return *this;}
	inline constexpr modint&operator-=(const modint&x){v-=x.v,v>>(sizeof(U)*8-1)&&(v+=P2);return *this;}
	inline constexpr modint&operator*=(const modint&x){v=reduce((D)v*x.v);return *this;}
	inline constexpr modint&operator/=(const modint&x){return *this*=x.inv();}
	inline constexpr friend modint operator+(modint x,const modint&y){return x+=y;}
	inline constexpr friend modint operator-(modint x,const modint&y){return x-=y;}
	inline constexpr friend modint operator*(modint x,const modint&y){return x*=y;}
	inline constexpr friend modint operator/(modint x,const modint&y){return x/=y;}
	template<class T>inline constexpr modint pow(T y)const{modint x=*this,z=1;while(y){if(y&1)z*=x;if(y>>= 1)x*= x;}return z;}
	template<class T>inline constexpr friend modint pow(const modint&x,T y){return x.pow(y);}
	inline constexpr modint inv()const{U a=val(),b=P;using T=std::make_signed_t<U>;T x=1,y=0;while(b){U q=a/b,t=a-q*b;a=b;b=t;T t1=x-(T)q*y;x=y;y=t1;}if(x<0)x+=(T)P;return modint((U)x);}
	inline constexpr friend modint inv(const modint&x){return x.inv();}
	inline friend std::istream&operator>>(std::istream &is,modint&x){S y;is>>y,x=y;return is;}
	inline friend std::ostream&operator<<(std::ostream &os,const modint&x){return os<<x.val();}
};
