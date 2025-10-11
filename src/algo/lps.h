#include<vector>
std::vector<int> lps_gen(std::string s){
    int n=s.size();
    std::vector<int> lps(n);
    for(int i=1;i<n;i++){
        int l=lps[i-1];
        while(l&&s[i]!=s[l])l=lps[l-1];
        lps[i]=s[i]==s[l]?l+1:l;
    }
    return lps;
}
