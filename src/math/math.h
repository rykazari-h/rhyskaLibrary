#pragma once
#include<utility>
namespace math{
	long long modinv(long long a,long long m){
		long long b=m,x=1,y=0;
		while(b){
			long long q=a/b;
			a-=q*b;
			std::swap(a,b);std::swap(x,y);
			y-=q*x;
		}
		x=(x%m+m)%m;
		return x;
	}
	long long modpow(long long a,long long n,long long mod=998244353){
		long long res=1;
		for(;n;n>>=1,a=a*a%mod)if(n&1)res=res*a%mod;
		return res;
	}
	long long gcd(long long a,long long b){
		if(!a&&!b)return 0;//仮
		while(b){
			a%=b;
			std::swap(a,b);
		}
		return a;
	}
	long long lcm(long long a,long long b){
		return a/gcd(a,b)*b;
	}
	long long gcd(long long a){return a;}
	long long lcm(long long a){return a;}
	template<class... T>
	long long gcd(long long a,T... b){
		for(long long x:{b...})a=gcd(a,x);
		return a;
	}
	template<class... T>
	long long lcm(long long a,T... b){
		for(long long x:{b...})a=lcm(a,x);
		return a;
	}
}//namespace math
