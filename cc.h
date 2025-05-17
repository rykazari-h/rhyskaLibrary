#include <vector>
#include <algorithm>
template<class T=int>class cc{
public:
	cc():did(0){}
	void push(T x){d.push_back(x),did=0;}
	int operator()(T x){
		init();
		return std::upper_bound(d.begin(),d.end(),x)-d.begin()-1;
	}
	T operator[](int x){
		init();
		return d[x];
	}
	int size(){
		init();
		return d.size();
	}
private:
	void init(){
		if(did)return;
		std::sort(d.begin(),d.end());
		d.erase(std::unique(d.begin(),d.end()),d.end());
		did=1;
	}
	int did;
	std::vector<T>d;
};
