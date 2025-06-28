#include<bits/stdc++.h>
struct Timer{
	std::chrono::high_resolution_clock::time_point st;
	Timer():st(std::chrono::high_resolution_clock::now()){}
	void show(std::string label="time")const{
		auto ed = std::chrono::high_resolution_clock::now();
		std::cout<<label<<" : "<<(std::chrono::duration<long double>(ed-st).count())*1000<<" ms\n";
	}
};
