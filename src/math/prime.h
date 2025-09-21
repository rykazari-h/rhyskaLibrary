#pragma once
#include<cmath>
#include<vector>
#include<utility>
class prime{
private:
	std::vector<int>bfactor;
public:
	prime(const int x){build(x);}
	void build(int x){
		++x;
		int x_i=x/2;
		bfactor.clear();
		bfactor.resize(x_i,0);
		for(int i=1;i<x_i;++i)bfactor[i]=i*2+1;
		bfactor[0]=1;
		const int b_x=static_cast<int>(std::ceil(std::sqrt(x)+0.1))/2;
		for(int i=1;i<b_x;++i)if(bfactor[i]==i*2+1){
			for(int p=2*i*(i+1),k=2*i+1;p<x_i;p+=k)bfactor[p]=i*2+1;
		}
	}
	bool operator[](int x){
		if(x==2)return 1;
		if(x==1)return 0;
		if(x&1)return bfactor[(x-1)/2]==x;
		return 0;
	}
	std::vector<std::pair<int,int>> factorize(int x){
		if(x==0)return {{0,0}};
		if(x==1)return {{1,1}};
		std::vector<std::pair<int,int>> res;
		{
			int cnt=0;
			while(!(x&1)&&x>1)++cnt,x>>=1;
			if(cnt)res.emplace_back(2,cnt);
		}
		int pidx=(x-1)/2;
		while(x>1){
			int p=bfactor[pidx],e=0;
			while(x%p==0)x/=p,++e;
			res.emplace_back(p,e);
			pidx=(x-1)/2;
		}
		return res;
	}
	std::vector<int>divisors(int x){
		std::vector<int> res(1,1);
		for(auto&&p:factorize(x)){
			int n=res.size();
			for(int i=0;i<n;++i)for(int j=0,v=1;j<p.second;++j)v*=p.first,res.push_back(res[i]*v);
		}
		if(res.size()==2&&res[0]==res[1]&&res[0]==1)return {1};
		return res;
	}
	int count(){
		int res=0;
		for(int i=1,sz=bfactor.size();i<sz;++i)res+=bfactor[i]==i*2+1;
		return res;
	}
	std::vector<int> primelist(){
		std::vector<int> res;
		for(int i=1,sz=bfactor.size();i<sz;++i)if(bfactor[i]==i*2+1)res.push_back(i*2+1);
		return res;
	}
};
