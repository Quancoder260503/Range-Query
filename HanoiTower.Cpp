#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
const int mod=1e9+7;
int p,n,q,timer;
long long d;
int bit[sz];
ll a[sz];
long long dp[sz];
vector<array<long long,3>>rings;
vector<long long>ycor;
long long tree[sz<<2];
void update(long long val, int L, int R, int l = 1, int r = n, int p = 1){
     if(L > r or R < l) return;
     if(l == r){
          if(tree[p] < val) tree[p] = val;
          return;
     }
     int mid = (l+r)>>1;
     update(val,L,R,l,mid,2*p);
     update(val,L,R,mid+1,r,2*p+1);
     tree[p] = max(tree[2*p],tree[2*p+1]);
}
long long query(int L,int R,int l = 1, int r = n, int p = 1){
     if(L > r or R < l) return 0;
     if(L <= l and r <= R) return tree[p];
     int mid = (l+r)>>1;
     return max(query(L,R,l,mid,2*p),query(L,R,mid+1,r,2*p+1));
}
int main(){
      cin>>n;
      for(int i = 1; i <= n; i++){
           long long x,y,h; cin>>x>>y>>h;
           ycor.push_back(y);
           rings.push_back({y,x,h});
      }
      sort(rings.begin(),rings.end());
      sort(ycor.begin(),ycor.end());
      ycor.erase(unique(ycor.begin(),ycor.end()),ycor.end());
      map<long long,int>mp;
      // b[i] >= b[j] and b[j] > a[i]
      for(int i = 0; i < ycor.size(); i++) mp[ycor[i]] = i+1;
      long long ans = 0;
      for(int i = 0; i < rings.size(); i++){
           array<long long,3> ring = rings[i];
           int pos =upper_bound(ycor.begin(),ycor.end(),ring[1])-ycor.begin();
           long long mx = query(pos+1,n);
           dp[i] = ring[2] + mx;
           ans = max(ans,dp[i]);
           update(dp[i],mp[ring[0]],mp[ring[0]]);
      }
      cout<<ans<<endl;
}
