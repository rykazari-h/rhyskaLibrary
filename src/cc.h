#pragma once
#include <vector>
#include <algorithm>
template<class T=int>class cc{
public:
	cc():did(0){}
	explicit cc(std::vector<T> &v):did(0),d(v){}
	template<class S>
	explicit cc(S x,S end):did(0){push(x,end);}
	void clear(){did=0;d.clear();}
	void push(T x){d.push_back(x),did=0;}
	void push(const std::vector<T> &v){for(const T &x:v)push(x);}
	template<class S>void push(S x,S end){for(;x!=end;++x)push(*x);}
	int operator()(T x){
		if(!did)init();
		return std::upper_bound(d.begin(),d.end(),x)-d.begin()-1;
	}
	template<class S>
	std::vector<int> press(S x,S end){
		if(!did)init();
		std::vector<int>res;
		for(;x!=end;++x)res.push_back((*this)(*x));
		return res;
	}
	std::vector<int> press(const std::vector<T>&v){
		if(!did)init();
		std::vector<int>res;
		res.reserve(v.size());
		for(auto&&x:v)res.push_back((*this)(x));
		return res;
	}
	T operator[](int x){
		if(!did)init();
		return d[x];
	}
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
