#include<algorithm>
namespace intersct{
	template<class T>int sub(std::pair<T,T>&p,std::pair<T,T>&q,std::pair<T,T>&r){
		T v=(q.first-p.first)*(r.second-p.second)-(q.second-p.second)*(r.first-p.first);
		return v>(T)(0)?1:v==(T)(0)?0:-1;
	}
}
template<class T>bool intersect(std::pair<T,T>&p,std::pair<T,T>&q,std::pair<T,T>&r,std::pair<T,T>&s){
	if(std::max(p.first,q.first)<std::min(r.first,s.first)||std::max(r.first,s.first)<std::min(p.first,q.first)||std::max(p.second,q.second)<std::min(r.second,s.second)||std::max(r.second,s.second)<std::min(p.second,q.second))return 0;
	return intersct::sub(p,q,r)*intersct::sub(p,q,s)<=0&&intersct::sub(r,s,p)*intersct::sub(r,s,q)<=0;
}
