#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
int kmax;
long long solve(vector<vector<int>>& memory,int i,int j,int n,int m,int k){
    if(i>=n or j>=m)return INT_MIN;
    if(i==n-1 and j==m-1)return 0;
    int take_r=0,take_d=0,skip_r=0,skip_d=0;
    if(k){
        take_d=memory[i][j]+solve(memory,i+1,j,n,m,kmax);
        take_r=memory[i][j]+solve(memory,i,j+1,n,m,k-1);
    }
    skip_d=solve(memory,i+1,j,n,m,kmax);
    skip_r=solve(memory,i,j+1,n,m,k);
    return max({take_d,take_r,skip_d,skip_r});
    
}

long long maximumMemory(vector<vector<int>>& memory, int k){
    int n=memory.size();
    int m=memory[0].size();
    kmax=k;
    return solve(memory,0,0,n,m,k);
}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    

    return 0;
}
