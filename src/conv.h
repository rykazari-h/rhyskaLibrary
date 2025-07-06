const long long mod4ntt=15*(1<<27)+1;
const long long root4ntt=137;
template<class T>
void ntt4conv(std::vector<T>&a,bool inv);
long long modpow4mul(long long a,long long b);
template<class T=int>
std::vector<T> convolution(std::vector<T> a,std::vector<T> b){
	long long n=1;
	while(n<(long long)(a.size()+b.size()))n<<=1;
	a.resize(n);b.resize(n);
	ntt4conv(a,0);
	ntt4conv(b,0);
	for(int i=0;i<n;i++)a[i]=(long long)(a[i])*b[i]%mod4ntt;
	ntt4conv(a,1);
	return a;
}
long long modpow4ntt(long long a,long long b){
	long long res=1;
	for(;b;b>>=1,a=a*a%mod4ntt)if(b&1)res=res*a%mod4ntt;
	return res;
}
template<class T>
void ntt4conv(std::vector<T>&a,bool inv){
	int n=a.size();
	for(int i=1,j=0;i<n;i++){
		int b=n>>1;
		for(;j&b;b>>=1)j^=b;
		j^=b;
		if(i<j)std::swap(a[i],a[j]);
	}
	for(int len=2;len<=n;len<<=1){
		long long wn=modpow4ntt(root4ntt,(mod4ntt-1)/len);
		if(inv)wn=modpow4ntt(wn,mod4ntt-2);
		for(int i=0;i<n;i+=len){
			long long w=1;
			for(int j=0;j<len/2;j++){
				long long  u=a[i+j],v=(long long)(a[i+j+len/2])*w%mod4ntt;
				a[i+j]=(u+v)%mod4ntt;
				a[i+j+len/2]=(u-v+mod4ntt)%mod4ntt;
				w=w*wn%mod4ntt;
			}
		}
	}
	if(inv){
		long long invn=modpow4ntt(n,mod4ntt-2);
		for(T&x:a)x=(long long)(x)*invn%mod4ntt;
	}
}
