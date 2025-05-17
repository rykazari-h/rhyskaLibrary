#include <algorithm>
#include <vector>
template<class T>class weighted_dsu{
public:
  explicit weighted_dsu(int _n,T _e=0):n(_n),parent(_n,-1),distance(_n,_e){}

  //新規に結合できたときtrueを返します
  int merge(int a,int b,T w=0){
    w+=diff(b,a);
    a=root(a),b=root(b);
    if(a==b)return 0;
    //aにbを結合します(union by size)
    if(parent[a]>parent[b])std::swap(a,b),w=-w;
    parent[a]+=parent[b];
    parent[b]=a;
    distance[b]=w;
    return 1;
  }

  //連結ならtrueを返します
  int same(int a,int b){return root(a)==root(b);}

  //rootを返します
  int root(int a){
    if(parent[a]<0)return a;
    int r=root(parent[a]);
    distance[a]+=distance[parent[a]];
    return parent[a]=r;
  }

  //頂点aが含まれる連結成分の要素数を返します
  int size(int a){return -parent[root(a)];}

  //森を返します
  std::vector<std::vector<int>> groups(){
    std::vector<std::vector<int>> res(n);
    for(int i=0;i<n;i++)res[root(i)].push_back(i);
    res.erase(remove_if(res.begin(),res.end(),
      [&](const std::vector<int>&v){return v.empty();}),res.end());
    return res;
  }

	//ノードのポテンシャルを返します
	T weight(int a){
      root(a);
      return distance[a];
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
  std::vector<T>distance;
};
