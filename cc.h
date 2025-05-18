#include <vector>
#include <algorithm>
template<class T=int>class cc{
public:
	cc():did(0){}
	void clear(){did=0;d.clear();}

	//要素の追加
	void push(T x){d.push_back(x),did=0;}
	void push(const std::vector<T> &v){for(const T &x:v)d.push_back(x);did=0;}

	//実座標->index
	int operator()(T x){
		init();
		return std::upper_bound(d.begin(),d.end(),x)-d.begin()-1;
	}
	std::vector<int> press(const std::vector<T> &v){
		init();
		std::vector<int>res;
		for(const T &x:v)res.push_back(std::upper_bound(d.begin(),d.end(),x)-d.begin()-1);
		return res;
	}

	//index->実座標
	T operator[](int x){
		init();
		return d[x];
	}

	//set(array).size
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
