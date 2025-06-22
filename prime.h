#include<vector>
struct eratos{
	std::vector<bool>sieve;
	std::vector<long long>bfactor;
	std::vector<long long>table;
	long long size;
	eratos(long long n=1<<20):sieve(n+1,1),bfactor(n+1,-1){
		sieve[0]=sieve[1]=0;
		bfactor[1]=1;
		for(long long i=2;i<=n;i++)if(sieve[i]){
			bfactor[i]=i;
			for(long long j=i*2;j<=n;j+=i){
				sieve[j]=0;
				if(bfactor[j]<0)bfactor[j]=i;
			}
		}
		for(long long i=2;i<=n;i++)if(sieve[i])table.push_back(i);
		size=table.size();
	}
	bool isprime(long long a)const{
		return sieve[a];
	}
	std::vector<long long>rangetable(long long l=2,long long r=1<<20)const{
		std::vector<long long>res;
		for(long long x:table)if(l<=x&&x<=r)res.push_back(x);
		return res;
	}
	std::vector<std::pair<long long,long long>>factorize(long long a)const{
		std::vector<std::pair<long long,long long>>res;
		while(a>1){
			long long m=bfactor[a],n=0;
			for(;bfactor[a]==m;a/=m)n++;
			res.emplace_back(m,n);
		}
		return res;
	}
	std::vector<std::vector<std::pair<long long,long long>>>facttable(long long l=2,long long r=1<<20)const{
		std::vector<std::vector<std::pair<long long,long long>>>res(r-l+1);
		for(long long i=l;i<=r;i++)res[i-l]=factorize(i);
		return res;
	}
	std::vector<long long>divisor(long long a)const{
		std::vector<long long>res(1,1);
		for(auto p:factorize(a))
			for(long long i=0,s=res.size();i<s;i++)
				for(long long j=0,v=1;j<p.second;j++)
					res.push_back(res[i]*(v*=p.first));
		return res;
	}
	std::vector<std::vector<long long>>divisortable(long long l=2,long long r=1<<20)const{
		std::vector<std::vector<long long>>res(r-l+1);
		for(long long i=l;i<=r;i++)res[i-l]=divisor(i);
		return res;
	}
};
