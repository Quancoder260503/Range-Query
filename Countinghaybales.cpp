#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,x,k,i,j,w,q,y;
ll a[sz];
struct node{
    ll val;
    ll mval;
    ll lzadd;
} tree[sz<<2];
void build(int l=1,int r=n,int p=1){
    if(l==r){
        tree[p].val=tree[p].mval=a[l];
        return;
    } int mid=(l+r)>>1;
      build(l,mid,2*p);
      build(mid+1,r,2*p+1);
      tree[p].val=tree[2*p].val+tree[2*p+1].val;
      tree[p].mval=min(tree[2*p].mval,tree[2*p+1].mval);
}
void push_down(int p,int l,int mid,int r){
    if(tree[p].lzadd!=0){
        tree[2*p].val+=(mid-l+1)*tree[p].lzadd;
        tree[2*p+1].val+=(r-mid)*tree[p].lzadd;
        tree[2*p].mval+=tree[p].lzadd; tree[2*p+1].mval+=tree[p].lzadd;
        tree[2*p].lzadd+=tree[p].lzadd;
        tree[2*p+1].lzadd+=tree[p].lzadd;
        tree[p].lzadd=0;
    }
}
void update(ll x,int L,int R,int l=1,int r=n,int p=1){
    if(L>r or R<l ) return;
    if(L<=l and r<=R){
        tree[p].val+=(r-l+1)*x;
        tree[p].mval+=x;
        tree[p].lzadd+=x;
        return;
    }
      int mid=(l+r)>>1;
      push_down(p,l,mid,r);
      update(x,L,R,l,mid,2*p);
      update(x,L,R,mid+1,r,2*p+1);
      tree[p].val=tree[2*p].val+tree[2*p+1].val;
      tree[p].mval=min(tree[2*p].mval,tree[2*p+1].mval);
}
ll querys(int L,int R,int l=1,int r=n,int p=1){
     if(L>r or R<l ) return 0 ;
     if(L<=l and r<=R) return tree[p].val;
     int mid=(l+r)>>1;
     push_down(p,l,mid,r);
     return querys(L,R,l,mid,2*p)+querys(L,R,mid+1,r,2*p+1);   
}
ll querymn(int L,int R,int l=1,int r=n,int p=1){
     if(L>r or R<l ) return INT_MAX ;
     if(L<=l and r<=R) return tree[p].mval;
     int mid=(l+r)>>1;
     push_down(p,l,mid,r);
     return min(querymn(L,R,l,mid,2*p),querymn(L,R,mid+1,r,2*p+1));   
}
int main(){
     cin>>n>>q;
     for(int i=1;i<=n;i++) cin>>a[i];
     build();
     for(int i=0;i<q;i++){
         char t; cin>>t;
         if(t=='M'){
             ll u,v;cin>>u>>v;
             ll res=querymn(u,v);
             cout<<res<<endl;
         } else if(t=='P'){
             ll u,v,d;cin>>u>>v>>d;
             update(d,u,v);
         } else if(t=='S'){
             ll u,v;cin>>u>>v;
             ll res=querys(u,v);
             cout<<res<<endl;
         }
     }
}