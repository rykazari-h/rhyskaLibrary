#pragma once
#include <vector>
#include <cmath>
struct prime{
	using int64 = long long;
	std::vector<bool> sieve;
	prime(int64 x):sieve(x+1, true){
		sieve[0] =sieve[1] = false;
		const int64 x_2 = std::ceil(std::sqrt(x)+0.1);
		for (int64 p = 2; p < x_2; p++) {
			if (!sieve[p]) continue;
			for (int64 q = p*p; q < x;q+=p) sieve[q] = false;
		}
	}
};
