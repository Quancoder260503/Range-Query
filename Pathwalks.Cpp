#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+1;
const int mod=1e9+7;
int p,n,q,timer,m;
long long d;
long long a[sz];
int freq[sz];
int cnt[sz];
int cntr[sz];
long long bit[sz];
set<pair<long long,int>>dp[sz];
int main(){
      cin>>n>>m;
      for(int i = 1; i <=n; i++) dp[i].insert({-1,0});
      long long ans = 0;
      for(int i = 1; i <= m; i++){
           long long u,v,w; 
           cin>>u>>v>>w;
           auto it = dp[u].lower_bound({w,0}); it--;
           int l = it->second + 1;
           auto itv = dp[v].lower_bound({w+1,0}); itv--;
           if(itv->second >= l) continue;
           if(itv->first < w) itv++; 
           while(itv!=dp[v].end()){
                if(itv->second <= l) dp[v].erase(itv++);
                else break;
           }
           dp[v].insert({w,l});
           ans = max(ans,(1ll)*l);
      }
      cout<<ans<<endl;
}
