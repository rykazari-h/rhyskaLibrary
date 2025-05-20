#include <vector>
#include <algorithm>
template<class T=int>class cc{
public:
	cc():did(0){}
	explicit cc(std::vector<T> &v):did(0),d(v){}
	explicit cc(T *x,T *end):did(0){push(x,end);}
	void clear(){did=0;d.clear();}

	//要素の追加
	void push(T x){d.push_back(x),did=0;}
	void push(const std::vector<T> &v){for(const T &x:v)push(x);}
	void push(T *x,T *end){for(;x!=end;x++)push(*x);}

	//実座標->index
	int operator()(T x){
		if(!did)init();
		return std::upper_bound(d.begin(),d.end(),x)-d.begin()-1;
	}
	std::vector<int> press(const std::vector<T> &v){
		if(!did)init();
		std::vector<int>res;
		for(const T &x:v)res.push_back(*this(x));
		return res;
	}

	//index->実座標
	T operator[](int x){
		if(!did)init();
		return d[x];
	}

	//set(array).size
	int size(){
		if(!did)init();
		return d.size();
	}
private:
	void init(){
		std::sort(d.begin(),d.end());
		d.erase(std::unique(d.begin(),d.end()),d.end());
		did=1;
	}
	int did;
	std::vector<T>d;
};
