#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q;
long long a[N + 1];
vector<int>adj[N + 1]; 
int in[N + 1];
int out[N + 1];
int dp[N + 1];
int timer = 1; 
struct node{
    long long val;
    long long mval;
    long long lzadd;
} tree[N << 2];
void dfs(int u){
     in[u] = timer++;
     for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           dp[v] = dp[u] + 1;
           dfs(v);
     }
     out[u] = timer - 1;
}
void push_down(int p,int l,int mid,int r){
    if(tree[p].lzadd != 0){
        tree[2*p].mval += tree[p].lzadd; 
        tree[2*p+1].mval += tree[p].lzadd;
        tree[2*p].lzadd += tree[p].lzadd;
        tree[2*p+1].lzadd += tree[p].lzadd;
        tree[p].lzadd = 0;
    }
}
void update(long long x,int L,int R,int l = 1,int r = n + 1,int p = 1){
    if(L > r or R < l) return;
    if(L <= l and r <= R){
        tree[p].mval += x;
        tree[p].lzadd += x;
        return;
    }
      int mid = (l + r)>>1;
      push_down(p,l,mid,r);
      update(x,L,R,l,mid,2*p);
      update(x,L,R,mid+1,r,2*p+1);
      tree[p].mval = max(tree[2*p].mval,tree[2*p + 1].mval);
}
long long querymax(int L,int R,int l = 1,int r = n + 1 ,int p = 1){
     if(L > r or R < l) return 0;
     if(L <= l and r <= R) return tree[p].mval;
     int mid = (l + r)>>1;
     push_down(p,l,mid,r);
     return max(querymax(L,R,l,mid,2*p),querymax(L,R,mid+1,r,2*p + 1));   
}
int main(){
      scanf("%d%d",&n,&k);
      for(int i = 1; i <= n; i++) scanf("%d",&a[i]);
      stack<pair<int,int>>stacks;  
      stacks.push({INT_MAX,n + 1}); 
      for(int i = n; i > 0; i--){
           while(stacks.size() and stacks.top().first <= a[i])  stacks.pop();
           int to = stacks.top().second; 
           adj[to].push_back(i); 
           stacks.push({a[i],i});
      }
      dfs(n + 1); 
      for(int i = 1; i < k; i++){
          update(1,in[i],out[i]);
      }
      for(int i = k; i <= n; i++){
            update(-1,in[i - k],out[i - k]);
            update(1,in[i],out[i]); 
            long long ans = querymax(1, n + 1); 
            cout<<ans<<' ';
      }
}
