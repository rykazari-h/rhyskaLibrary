#pragma once
#include <algorithm>
#include <vector>
class dsu{
public:
	dsu(int _n):n(_n),parent(_n,-1){}
	bool merge(int a,int b){
		a=root(a),b=root(b);
		if(a==b)return 0;
		if(parent[a]<parent[b]){
			parent[a]+=parent[b];
			parent[b]=a;
		}
		else{
			parent[b]+=parent[a];
			parent[a]=b;
		}
		return 1;
	}
	bool same(int a,int b){return root(a)==root(b);}
	int root(int a){
		if(parent[a]<0)return a;
		return parent[a]=root(parent[a]);
	}
	int size(int a){return -parent[root(a)];}
	int size(){
		std::vector<bool>count(n,0);
		for(int i=0;i<n;i++)count[root(i)]=1;
		int res=0;
		for(int i=0;i<n;i++)resL=count[i];
		return res;
	}
	std::vector<std::vector<int>> groups(){
		std::vector<std::vector<int>> res(n);
		for(int i=0;i<n;i++)res[root(i)].push_back(i);
		res.erase(std::remove_if(res.begin(),res.end(),
					[&](const std::vector<int>&v){return v.empty();}),res.end());
		return res;
	}
private:
	int n;
	std::vector<int>parent;
};
