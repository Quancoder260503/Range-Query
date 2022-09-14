#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1001;
const int sz1=1e5+1;
int n,k,w,m,q;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
ll dp[sz][sz];
char p[sz][sz];
int main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>p[i][j];
        }
    } 
    if(p[1][1]=='*')  dp[1][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if (i==1){
                dp[i][j]=dp[i][j-1];
                if(p[i][j]=='*') dp[i][j]++;
            }if (j==1){
                dp[i][j]=dp[i-1][j];
                if(p[i][j]=='*') dp[i][j]++;
            }if (i>1 and j>1){
                dp[i][j]=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
                if(p[i][j]=='*') dp[i][j]++;
            }
        }
    } 
    for(int i=0;i<q;i++){
          int u,v,x,y;
          cin>>u>>v>>x>>y;
          ll res=dp[x][y]+dp[u-1][v-1]-dp[u-1][y]-dp[x][v-1];
          cout<<res<<endl;
    }
}