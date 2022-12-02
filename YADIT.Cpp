#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz =2e5+1;
const int ssz=5e3+1;
const int mod=1e9+7;
int p,n,q,timer,m;
long long a[sz];
long long pf[sz];
long long ans[sz];
vector<pair<long long,int>>pr;
pair<long long,int>dp[sz];
pair<long long,int>tree[sz<<2];
void build(int l = 1,int r = n,int p = 1){
     if(l==r){
          tree[p].first = INT_MAX;
          tree[p].second = l;
          return;
     }
     int mid = (l+r)>>1;
     build(l,mid,2*p);
     build(mid+1,r,2*p+1);
}
void update(long long val, int L,int R, int l = 1, int r = n, int p = 1){
    if(L > r or R < l) return;
    if(L <= l and r <= R){
         tree[p].first = min(val,tree[p].first);
         return;
    }
    int mid = (l+r)>>1;
    update(val,L,R,l,mid,2*p);
    update(val,L,R,mid+1,r,2*p+1);
    tree[p] = tree[2*p];
    if(tree[p].first > tree[2*p+1].first) tree[p] = tree[2*p+1];
}
pair<long long,int>query(int L,int R,int l = 1,int r = n,int p = 1){
      if(L > r or R < l) return{INT_MAX,0};
      if(L <= l and r <= R) return tree[p];
      int mid = (l+r)>>1;
      pair<long long,int> left = query(L,R,l,mid,2*p);
      pair<long long,int> right = query(L,R,mid+1,r,2*p+1);
      if(left.first < right.first) return left;
      else return right;
}
int main(){
      cin>>n;
      pr.push_back({0,0});
      for(int i = 1; i <= n; i++){
           long long x; cin>>x;
           pr.push_back({x,i});
      }
      sort(pr.begin(),pr.end());
      build();
      for(int i = 3; i < n; i++) update(pr[i].first-pr[1].first-pr[i+1].first,i,i);
      for(int i = 6; i <= n; i++){
             pair<long long,int> prefix = query(1,i-3);
             dp[i].first =  prefix.first + pr[i].first;
             dp[i].second = prefix.second;   
             if( i+1 <= n){
                  long long val = dp[i].first - pr[i+1].first;
                  update(val,i,i);
             }
      }
      if(n < 6){
          cout<<pr[n].first - pr[1].first<<' '<<1<<endl;
          for(int i = 1; i <= n; i++) cout<<1<<' ';
          return 0;
      }
      int cur = n;
      int to = 1;
      while(dp[cur].second != 0){
           int par = dp[cur].second;
           for(int i = par + 1; i <= cur; i++) ans[pr[i].second] = to;
           to++;
           cur = par;
      }
      cout<<dp[n].first<<' '<<to<<endl;
      for(int i = 1; i <= n; i++){
           if(!ans[i]) ans[i] = to;
           cout<<ans[i]<<' ';
      }
}
