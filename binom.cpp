vector<vector<long long>>binom(int n){
    vector C(n+1,vector<long long>(n+1,0));
    for(int i=0;i<=n;i++){
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++){
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
    return C;
}