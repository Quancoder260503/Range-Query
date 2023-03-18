#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 5e5 + 10;
const long long INF = 1e17;
const int N = (1 << 19);
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x,ans,t;
long long na,nb,nc; 
long long a[N + 1]; 
int timer = 0;
map<long long,long long>mp; 
struct node{
     long long val; 
     int l,r; 
} tree[N * 22];
int root[N + 1]; 
int build(int l = 1, int r = n){
      if(l == r){
            tree[++timer].val = INF;
            return timer; 
      } 
      int mid = (l + r) >> 1;
      int node = ++timer;
      tree[node].l = build(l,mid);
      tree[node].r = build(mid + 1,r);
    //   cout << node << ' ' << tree[node].l <<' ' << tree[node].r << endl; 
      tree[node].val = min(tree[tree[node].l].val,tree[tree[node].r].val);
      return node; 
}
int update(int cur,int val,int pos,int l = 1,int r = n){
      if(l == r){
           tree[++timer].val = val; 
           return timer; 
      }
      int mid = (l + r) >> 1;
      int node = ++timer; 
      if(pos > mid){
           tree[node].l = tree[cur].l; 
           tree[node].r = update(tree[cur].r,val,pos,mid + 1,r);
      }
      else{
          
          tree[node].r = tree[cur].r; 
          tree[node].l = update(tree[cur].l,val,pos,l,mid); 
      }
      tree[node].val = min(tree[tree[node].l].val,tree[tree[node].r].val); 
      return node; 
}
long long query(int cur, int L, int R,int l = 1,int r = n){
      if(L > r or R < l) return INF;
      if(L <= l and r <= R) return tree[cur].val; 
      int mid = (l + r) >> 1; 
      return min(query(tree[cur].l, L, R, l, mid),query(tree[cur].r, L, R, mid + 1,r));
}
int main(){
      scanf("%d%d",&n,&q);
      root[n + 1] = build(); 
      for(int i = 1; i <= n; i++) scanf("%lld",&a[i]); 
      for(int i = n; i > 0; i--){
           if(!mp.count(a[i])){
                root[i] = root[i + 1];
                mp[a[i]] = i; 
           }
           else{
                root[i] = update(root[i + 1],mp[a[i]] - i,mp[a[i]]);
                mp[a[i]] = i;
           }
      }
      int l,r; 
      for(int i = 0; i < q; i++){
           scanf("%d%d",&l,&r);
           long long ans = query(root[l],l,r); 
           if(ans < INF) printf("%lld\n",ans); 
           else printf("%d\n",-1); 
      }
      return 0; 
}
