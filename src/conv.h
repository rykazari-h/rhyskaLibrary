#pragma once
namespace ntt_conv {
	const long long mod=15*(1<<27)+1;
	const long long root=137;
	long long modpow(long long a,long long b){
		long long res=1;
		for (;b;b>>=1,a=a*a%mod)if(b&1)res=res*a%mod;
		return res;
	}
	template<class T>
	void ntt(std::vector<T>&a,bool inv){
		int n=a.size();
		for(int i=1,j=0;i<n;i++){
			int b=n>>1;
			for(;j&b;b>>=1)j^=b;
			j^=b;
			if(i<j)std::swap(a[i],a[j]);
		}
		for(int len=2;len<=n;len<<=1){
			long long wn=modpow(root,(mod-1)/len);
			if(inv)wn=modpow(wn,mod-2);
			for(int i=0;i<n;i+=len){
				long long w=1;
				for(int j=0;j<len/2;j++){
					long long u=a[i+j],v=(long long)(a[i+j+len/2])*w%mod;
					a[i+j]=(u+v)%mod;
					a[i+j+len/2]=(u-v+mod)%mod;
					w=w*wn%mod;
				}
			}
		}
		if(inv){
			long long invn=modpow(n,mod-2);
			for(T&x:a)x=(long long)(x)*invn%mod;
		}
	}
}
template<class T=int>
std::vector<T>convolution(std::vector<T>a,std::vector<T>b){
	long long n=1;
	while(n<(long long)(a.size()+b.size()))n<<=1;
	a.resize(n);b.resize(n);
	ntt_conv::ntt(a,0);
	ntt_conv::ntt(b,0);
	for(int i=0;i<n;i++)a[i]=(long long)(a[i])*b[i]%ntt_conv::mod;
	ntt_conv::ntt(a,1);
	return a;
}

