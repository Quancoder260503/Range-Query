#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 3e5 + 10;
const long long INF = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p;
vector<int>adj[N + 1];
long long a[N + 1];
long long dp[N + 1][20];
long long b[N + 1];
int main(){
      scanf("%d%d",&n,&q);
      for(int i = 1; i <= n; i++){
           scanf("%lld",&a[i]);
           for(int j = 0; j < 20; j++){
                if(a[i] & (1 << j)){
                     dp[i][j] = i; 
                }
                else{ 
                    for(int k = 0; k < 20; k++){
                          if((a[i] & (1 << k)) && b[k]){
                                dp[i][j] = max(dp[i][j], dp[b[k]][j]); 
                          }
                    }
                }
           }
           for(int j = 0; j < 20; j++){
                 if(a[i] & (1 << j)) b[j] = i;  
           }
      }
      for(int i = 0; i < q; i++){
           int l,r; scanf("%d%d",&l,&r);
           bool reach = 0; 
           for(int j = 0; j < 20; j++){                  
                  if(dp[r][j] > l && (a[l] & (1ll << j))){
                        reach = 1;
                        break; 
                  }                
           }
           if(reach) printf("Shi\n"); 
           else printf("Fou\n"); 
      }
      return 0;
}
