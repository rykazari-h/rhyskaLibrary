#pragma once
#include <algorithm>
#include <vector>
template<class T>class weighted_dsu{
public:
	explicit weighted_dsu(int _n,T _e=0):n(_n),parent(_n,-1),potential(_n,_e){}
	int merge(int a,int b,T w=0){
		w+=weight(a)-weight(b);
		a=root(a),b=root(b);
		if(a==b)return 0;
		if(parent[a]<parent[b]){
			parent[a]+=parent[b];
			parent[b]=a;
			potential[b]=w;
		}
		else{
			parent[b]+=parent[a];
			parent[a]=b;
			potential[a]=-w;
		}
		return 1;
	}
	int same(int a,int b){return root(a)==root(b);}
	int root(int a){
		if(parent[a]<0)return a;
		int r=root(parent[a]);
		potential[a]+=potential[parent[a]];
		return parent[a]=r;
	}
	int size(int a){return -parent[root(a)];}
	int size(){
		std::vector<bool>count(n,0);
		for(int i=0;i<n;i++)count[root(i)]=1;
		int res=0;
		for(int i=0;i<n;i++)res+=count[i];
		return res;
	}
	std::vector<std::vector<int>> groups(){
		std::vector<std::vector<int>> res(n);
		for(int i=0;i<n;i++)res[root(i)].push_back(i);
		res.erase(std::remove_if(res.begin(),res.end(),
					[&](const std::vector<int>&v){return v.empty();}),res.end());
		return res;
	}

	T weight(int a){
		root(a);
		return potential[a];
	}
	T diff(int a,int b){
		return weight(b)-weight(a);
	}
private:
	int n;
	std::vector<int>parent;
	std::vector<T>potential;
};
