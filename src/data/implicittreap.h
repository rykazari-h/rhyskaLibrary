#include<data/xorshift.h>
#include<vector>
template<class T,auto f=[](const T&a,const T&b)->T&{return a;}>class implicitTreap{

	struct Node{
		Node*l,*r;
		T prod,val;
		unsigned pri;
		int size;
		//bool rev;
		//T delta;
		Node(const T&k,unsigned p):val(k),prod(k),pri(p),l(NULL),r(NULL),size(1){}
	} *root=NULL;
	xorshift32 rnd;
	using Tree=Node*;
	inline int sz(Tree t){return !t?0:t->size;}
	inline Tree update(Tree t){
		//update size
		t->size=sz(t->l)+1+sz(t->r);
		//update prod
		t->prod=t->val;
		if(t->l)t->prod=f(t->l->prod,t->prod);
		if(t->r)t->prod=f(t->prod,t->r->prod);
		return t;
	}
	Tree kth(Tree t,int k){
		if(!t)return NULL;
		int ls=sz(t->l);
		if(k < ls)	return kth(t->l,k);
		if(k == ls)	return t;
		return kth(t->r,k-ls-1);
	}
	Tree merge(Tree a,Tree b){
		if(!a||!b)return !a ? b : a;
		if(a->pri < b->pri){
			b->l=merge(a,b->l);
			return update(b);
		}else{
			a->r=merge(a->r,b);
			return update(a);
		}
	}
	std::pair<Tree,Tree> split(Tree t,int k){
		if(!t)return {NULL,NULL};
		if(k <= sz(t->l)){
			Tree l;
			std::tie(l,t->l)=split(t->l,k);
			return {l,update(t)};
		}else{
			Tree r;
			std::tie(t->r,r)=split(t->r,k-sz(t->l)-1);
			return {update(t),r};
		}
	}
	Tree insert(Tree t,int k,Tree node){
		if(!t)return node;
		auto[l,r]=split(t,k);
		return merge(merge(l,node),r);
	}
	std::pair<Tree,T> erase(Tree t,int k){
		int ls=sz(t->l);
		T val;
		if(k < ls){std::tie(t->l,val)=erase(t->l,k);return {update(t),val};}
		if(k == ls){val=t->val;return {merge(t->l,t->r),val};}
		std::tie(t->r,val)=erase(t->r,k-ls-1);return {update(t),val};
	}
	inline void delete_node(Tree t){
		if(!t)return;
		delete_node(t->l);
		delete_node(t->r);
		delete t;
	}
	int fill_inorder(Tree t,std::vector<T>&arr,int i){
		if(!t)return i;
		i=fill_inorder(t->l,arr,i);
		arr[i]=t->val;
		return fill_inorder(t->r,arr,i+1);
	}

public:

	template<bool IsConst>struct iterator_base{
		using iterator_category=std::random_access_iterator_tag;
		using value_type=std::conditional_t<IsConst,const T,T>;
		using difference_type=std::ptrdiff_t;
		using pointer=std::conditional_t<IsConst,const T*,T*>;
		using reference=std::conditional_t<IsConst,const T&,T&>;
		implicitTreap*self;
		int idx;
		Tree root,node;
		iterator_base()=default;
		iterator_base(const iterator_base&b):self(b.self),idx(b.idx),root(b.root),node(b.node){}
		iterator_base(implicitTreap*self_,Tree root_,Tree node_,int idx_):self(self_),idx(idx_),root(root_),node(node_){}
		inline reference operator*()const{return node->val;}
		inline pointer operator->()const{return&node->val;}
		inline iterator_base&operator+=(int n){
			node=self->kth(root,idx+=n);
			return*this;
		}
		inline iterator_base operator+(int n)const{return iterator_base(*this)+=n;}
		inline iterator_base&operator-=(int n){return*this+=(-n);}
		inline iterator_base operator-(int n)const{return*this+(-n);}
		inline difference_type operator-(iterator_base b)const{return idx-b.idx;}
		inline iterator_base&operator++(){return(*this)+=1;}
		inline iterator_base operator++(int){auto tmp=*this;++(*this);return tmp;}
		inline iterator_base&operator--(){return(*this)-=1;}
		inline iterator_base operator--(int){auto tmp=*this;--(*this);return tmp;}
		inline bool operator==(const iterator_base&b)const{return idx == b.idx;}
		inline bool operator!=(const iterator_base&b)const{return!(*this == b);}
		inline bool operator<(const iterator_base&b)const{return idx < b.idx;}
		inline bool operator<=(const iterator_base&b)const{return*this<b||*this==b;}
		inline bool operator>(const iterator_base&b)const{return b<*this;}
		inline bool operator>=(const iterator_base&b)const{return b<=*this;}
		iterator_base&operator=(const iterator_base&b){self=b.self;idx=b.idx;root=b.root;node=b.node;return*this;}
		void swap(iterator_base&b){std::swap(self,b.self);std::swap(idx,b.idx);std::swap(root,b.root);std::swap(node,b.node);}
	};
	using iterator=iterator_base<false>;
	using const_iterator=iterator_base<true>;
	using reverse_iterator=std::reverse_iterator<iterator>;
	using const_reverse_iterator=std::reverse_iterator<const_iterator>;
	inline iterator begin()const{return empty?end():iterator(this,root,kth(root,0),0);}
	inline iterator end()const{return iterator(this,root,NULL,size());}
	inline const_iterator cbegin()const{return empty?cend():const_iterator(this,root,kth(root,0),0);}
	inline const_iterator cend()const{return const_iterator(this,root,NULL,size());}
	inline reverse_iterator rbegin()const{return reverse_iterator(end());}
	inline reverse_iterator rend()const{return reverse_iterator(begin());}
	inline reverse_iterator crbegin()const{return reverse_iterator(cend());}
	inline reverse_iterator crend()const{return reverse_iterator(cbegin());}
	implicitTreap()=default;
	inline int size(){return sz(root);}
	inline bool empty(){return !root;}
	inline void clear(){delete_node(root);root=NULL;}
	T& operator[](int k){return kth(root,k < 0 ? k+size():k)->val;}
	void set(int k,const T&x){
		auto[a,m]=split(root,k);
		auto[n,b]=split(m,1);
		n->val=x;
		update(n);
		root=merge(a,merge(n,b)); 
	}
	T& front(){return kth(root,0)->val;}
	T& back(){return kth(root,size()-1)->val;}
	void insert(int k,const T&x){root=insert(root,k < 0 ? k+size():k,new Node(x,rnd.random()));}
	void push(const T&x){root=insert(root,size()-1,new Node(x,rnd.random()));}
	template<class... U>void emplace(int k,U&&... x){insert(k,T(std::forward<U>(x)...));}
	void pop(int k=-1){erase(root,k < 0 ? k+size():k);}
	T prod(int l,int r){
		auto[a,m]=split(root,l);
		auto[n,b]=split(m,r-l);
		T res=n->prod;
		root=merge(a,merge(n,b));
		return res;
	}
	std::vector<T>to_a(){
		std::vector<T>res(size());
		fill_inorder(root,res,0);
		return res;
	}
};
