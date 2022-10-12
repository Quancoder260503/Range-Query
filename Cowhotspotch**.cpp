#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=755;
const int mod=1e9+7;
int n,m,k;
int a[sz][sz];
ll bit[sz];
map<ll,ll>bit_col[sz];
ll dp[sz][sz];
struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            upd(i, a[i]);
    }

    ll query(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    ll sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void upd(int idx, ll delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
} bit[sz];
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++){
      for(int j=1;j<=m;j++){
          cin>>a[i][j];
       }
    }
    bit[a[1][1]].upd(1,1);
    bit[0].upd(1,1);
    for(int i=2;i<=n;i++){
      for(int j=2;j<=m;j++){
           dp[i][j]=bit[0].query(j-1)-bit[a[i][j]].query(j-1,a[i][j]);
           if(dp[i][j]<0) dp[i][j]+=mod;
      }
      for(int j=2;j<=m;j++){
          bit]ao.upd(j,a[i][j],dp[i][j]);
          if(!dp[i][j]) continue;
          upd(j,dp[i][j]);
       }
    } 
    cout<<(dp[n][m])%mod<<endl;
}
  
