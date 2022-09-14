#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=998244353;
int n,x,k,i,q,j,w,m;
ll a[sz];
ll tree[sz<<2];
ll lztree[sz<<2];
ll lzcnt[sz<<2];
void push(int p){
    tree[p]=tree[2*p]+tree[2*p+1];
}
void push_down(int p,int l,int mid,int r){
    if(lztree[p]!=0){
         ll t=-2*lztree[p]+lzcnt[p]*(mid+l+2);
         ll t1=-2*lztree[p]+lzcnt[p]*(r+mid+3);
         tree[2*p]+=(((ll) t*(ll) (mid-l+1))/2);
         tree[2*p+1]+=(((ll) t1* (ll) (r-mid))/2);
         lzcnt[2*p]+=lzcnt[p];
         lzcnt[2*p+1]+=lzcnt[p];
         lztree[2*p]+=lztree[p];
         lztree[2*p+1]+=lztree[p];
         lztree[p]=lzcnt[p]=0;
    }
}
void build(int l=1,int r=n,int p=1){
    if(l==r){
        tree[p]=a[l];
        return;
    }   
        int mid=(l+r)>>1;
        build(l,mid,2*p);
        build(mid+1,r,2*p+1);
        push(p);
}
void update(int L,int R,int l=1,int r=n,int p=1){
    if(l>R or r<L) return;
    if(L<=l and r<=R){
        int x=l-L;
        int y=r-L+1;
        lztree[p]+=L;
        lzcnt[p]++;
        ll t=(ll)y*(y+1)-(ll)x*(x+1); t/=2;
        tree[p]+=t;
        return;
    } 
      int mid=(l+r)>>1;
      push_down(p,l,mid,r);
      update(L,R,l,mid,2*p);
      update(L,R,mid+1,r,2*p+1);
      push(p);
}
ll query(int L,int R,int l=1,int r=n,int p=1){
    if(l>R or r<L) return 0 ;
    if(L<=l and r<=R){
      return tree[p];
   }
    int mid=(l+r)>>1;
    push_down(p,l,mid,r);
    return query(L,R,l,mid,2*p)+query(L,R,mid+1,r,2*p+1);
}
int main(){
      cin>>n>>q;
      for(int i=1;i<=n;i++) cin>>a[i];
      build();
      for(int i=0;i<q;i++){
          int t,u,v; cin>>t>>u>>v;
          if(t==1) update(u,v);
          else{
              ll res=query(u,v);
              cout<<res<<endl;
          }
      }
}