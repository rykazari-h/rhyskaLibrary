#include <algorithm>
#include <vector>
class dsu{
public:
  explicit dsu(int _n):n(_n),parent(_n,-1){}

  //新規に併合できた時trueを返します
  int merge(int a,int b){
    a=root(a),b=root(b);
    if(a==b)return 0;
    //aにbを併合します(union by size)
    if(parent[a]>parent[b])std::swap(a,b);
    parent[a]+=parent[b];
    parent[b]=a;
    return 1;
  }

  //連結ならtrueを返します
  int same(int a,int b){return root(a)==root(b);}

  //rootを返します
  int root(int a){
    if(parent[a]<0)return a;
    //経路圧縮あり
    if(path_compress)return parent[a]=root(parent[a]);
    //経路圧縮なし
    return root(parent[a]);
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
private:
  int n;
  //0-indexed
  std::vector<int>parent;
  //経路圧縮するか
  int path_compress=1;
};

