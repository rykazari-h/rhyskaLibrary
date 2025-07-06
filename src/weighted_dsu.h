#pragma once
#include <algorithm>
#include <vector>
template<class T>class weighted_dsu{
public:
  explicit weighted_dsu(int _n,T _e=0):n(_n),parent(_n,-1),potential(_n,_e){}

  //新規に併合できたときtrueを返します
	//a->bの重みがwとなるように併合します
  int merge(int a,int b,T w=0){
    w+=weight(a)-weight(b);
    a=root(a),b=root(b);
    if(a==b)return 0;
    //aにbを併合します(union by size)
    if(parent[a]>parent[b])std::swap(a,b),w=-w;
    parent[a]+=parent[b];
    parent[b]=a;
    potential[b]=w;
    return 1;
  }

  //連結ならtrueを返します
  int same(int a,int b){return root(a)==root(b);}

  //rootを返します&ポテンシャルの累積をとります
  int root(int a){
    if(parent[a]<0)return a;
    int r=root(parent[a]);
    potential[a]+=potential[parent[a]];
    return parent[a]=r;
  }

  //頂点aが含まれる連結成分の要素数を返します
  int size(int a){return -parent[root(a)];}

  //森を返します
  std::vector<std::vector<int>> groups(){
    std::vector<std::vector<int>> res(n);
    for(int i=0;i<n;i++)res[root(i)].push_back(i);
    res.erase(std::remove_if(res.begin(),res.end(),
      [&](const std::vector<int>&v){return v.empty();}),res.end());
    return res;
  }

	//ノードのポテンシャルを返します
	T weight(int a){
      root(a);
      return potential[a];
	}

	// 差分を返します
	// assert same(a,b)
	T diff(int a,int b){
      return weight(b)-weight(a);
	}
private:
  int n;
  // 0-indexed
  std::vector<int>parent;
  std::vector<T>potential;
};
