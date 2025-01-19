#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct dsu{
	public:
		dsu() : _n(0) {}
		explicit dsu(int n) : _n(n),P(n,-1) {}
		int root(int i){
			if(P[i]<0)return i;
			return P[i]=root(P[i]);
		}
		int merge(int a,int b){
			int x=root(a);
			int y=root(b);
			if(x==y)return x;
			if(P[x]>P[y])swap(x,y);
			P[x]+=P[y];
			P[y]=x;
			return x;
		}
		bool same(int a,int b){
			return root(a)==root(b);
		}
		int size(int i){
			return -P[root(i)];
		}
		vector<vector<int>>groups(){
			vector<int>L(_n),G(_n);
			for(int i=0;i<_n;i++){
				L[i]=root(i);
				G[L[i]]++;
			}
			vector<vector<int>>R(_n);
			for(int i=0;i<_n;i++)R[i].reserve(G[i]);
			for(int i=0;i<_n;i++)R[L[i]].push_back(i);
			R.erase(remove_if(R.begin(),R.end(),[&](const vector<int>&v){return v.empty();}),R.end());
			return R;
		}
	private:
		int _n;
		vector<int>P;
};
