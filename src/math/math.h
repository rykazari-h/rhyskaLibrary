#pragma once
#include<cmath>
namespace math{
	constexpr long long isqrt(long long n){
		if(n<=0)return 0;
		long long x=std::sqrt(n);
		while((x+1)*(x+1)<=n)x++;
		while(x*x>n)x--;
		return x;
	}
	constexpr long long modpow(long long a,long long n,long long m=998244353){
		long long res=1;
		for(a%=m;n;n>>=1,a=a*a%m)if(n&1)res=res*a%m;
		return res;
	}
	constexpr int primitive_root(int m){
		if(m==2)return 1;
		if(m==0xA000001)return 3;
		if(m==0x1C000001)return 3;
		if(m==0x2D000001)return 11;
		if(m==998244353)return 3;
		int d[20]{};
		d[0]=2;
		int c=1;
		int x=(m-1)/2;
		while(x%2==0)x/=2;
		for(int i=3;(long long)(i)*i<=x;i+=2)if(x%i==0){
			d[c++]=i;
			while(x%i==0)x/=i;
		}
		if(x>1)d[c++]=x;
		for(int g=2;;g++){
			bool f=1;
			for(int i=0;i<c;i++)if(modpow(g,(m-1)/d[i],m)==1){
				f=0;
				break;
			}
			if(f)return g;
		}
	}
	constexpr long long modinv(long long a,long long m){
		long long b=m,x=1,y=0;
		while(b){
			long long q=a/b;
			long long t=a-q*b;
			a=b;b=t;
			t=y;y=x;x=t;
			y-=q*x;
		}
		if(x<0)x+=m;
		return x;
	}
	constexpr long long gcd(long long a,long long b){
		if(!a&&!b)return 0;//仮
		while(b){
			long long t=a%b;
			a=b;b=t;
		}
		return a;
	}
	constexpr long long lcm(long long a,long long b){return a/gcd(a,b)*b;}
	constexpr long long gcd(long long a){return a;}
	constexpr long long lcm(long long a){return a;}
	template<class... T>constexpr long long gcd(long long a,T... b){
		for(long long x:{b...})a=gcd(a,x);
		return a;
	}
	template<class... T>constexpr long long lcm(long long a,T... b){
		for(long long x:{b...})a=lcm(a,x);
		return a;
	}
}//namespace math
