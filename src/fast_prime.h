#pragma once
#include<cmath>
#include<vector>
struct fast_prime{
private:
	using i64=long long;
	using u64=unsigned long long;
	using u8=unsigned char;
	static u64 popcnt(u64 n){return __builtin_popcountll(n);}
	static int bit_pos(u8 a){return __builtin_ctz(a);}
	static u8 find_idx(int x){
		switch(x){
			case 1: return 1;
			case 7: return 2;
			case 11: return 4;
			case 13: return 8;
			case 17: return 16;
			case 19: return 32;
			case 23: return 64;
			case 29: return 128;
			default: return 0; 
		}
	}
	void initFlags(const i64 x,const i64 size){
		flags.clear();
		flags.resize(size,255);
		u8 r=x%30;
		flags[0]=254;
		if(r){
			if(r==1)flags.back()=0;
			else if(r<=7)flags.back()=1;
			else if(r<=11)flags.back()=3;
			else if(r<=13)flags.back()=7;
			else if(r<=17)flags.back()=15;
			else if(r<=19)flags.back()=31;
			else if(r<=23)flags.back()=63;
			else flags.back()=127;
		}
		if(1<x&&x<30)flags[0]^=1;
	}
	void rmemo(const i64 x){
		pflags.clear();indexes.clear();
		const u64 xi=x/30+1;
		const u64 b_x=static_cast<i64>(std::ceil(std::sqrt(x)))/30+1;
		pflags.resize(xi,255);
		pflags[0]=254;
		for(u64 k=0;k<=b_x;++k)for(u8 flag=pflags[k];flag;flag&=flag-1){
			int idx=bit_pos(flag&(-flag));
			const int m=Res30[idx];
			for(u64 p=k*(30*k+2*m)+m*m/30,i=idx;p<pflags.size();
					p+=k*offset1[i]+offset0[idx][i],i=(i+1)&7)pflags[p]&=posMask[idx][i];
		}
		for(u64 i=0,sz=pflags.size();i<sz;++i)for(u8 flag=pflags[i];flag;flag&=flag-1){
			int idx=bit_pos(flag&(-flag));
			const int m=Res30[idx];
			indexes.push_back((i*(30*i+2*m)+m*m/30+Base)<<3|idx);
		}
	}
	void segbuild(u8* flag,const u64 size){
		auto p_idx=indexes.begin();
		for(u64 k=0,sz=pflags.size();k<sz;++k)for(u8 f=pflags[k];f;f&=f-1){
			int idx=bit_pos(f&(-f));
			u64 nidx=*p_idx;
			u64 p=(nidx>>3)-Base,i=nidx&7;
			for(;p<size;p+=k*offset1[i]+offset0[idx][i],i=(i+1)&7)flag[p]&=posMask[idx][i];
			*p_idx=(p<<3)|i;
			++p_idx;
		}
	}
	static constexpr u8 posMask[][8]={
		{254,253,251,247,239,223,191,127},
		{253,223,239,254,127,247,251,191},
		{251,239,254,191,253,127,247,223},
		{247,254,191,223,251,253,127,239},
		{239,127,253,251,223,191,254,247},
		{223,247,127,253,191,254,239,251},
		{191,251,247,127,254,239,223,253},
		{127,191,223,239,247,251,253,254},
	};
	static constexpr int Res30[8]={1,7,11,13,17,19,23,29};
	static constexpr int offset1[]={6,4,2,4,2,4,6,2};
	static constexpr int offset0[][8]={
		{0,0,0,0,0,0,0,1},{1,1,1,0,1,1,1,1},
		{2,2,0,2,0,2,2,1},{3,1,1,2,1,1,3,1},
		{3,3,1,2,1,3,3,1},{4,2,2,2,2,2,4,1},
		{5,3,1,4,1,3,5,1},{6,4,2,4,2,4,6,1},
	};
	static constexpr u64 Base=1000000;
	std::vector<u8>flags;
	std::vector<u8>pflags;
	std::vector<u64>indexes;
	u64 x_;
public:
	fast_prime(const i64 x){build(x);}
	void build(i64 x){
		x_=x++;
		rmemo(std::ceil(std::sqrt(x)));
		i64 sz=(x+29)/30;
		initFlags(x,sz);
		for(u8* seg=flags.data();sz>0;seg+=Base,sz-=Base)
			segbuild(seg,std::min((u64)sz,Base));
	}
	bool operator[](const u64 x){
		if(x==2||x==3||x==5)return true;
		if(x<2||!(x&1)||x%3==0||x%5==0)return false;
		return static_cast<bool>(flags[x/30]&find_idx(x%30));
	}
	u64 count(){
		if(x_<2)return 0;
		if(x_<3)return 1;
		if(x_<5)return 2;
		if(x_<7)return 3;
		u64 res=3;
		for(u8 f:flags)res+=popcnt(f);
		return res;
	}
	std::vector<u64> primelist(){
		if(x_<2)return {};
		if(x_<3)return {2};
		if(x_<5)return {2,3};
		if(x_<7)return {2,3,5};
		std::vector<u64> res={2,3,5};
		for(i64 i=0,sz=flags.size();i<sz;++i)
			for(int j=0;j<8;++j)
				if(flags[i]&(1<<j))res.push_back(i*30+Res30[j]);
		return res;
	}
};
