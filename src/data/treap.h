#include<vector>
#include<functional>
template<class T,auto f=[](const T&a,const T&b)->T&{return a;}>class Treap{

	struct Node{
		Node*l,*r;
		T prod,key;
		unsigned pri;
		int size;
		Node(const T&k,unsigned p):key(k),prod(k),pri(p),l(NULL),r(NULL),size(1){}
	} *root=NULL;

	using Tree=Node*;
	inline int sz(Tree&t){return !t?0:t->size;}
	inline Tree update(Tree t){
		t->size=sz(t->l)+1+sz(t->r);
		t->prod=t->key;
		if(t->l)t->prod=f(t->l->prod,t->prod);
		if(t->r)t->prod=f(t->prod,t->r->prod);
		return t;
	}
	Tree kth(Tree t,int k)const{
		if(!t)return NULL;
		int ls=sz(t->l);
		if(k < ls)return kth(t->l,k);
		else if(k == ls)return t;
		else return kth(t->r,k-ls-1);
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
	//[v|v<-self,v<x],[v|v<-self,x<=v]にsplit(不正でないことが前提)
	std::pair<Tree,Tree> split_less(Tree t,const T&x){
		if(!t)return {NULL,NULL};
		if(x <= t->key){
			auto[l,r]=split_less(t->l,x);
			t->l=r;
			return {l,update(t)};
		}else{
			auto[l,r]=split_less(t->r,x);
			t->r=l;
			return {update(t),r};
		}
	}
	//[v|v<-self,v<=x],[v|v<-self,x<v]にsplit(不正でないことが前提)
	std::pair<Tree,Tree> split_leq(Tree t,const T &x){
		if(!t)return {NULL,NULL};
		if(x < t->key){
			auto[l,r]=split_leq(t->l,x);
			t->l=r;
			return {l,update(t)};
		}else{
			auto[l,r]=split_leq(t->r,x);
			t->r=l;
			return {update(t),r};
		}
	}
	//self[...k],self[k..]にsplit(いつもの)
	std::pair<Tree,Tree> split_index(Tree t,int k){
		if(!t)return {NULL,NULL};
		if(k <= sz(t->l)){
			Tree l;
			std::tie(l,t->l)=split_index(t->l,k);
			return {l,update(t)};
		}else{
			Tree r;
			std::tie(t->r,r)=split_index(t->r,k-sz(t->l)-1);
			return {update(t),r};
		}
	}
	Tree insert(Tree t, Tree node){
		if(!t)return node;
		if(t->pri < node->pri){std::tie(node->l,node->r)=split_less(t,node->key);return update(node);}
		if(node->key < t->key){t->l=insert(t->l,node);return update(t);}
		t->r=insert(t->r,node);return update(t);
	}
	Tree erase(Tree t,const T&x){
		if(!t)return NULL;
		if(x == t->key){Tree res=merge(t->l,t->r);/*delete t;*/return res;}
		if(x < t->key){t->l=erase(t->l,x);return update(t);}
		t->r=erase(t->r,x);return update(t);
	}
	// アクセスが不正でないことを前提とする
	std::pair<Tree,T> erase_index(Tree t,int k){
		int ls=sz(t->l);
		T val;
		if(k < ls){std::tie(t->l,val)=erase_index(t->l,k);return {update(t),val};}
		if(k == ls){val=t->key;return {merge(t->l,t->r),val};}
		std::tie(t->r,val)=erase_index(t->r,k-ls-1);return {update(t),val};
	}
	void delete_node(Tree t){
		if(!t)return;
		delete_node(t->l);
		delete_node(t->r);
		delete t;
	}
	int fill_inorder(Tree t,std::vector<T>&arr,int i){
		if(!t)return i;
		i=fill_inorder(t->l,arr,i);
		arr[i]=t->key;
		return fill_inorder(t->r,arr,i+1);
	}

public:

	struct iterator{
		using iterator_category=std::random_access_iterator_tag;
		using value_type=const T;
		using difference_type=std::ptrdiff_t;
		using pointer=const T*;
		using reference=const T&;
		Treap*self;
		int idx;
		Tree root,node;
		iterator()=default;
		iterator(const iterator&b):self(b.self),idx(b.idx),root(b.root),node(b.node){}
		iterator(Treap*self_,Tree root_,Tree node_,int idx_):self(self_),idx(idx_),root(root_),node(node_){}
		reference operator*()const{return node->key;}
		pointer operator->()const{return&node->key;}
		iterator&operator+=(int n){
			node=self->kth(root,idx+=n);
			return*this;
		}
		iterator operator+(int n)const{return iterator(*this)+=n;}
		iterator&operator-=(int n){return*this+=(-n);}
		iterator operator-(int n)const{return*this+(-n);}
		difference_type operator-(iterator b)const{return idx-b.idx;}
		iterator&operator++(){return(*this)+=1;}
		iterator operator++(int){auto tmp=*this;++(*this);return tmp;}
		iterator&operator--(){return(*this)-=1;}
		iterator operator--(int){auto tmp=*this;--(*this);return tmp;}
		bool operator==(const iterator&b)const{return idx == b.idx;}
		bool operator!=(const iterator&b)const{return!(*this == b);}
		bool operator<(const iterator&b)const{return idx < b.idx;}
		bool operator<=(const iterator&b)const{return*this<b||*this==b;}
		bool operator>(const iterator&b)const{return b<*this;}
		bool operator>=(const iterator&b)const{return b<=*this;}
		iterator&operator=(const iterator&b){self=b.self;idx=b.idx;root=b.root;node=b.node;return*this;}
		void swap(iterator&b){std::swap(self,b.self);std::swap(idx,b.idx);std::swap(root,b.root);std::swap(node,b.node);}
	};
	using const_iterator=iterator;
	using reverse_iterator=std::reverse_iterator<iterator>;
	using const_reverse_iterator=reverse_iterator;
	iterator begin()const{return empty?end():iterator(this,root,kth(root,0),0);}
	iterator end()const{return iterator(this,root,NULL,size());}
	iterator cbegin()const{return begin();}
	iterator cend()const{return end();}
	reverse_iterator rbegin()const{return reverse_iterator(end());}
	reverse_iterator rend()const{return reverse_iterator(begin());}
	reverse_iterator crbegin()const{return reverse_iterator(end());}
	reverse_iterator crend()const{return reverse_iterator(begin());}
	Treap()=default;
	int size(){return sz(root);}
	bool empty(){return !root?1:0;}
	void clear(){delete_node(root);root=NULL;}
	void insert(const T&x){root=insert(root,new Node(x,((unsigned)rand() << 16) ^ rand()));}
	template<class... U>void emplace(U&&... x){insert(T(std::forward<U>(x)...));}
	void erase(const T&x){root=erase(root,x);}
	void erase_all(const T&x){
		auto[a,m]=split_less(root,x);
		auto[e,b]=split_leq(m,x);
		// delete_node(e);
		root=merge(a,b);
	}
	T pop(int k=-1){
		if(k < 0)k+=size();
		T v;
		std::tie(root,v)=erase_index(root,k);
		return v;
	}
	T operator[](int k){
		if(k < 0)k+=size();
		return kth(root,k)->key;
	}
	int count(const T&x){return index_rg(root,x)-index(root,x);}
	iterator find(const T&x){
		auto it=lower_bound(x);
		return it == end() || *it != x ? end() : it;
	}
	bool contains(const T&x){
		Tree t=root;
		if(!t)return 0;
		while(t)
			if(x == t->key)return 1;
			else if(x < t->key)t=t->l;
			else t=t->r;
		return 0;
	}
	int index(Tree t,const T&x){
		if(!t)return 0;
		if(x <= t->key)return index(t->l,x);
		return 1+sz(t->l)+index(t->r,x);
	}
	int index_rg(Tree t,const T&x){
		if(!t)return 0;
		if(x < t->key)return index(t->l,x);
		return 1+sz(t->l)+index(t->r,x);
	}
	iterator lower_bound(const T&x){
		Tree t=root,best=NULL;
		int idx=0,best_idx=0;
		while(t)
			if(x <= t->key){
				best=t;
				best_idx=idx+sz(t->l);
				t=t->l;
			}else{
				idx+=1+sz(t->l);
				t=t->r;
			}
		return !best?end():iterator(this,root,best,best_idx);
	}
	iterator upper_bound(const T&x){
		Tree t=root,best=NULL;
		int idx=0,best_idx=0;
		while(t)
			if(x < t->key){
				best=t;
				best_idx=idx+sz(t->l);
				t=t->l;
			}else{
				idx+=1+sz(t->l);
				t=t->r;
			}
		return !best?end():iterator(this,root,best,best_idx);
	}
	T operator()(int l,int r){
		if(l < 0)l+=size();
		if(r < 0)r+=size();
		auto[a,mr]=split_index(root,l);
		auto[m,b]=split_index(mr,r-l);
		T res=m->prod;
		root=merge(a,merge(m,b));
		return res;
	}
	T prod(int l,int r){
		return this->operator()(l,r);
	}
	std::pair<Treap,Treap> split_less(const T&x){
		auto[a,b]=split_less(root,x);
		Treap l,r;
		l.root=a,r.root=b;
		return {l,r};
	}
	std::pair<Treap,Treap> split_leq(const T&x){
		auto[a,b]=split_leq(root,x);
		Treap l,r;
		l.root=a,r.root=b;
		return {l,r};
	}
	std::pair<Treap,Treap> split_index(const T&k){
		auto[a,b]=split_index(root,k);
		Treap l,r;
		l.root=a,r.root=b;
		return {l,r};
	}
	operator std::vector<T>(){
		return to_a();
	}
	std::vector<T> to_a(){
		std::vector<T>res(size());
		fill_inorder(root,res,0);
		return res;
	}
};
