#include<data/rmodint.h>
#include<array>
bool isprime_fast(long long x) {
	if(x == 2)return 1;
	if(x < 2 || !(x&1))return 0;
	auto mil{[&x](auto arr){
		using mint=rmodint<0>;
		mint::setmod(x);
		long long s=0,d=x-1;
		for(;!(d&1);d>>=1)++s;
		for(auto a:arr){
			if(x<=a)return 1;
			mint z = mint(a).pow(d);
			if(z == 1)continue;
			long long t{};
			for(;t<s;++t,z*=z)if(z == x-1)break;
			if(t == s)return 0;
		}
		return 1;
	}};
	return x < 4759123141LL ? mil(std::array<int,3>{2,7,61}):mil(std::array<int,7>{2,325,9375,28178,450775,9780504,1795265022});
}
