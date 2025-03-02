//bitceil_and_back0cnt.begin
#if __cplusplus >= 202002L
#include <bit>
#endif
#if __cplusplus >= 202002L
using std::bit_ceil;
#else
unsigned int bit_ceil(unsigned int n){
	unsigned int x=1;
	while(x<n)x*=2;
	return x;
}
#endif
int cnt0(unsigned int n){
	return __builtin_ctz(n);
}
//bitceil_and_back0cnt.end
//seg.begin
template<class S,S(*op)(S,S),S(*e)()>struct segtree{
	public:
		segtree():segtree(0){}
    explicit segtree(int n):segtree(vector<S>(n,e())){}
    explicit segtree(const vector<S>&v):_n(int(v.size())) {
	    size=(int)bit_ceil((unsigned int)(_n));
      lo=cnt0((unsigned int)size);
      d=vector<S>(2*size,e());
      for(int i=0;i<_n;i++)d[size + i] = v[i];
      for(int i=size-1;i>=1;i--)update(i);
    }
    void set(int p,S x){
      p+=size;
      d[p]=x;
      for(int i=1;i<=lo;i++)update(p >> i);
    }
    S get(int p)const{
      return d[p+size];
    }
    S prod(int l,int r)const{
      S sml=e(),smr=e();
      l+=size;
      r+=size;
      while(l<r){
        if(l&1)sml=op(sml,d[l++]);
        if(r&1)smr=op(d[--r],smr);
        l>>=1;
        r>>=1;
      }
      return op(sml,smr);
    }
    S all_prod()const{return d[1];}
    template<bool(*f)(S)>int max_right(int l)const{
      return max_right(l,[](S x){return f(x);});
    }
    template<class F>int max_right(int l,F f)const{
      if(l==_n)return _n;
      l+=size;
      S sm=e();
      do{
        while(l%2==0)l>>=1;
        if (!f(op(sm,d[l]))){
          while (l<size){
            l=(2*l);
            if(f(op(sm,d[l]))){
              sm=op(sm,d[l]);
              l++;
            }
          }
	        return l-size;
        }
        sm=op(sm,d[l]);
        l++;
      }while((l&-l)!=l);
        return _n;
    }
		template<bool(*f)(S)>int min_left(int r)const{
      return min_left(r,[](S x){return f(x);});
    }
    template<class F>int min_left(int r,F f)const{
      if(r==0)return 0;
      r+=size;
      S sm=e();
      do{
				r--;
        while(r%2&&r>1)r>>=1;
        if (!f(op(d[r],sm))){
          while (r<size){
            r=(2*r+1);
            if(f(op(d[r],sm))){
              sm=op(d[r],sm);
              r--;
            }
          }
	        return r+1-size;
        }
        sm=op(d[r],sm);
      }while((r&-r)!=r);
        return 0;
    }
private:
		int _n,size,lo;
		vector<S>d;
		void update(int k){d[k]=op(d[2*k],d[2*k+1]);}
};
