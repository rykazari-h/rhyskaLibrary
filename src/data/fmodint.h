#pragma once
template<int id>class fmodint{
	public:
	unsigned v;
	inline static unsigned P;
	inline static unsigned long long P2;
	static void setmod(unsigned S){P=S;P2=-1ull/P+1;}
	inline static unsigned mod(){return P;}
	inline fmodint():v(0){}
	inline fmodint(const fmodint&x):v(x.v){}
	inline fmodint(long long x){x%=P;v=(x>=0?x:x+P);}
	inline fmodint(unsigned x,int):v(x){}
	inline unsigned val()const{return v;}
	template<class T>inline constexpr operator T()const{return val();}
	inline friend bool operator==(const fmodint&x,const fmodint&y){return x.val()==y.val();}
	inline friend bool operator!=(const fmodint&x,const fmodint&y){return x.val()!=y.val();}
	inline fmodint&operator=(const fmodint&x){v=x.v;return *this;}
	inline fmodint&operator++(){++v;v==P&&(v=0);return *this;}
	inline fmodint operator++(int){fmodint x=*this;++*this;return x;}
	inline fmodint&operator--(){v==0?v=P-1:--v;return *this;}
	inline fmodint operator--(int){fmodint x=*this;--*this;return x;}
	inline fmodint operator-()const{return fmodint(v?P-v:0,0);}
	inline fmodint&operator+=(const fmodint&x){v+=x.v;v>=P&&(v-=P);return*this;}
	inline fmodint&operator-=(const fmodint&x){v+=P-x.v;v>=P&&(v-=P);return*this;}
	inline fmodint&operator*=(const fmodint&x){unsigned long long z=(unsigned long long)v*x.v,c,zc;c=((unsigned __int128)(z)*P2)>>64;zc=c*P;v=(unsigned)(z-zc+(z<zc?P:0));return *this;}
	inline fmodint&operator/=(const fmodint&x){return*this*=x.inv();}
	inline fmodint operator+(const fmodint&y){return fmodint(*this)+=y;}
	inline fmodint operator-(const fmodint&y){return fmodint(*this)-=y;}
	inline fmodint operator*(const fmodint&y){return fmodint(*this)*=y;}
	inline fmodint operator/(const fmodint&y){return fmodint(*this)/=y;}
	template<class T>inline friend fmodint operator+(const T&x,const fmodint&y){return y+x;}
	template<class T>inline friend fmodint operator-(const T&x,const fmodint&y){return fmodint(x)-y;}
	template<class T>inline friend fmodint operator*(const T&x,const fmodint&y){return y*x;}
	template<class T>inline friend fmodint operator/(const T&x,const fmodint&y){return fmodint(x)/y;}
	template<class T>inline fmodint pow(T y)const{fmodint x=*this,z=1;while(y){if(y&1)z*=x;if(y>>=1)x*=x;}return z;}
	template<class T>inline friend fmodint pow(const fmodint&x,T y){return x.pow(y);}
	inline fmodint inv()const{unsigned a=val(),b=P;int x=1,y=0;while(b){unsigned q=a/b,t=a-q*b;a=b;b=t;int t1=x-q*y;x=y;y=t1;}if(x<0)x+=(int)P;return fmodint((unsigned)x,0);}
	inline friend fmodint inv(const fmodint&x){return x.inv();}
	inline friend std::istream&operator>>(std::istream &is,fmodint&x){long long y;is>>y,x=y;return is;}
	inline friend std::ostream&operator<<(std::ostream &os,const fmodint&x){return os<<x.val();}
};
