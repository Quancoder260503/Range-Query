#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
const int mod=1e9+7;
int p,n,q,timer;
long long d;
int bit[sz];
ll a[sz];
pair<ll,int>dp[sz];
ll h[sz];
pair<ll,int>tree[sz<<2];
void update(int idx,int val, int L, int R, int l = 1,int r = n,int p = 1){
      if(L > r or R < l) return;
      if(l == r){
           if(tree[p].first < val){
                tree[p].first = val;
                tree[p].second = idx;
           }
           return;
      }
      int mid = (l+r)>>1;
      update(idx,val,L,R,l,mid,2*p);
      update(idx,val,L,R,mid+1,r,2*p+1);
      if(tree[2*p].first < tree[2*p+1].first) tree[p] = tree[2*p+1];
      else tree[p] = tree[2*p];
}
pair<long long,int>query(int L,int R, int l = 1, int r = n, int p = 1){
      if(L > r or R < l) return {0,0};
      if(L<= l and r <= R) return tree[p];
      int mid = (l+r)>>1;
      pair<long long,int> left = query(L,R,l,mid,2*p);
      pair<long long,int> right = query(L,R,mid+1,r,2*p+1);
      if(left.first < right.first) return right;
      else return left;
}
int main(){
       cin>>n>>d;
       vector<ll>heights;
       for(int i = 1; i <= n ; i++){
           cin>>h[i];
           heights.push_back(h[i]);
       }
       for(int i = 0; i <= n; i++) dp[i].second = -1;
       sort(heights.begin(),heights.end());
       heights.erase(unique(heights.begin(),heights.end()),heights.end());
       map<long long,int>mp;
       int ans = 0;
       int ans_pos = 0;
       // h[i] - d >= h[j] or h[j] >= h[i] + d 
       for(int i = 0; i < heights.size();i++) mp[heights[i]] = i+1;
       for(int i = 1; i <= n; i++){
             long long l = h[i] - d;
             long long r = h[i] + d;
             int posl = lower_bound(heights.begin(),heights.end(),l)-heights.begin();
             int posr = lower_bound(heights.begin(),heights.end(),r)-heights.begin();
             if(l == heights[posl]) posl++;
             pair<long long,int>right = query(posr+1,n);
             pair<long long,int>left  = query(1,posl);
             dp[i].first = 1 + max(left.first,right.first);
             if(left.first < right.first) dp[i].second = right.second;
             else dp[i].second = left.second;
             update(i,dp[i].first,mp[h[i]],mp[h[i]]);
             if(dp[i].first > ans){
                  ans = dp[i].first;
                  ans_pos = i;
             }
       }
       cout<<ans<<endl;
       vector<int>res;
       while(dp[ans_pos].second != -1){
            res.push_back(ans_pos);
            ans_pos = dp[ans_pos].second;
       }
       reverse(res.begin(),res.end());
       for(int i = 0; i < res.size(); i++) cout<<res[i]<<' ';
}
