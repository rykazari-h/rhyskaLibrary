#include<vector>
#include<utility>
#include<algorithm>
#include<cmath>
#include<tuple>
template<class T>class bucket_set{
	static constexpr int kRatio=16,kBound=24;
	std::vector<std::vector<T>> list_;
	int size_;
	std::tuple<std::vector<T>*,int,int> _position(const T&x)const{
		int sz=list_.size();
		for(int i=0;i<sz;i++)if(x<=list_[i].back())
			return {&(list_[i]),i,(int)(std::lower_bound(list_[i].begin(),list_[i].end(),x)-list_[i].begin())};
		return {&(list_.back()),sz-1,list_.back().size()};
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
	struct iterator{
		using iterator_category=std::bidirectional_iterator_tag;
		using value_type=T;
		using difference_type=std::ptrdiff_t;
		using pointer=T*;
		using reference=T&;
		using outer_iter=typename std::vector<std::vector<T>>::iterator;
		using inner_iter=typename std::vector<T>::iterator;
		outer_iter outer_cur, outer_end;
		inner_iter inner_cur;
		iterator()=default;
		iterator(outer_iter o_cur,outer_iter o_end,inner_iter i_cur):outer_cur(o_cur),outer_end(o_end),inner_cur(i_cur){}
		reference operator*()const{return*inner_cur;}
		pointer operator->()const{return&(*inner_cur);}
		iterator&operator++(){
			++inner_cur;
			if(outer_cur!=outer_end&&inner_cur==outer_cur->end()){
				++outer_cur;
				if (outer_cur!=outer_end){
					inner_cur=outer_cur->begin();
				}
			}
			return*this;
		}
		iterator operator++(int){auto tmp=*this;++(*this);return tmp;}
		iterator&operator--(){
			if(outer_cur==outer_end){ // end() から戻る
				--outer_cur;
				inner_cur=outer_cur->end();
			}
			if(inner_cur==outer_cur->begin()){
				--outer_cur;
				inner_cur=outer_cur->end();
			}
			--inner_cur;
			return*this;
		}
		iterator operator--(int){auto tmp=*this;--(*this);return tmp;}
		bool operator==(const iterator&other)const{
			return outer_cur==other.outer_cur&&(outer_cur==outer_end||inner_cur==other.inner_cur);
		}
		bool operator!=(const iterator& other)const{return!(*this==other);}
	};
	struct const_iterator{
		using iterator_category=std::bidirectional_iterator_tag;
		using value_type=const T;
		using difference_type=std::ptrdiff_t;
		using pointer=const T*;
		using reference=const T&;
		using outer_iter=typename std::vector<std::vector<T>>::const_iterator;
		using inner_iter=typename std::vector<T>::const_iterator;
		outer_iter outer_cur,outer_end;
		inner_iter inner_cur;
		const_iterator()=default;
		const_iterator(outer_iter o_cur,outer_iter o_end,inner_iter i_cur):outer_cur(o_cur),outer_end(o_end),inner_cur(i_cur){}
		reference operator*()const{return*inner_cur;}
		pointer operator->()const{return&(*inner_cur);}
		const_iterator&operator++(){
			++inner_cur;
			if(outer_cur!=outer_end&&inner_cur==outer_cur->end()){
				++outer_cur;
				if(outer_cur!=outer_end){
					inner_cur=outer_cur->begin();
				}
			}
			return*this;
		}
		const_iterator operator++(int){auto tmp=*this;++(*this);return tmp;}
		const_iterator&operator--(){
			if(outer_cur==outer_end){
				--outer_cur;
				inner_cur=outer_cur->end();
			}
			if(inner_cur==outer_cur->begin()){
				--outer_cur;
				inner_cur=outer_cur->end();
			}
			--inner_cur;
			return*this;
		}
		const_iterator operator--(int){auto tmp=*this;--(*this);return tmp;}
		bool operator==(const const_iterator&other)const{
			return outer_cur==other.outer_cur&&(outer_cur==outer_end||inner_cur==other.inner_cur);
		}
		bool operator!=(const const_iterator&other)const{return!(*this==other);}
	};
	iterator begin(){
		if(list_.empty())return end();
		return iterator(list_.begin(),list_.end(),list_.front().begin());
	}
	iterator end(){
		return iterator(list_.end(),list_.end(),{});
	}
	const_iterator begin()const{return cbegin();}
	const_iterator end()const{return cend();}
	const_iterator cbegin()const{
		if(list_.empty())return cend();
		return const_iterator(list_.cbegin(),list_.cend(),list_.front().cbegin());
	}
	const_iterator cend()const{
		return const_iterator(list_.cend(),list_.cend(),{});
	}
	using reverse_iterator=std::reverse_iterator<iterator>;
	using const_reverse_iterator=std::reverse_iterator<const_iterator>;
	reverse_iterator rbegin(){return reverse_iterator(end());}
	reverse_iterator rend(){return reverse_iterator(begin());}
	const_reverse_iterator rbegin()const{return const_reverse_iterator(end());}
	const_reverse_iterator rend()const{return const_reverse_iterator(begin());}
	const_reverse_iterator crbegin()const{return const_reverse_iterator(cend());}
	const_reverse_iterator crend()const{return const_reverse_iterator(cbegin());}
	//constructer BEGIN:
	bucket_set():size_(0){}
	bucket_set(std::vector<T> z){
		if(!std::is_sorted(z.begin(),z.end()))std::sort(z.begin(),z.end());
		z.erase(std::unique(z.begin(),z.end()),z.end());
		int n=size_=z.size();
		int s=std::ceil(std::sqrt((double)n/kRatio));
		list_.resize(s);
		for(int i=0;i<s;i++)list_[i].assign(z.begin()+n*i/s,z.begin()+n*(i+1)/s);
	}
	bucket_set&operator=(const bucket_set&b){list_=b.list_,size_=b.size_;return*this;}
	bucket_set&operator=(bucket_set&&b){list_=std::move(b.list_),size_=b.size_;return *this;}
	//END constructer

	//utility BEGIN:
	bool empty()const{return !size_;}
	int size()const{return size_;}
	std::vector<std::vector<T>>&bucket(){return list_;}
	//END utility

	//operation BEGIN:
	void clear(){size_=0;list_.clear();}
	//return True if inserted 
	bool insert(T x){
		if(!size_){list_={{x}},size_=1;return true;}
		auto[b,bi,i]=_position(x);
		if(i!=(int)b->size()&&(*b)[i]==x)return false;
		b->insert(b->begin()+i,x);
		size_++;
		//split
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
	//erase and return ith elem.
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
	}
	void swap(bucket_set&b){
		std::swap(list_,b.list_);
		std::swap(size_,b.size_);
	}
	void merge(const bucket_set&b){
		std::vector<T> all;
		all.reserve(size_+b.size_);
		for(auto& a:list_)all.insert(all.end(),a.begin(),a.end());
		for(auto& a:b.list_)all.insert(all.end(),a.begin(),a.end());
		*this=std::move(bucket_set(all));
	}
	//END operation
	//access BEGIN:
	bool count(const T&x)const{
		if(!size_)return false;
		auto[b,_,i]=_position(x);
		return i!=(int)b->size()&&(*b)[i]==x;
	}
	bool find(const T&x)const{return count(x);}
	bool contains(const T&x)const{return count(x);}
	T operator[](int i)const{
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
	//lower/upper_bound return the item: type is T
	iterator lower_bound(const T&x)const{
		for(auto lt=list_.begin(),gt=list_.end();lt!=gt;++lt)if(!lt->empty()&&lt->back()>=x)
			return iterator(lt,gt,std::lower_bound(lt->begin(),lt->end(),x));
		return end();
	}
	iterator upper_bound(const T&x)const{
		for(auto lt=list_.begin(),gt=list_.end();lt!=gt;++lt)if(!lt->empty()&&lt->back()>x)
			return iterator(lt,gt,std::upper_bound(lt->begin(),lt->end(),x));
		return end();
	}
	int index(const T&x){
		int res=0;
		for(auto&a:list_){
			if(a.back()>=x)return res+(int)(std::lower_bound(a.begin(),a.end(),x)-a.begin());
			res+=a.size();
		}
		return res;
	}
	//END access
	//not member function a.k.a hidden friend BEGIN:
	friend bool operator==(const bucket_set&a,const bucket_set&b){return a.size_==b.size_&&a.list_==b.list_;}
	friend bool operator!=(const bucket_set&a,const bucket_set&b){return!(a==b);}
	friend bool operator<(const bucket_set&a,const bucket_set&b){return a.list_<b.list_;}
	friend bool operator<=(const bucket_set&a,const bucket_set&b){return a==b||a<b;}
	friend bool operator>(const bucket_set&a,const bucket_set&b){return b<a;}
	friend bool operator>=(const bucket_set&a,const bucket_set&b){return b<=a;}
	friend void swap(bucket_set&a,bucket_set&b){a.swap(b);}
	//END not member
};
