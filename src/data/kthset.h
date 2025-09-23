#pragma once
//Original code by tatyam:https://github.com/tatyam-prime/SortedSet
#include<vector>
#include<algorithm>
#include<cmath>
#include<tuple>
template<class T>class kthset{
	static constexpr int kRatio=2,kBound=20;
	std::vector<std::vector<T>> list_;int size_;
	std::tuple<std::vector<T>*,int,int> _position(const T&x){
		int sz=list_.size();
		for(int i=0;i<sz;i++)if(x<=list_[i].back())
			return std::make_tuple(&(list_[i]),i,(int)(std::lower_bound(list_[i].begin(),list_[i].end(),x)-list_[i].begin()));
		return std::make_tuple(&(list_.back()),sz-1,list_.back().size());
	}
	T _pop(std::vector<T>*b,int bi,int i){
		T v=(*b)[i];
		b->erase(b->begin()+i);
		size_--;
		if(b->empty())list_.erase(list_.begin()+bi);
		return v;
	}
	public:
	std::vector<std::vector<T>>&a(){return list_;}
	const std::vector<std::vector<T>>&a()const{return list_;}
	template<bool IsConst>struct iterator_base{
		using iterator_category=std::random_access_iterator_tag;
		using value_type=std::conditional_t<IsConst,const T,T>;
		using difference_type=std::ptrdiff_t;
		using pointer=std::conditional_t<IsConst,const T*,T*>;
		using reference=std::conditional_t<IsConst,const T&,T&>;
		int out_idx,in_idx;std::conditional_t<IsConst,const std::vector<std::vector<T>>&,std::vector<std::vector<T>>&> bucket;
		iterator_base()=default;
		iterator_base(const iterator_base&b):out_idx(b.out_idx),in_idx(b.in_idx),bucket(b.bucket){}
		iterator_base(int a,int b,kthset*ptr):out_idx(a),in_idx(b),bucket(ptr->a()){}
		reference operator*()const{return bucket[out_idx][in_idx];}
		pointer operator->()const{return&bucket[out_idx][in_idx];}
		iterator_base&operator+=(int n){
			if(n>=0){
				while((int)bucket[out_idx].size()-1-in_idx<n)n-=bucket[out_idx++].size()-in_idx,in_idx=0;
				in_idx+=n;
			}
			else{
				n=-n;
				while(in_idx<n)n-=in_idx+1,in_idx=bucket[--out_idx].size()-1;
				in_idx-=n;
			}
			return*this;
		}
		iterator_base operator+(int n)const{return iterator_base(*this)+=n;}
		iterator_base&operator-=(int n){return*this+=(-n);}
		iterator_base operator-(int n)const{return*this+(-n);}
		difference_type operator-(iterator_base b)const{
			difference_type dist=0;
			iterator_base a=*this;
			int sign=1;
			if(a<b)a.swap(b),sign=-1;
			while(a.out_idx>b.out_idx)dist+=bucket[b.out_idx++].size()-b.in_idx,b.in_idx=0;
			dist+=a.in_idx-b.in_idx;
			return dist*sign;
		}
		iterator_base&operator++(){return++in_idx>=(int)bucket[out_idx].size()?out_idx++,in_idx=0,*this:*this;}
		iterator_base operator++(int){auto tmp=*this;++(*this);return tmp;}
		iterator_base&operator--(){in_idx==0?--out_idx,in_idx=bucket[out_idx].size()-1:--in_idx;return*this;}
		iterator_base operator--(int){auto tmp=*this;--(*this);return tmp;}
		bool operator==(const iterator_base&b)const{return in_idx==b.in_idx&&out_idx==b.out_idx;}
		bool operator!=(const iterator_base&b)const{return!(*this==b);}
		bool operator<(const iterator_base&b)const{return out_idx<b.out_idx||(out_idx==b.out_idx&&in_idx<b.in_idx);}
		bool operator<=(const iterator_base&b)const{return*this<b||*this==b;}
		bool operator>(const iterator_base&b)const{return b<*this;}
		bool operator>=(const iterator_base&b)const{return b<=*this;}
		iterator_base&operator=(const iterator_base&b){in_idx=b.in_idx,out_idx=b.out_idx;return*this;}
		void swap(iterator_base&b){std::swap(in_idx,b.in_idx);std::swap(out_idx,b.out_idx);}
	};
	using iterator=iterator_base<false>;
	using const_iterator=iterator_base<true>;
	iterator begin(){return list_.empty()?end():iterator(0,0,this);}
	iterator end(){return iterator(list_.size(),0,this);}
	const_iterator begin()const{return cbegin();}
	const_iterator end()const{return cend();}
	const_iterator cbegin()const{return list_.empty()?cend():const_iterator(0,0,this);}
	const_iterator cend()const{return const_iterator(list_.size(),0,this);}
	using reverse_iterator=std::reverse_iterator<iterator>;
	using const_reverse_iterator=std::reverse_iterator<const_iterator>;
	reverse_iterator rbegin(){return reverse_iterator(end());}
	reverse_iterator rend(){return reverse_iterator(begin());}
	const_reverse_iterator rbegin()const{return const_reverse_iterator(end());}
	const_reverse_iterator rend()const{return const_reverse_iterator(begin());}
	const_reverse_iterator crbegin()const{return const_reverse_iterator(cend());}
	const_reverse_iterator crend()const{return const_reverse_iterator(cbegin());}
	kthset():size_(0){}
	kthset(std::vector<T> z){
		if(!std::is_sorted(z.begin(),z.end()))std::sort(z.begin(),z.end());
		z.erase(std::unique(z.begin(),z.end()),z.end());
		int n=size_=z.size();
		int s=std::ceil(std::sqrt((double)n/kRatio));
		list_.resize(s);
		for(int i=0;i<s;i++)list_[i].assign(z.begin()+n*i/s,z.begin()+n*(i+1)/s);
	}
	std::vector<T> list(){
		std::vector<T> res;res.reserve(size_);
		for(auto&a:list_)res.insert(res.end(),a.begin(),a.end());
		return res;
	}
	kthset&operator=(const kthset&b){list_=b.list_,size_=b.size_;return*this;}
	kthset&operator=(kthset&&b){list_=std::move(b.list_),size_=b.size_;return*this;}
	bool empty()const{return!size_;}
	int size()const{return size_;}
	void clear(){size_=0;list_.clear();}
	bool insert(T x){
		if(!size_){list_={{x}},size_=1;return true;}
		auto[b,bi,i]=_position(x);
		if(i!=(int)b->size()&&(*b)[i]==x)return false;
		b->insert(b->begin()+i,x);
		size_++;
		if((int)b->size()>(int)list_.size()*kBound){
			int mid=b->size()>>1;
			std::vector<T>nb(b->begin()+mid,b->end());
			b->erase(b->begin()+mid,b->end());
			list_.insert(list_.begin()+bi+1,std::move(nb));
		}
		return true;
	}
	template<class... U>bool emplace(U&&... x){return insert(T(std::forward<U>(x)...));}
	bool erase(const T&x){
		if(!size_)return false;
		auto[b,bi,i]=_position(x);
		if(i==(int)b->size()||(*b)[i]!=x)return false;
		_pop(b,bi,i);
		return true;
	}
	bool toggle(const T&x){return insert(x)?true:!erase(x);}
	T pop(int i=-1){
		if(i>=0){
			for(int b=0,n=list_.size();b<n;b++){
				if(i<(int)list_[b].size())return _pop(&list_[b],b,i);
				i-=list_[b].size();
			}
		}
		else{
			for(int b=list_.size()-1;b>=0;b--){
				i+=list_[b].size();
				if(i>=0)return _pop(&list_[b],b,i);
			}
		}
		return list_.back().back();
	}
	void swap(kthset&b){std::swap(list_,b.list_);std::swap(size_,b.size_);}
	void merge(const kthset&b){
		std::vector<T> all;
		all.reserve(size_+b.size_);
		for(auto& a:list_)all.insert(all.end(),a.begin(),a.end());
		for(auto& a:b.list_)all.insert(all.end(),a.begin(),a.end());
		*this=std::move(kthset(all));
	}
	bool count(const T&x){
		if(!size_)return false;
		auto[b,_,i]=_position(x);
		return i!=(int)b->size()&&(*b)[i]==x;
	}
	bool find(const T&x){return count(x);}
	bool contains(const T&x){return count(x);}
	T operator[](int i){
		if(i>=0){
			for(auto lt=list_.begin(),gt=list_.end();lt!=gt;++lt){
				if(i<(int)lt->size())return (*lt)[i];
				i-=lt->size();
			}
		}
		else{
			for(auto lt=list_.rbegin(),gt=list_.rend();lt!=gt;++lt){
				i+=lt->size();
				if(i>=0)return (*lt)[i];
			}
		}
		return list_.back().back();
	}
	iterator lower_bound(const T&x){
		for(int i=0,sz=list_.size();i<sz;i++)if(!list_[i].empty()&&list_[i].back()>=x)
			return iterator(i,(int)(std::lower_bound(list_[i].begin(),list_[i].end(),x)-list_[i].begin()),this);
		return end();
	}
	iterator upper_bound(const T&x){
		for(int i=0,sz=list_.size();i<sz;i++)if(!list_[i].empty()&&list_[i].back()>x)
			return iterator(i,(int)(std::upper_bound(list_[i].begin(),list_[i].end(),x)-list_[i].begin()),this);
		return end();
	}
	bool operator==(const kthset&b){return this->size_==b.size_&&this->list_==b.list_;}
	bool operator!=(const kthset&b){return!(*this==b);}
	bool operator<(const kthset&b){return this->list_<b.list_;}
	bool operator<=(const kthset&b){return*this==b||*this<b;}
	bool operator>(const kthset&b){return b<*this;}
	bool operator>=(const kthset&b){return b<=*this;}
	friend void swap(kthset&a,kthset&b){a.swap(b);}
};
