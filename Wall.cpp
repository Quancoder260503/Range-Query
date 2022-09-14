#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e6+5;
const int inf=1e9;
int n,x,k,i,j,w,q,y;
struct node{
    ll mxval;
    ll lzadd;
    ll lzadd1;
    ll mnval;
} tree[sz<<2];
void padd(int p,ll x){
    tree[p].mxval=max(tree[p].mxval,x);
    tree[p].mnval=max(tree[p].mnval,x);
    tree[p].lzadd=max(tree[p].lzadd,x);
    tree[p].lzadd1=max(tree[p].lzadd1,x);
}
void pre(int p,ll x){
    tree[p].mxval=min(tree[p].mxval,x);
    tree[p].mnval=min(tree[p].mnval,x);
    tree[p].lzadd=min(tree[p].lzadd,x);
    tree[p].lzadd1=min(tree[p].lzadd1,x);
}
void push_down(int p){
    if(tree[p].lzadd!=inf){
        ll x=tree[p].lzadd;
        pre(2*p,x);
        pre(2*p+1,x);
        tree[p].lzadd=inf;
    }
    if(tree[p].lzadd1!=-inf){
        ll x=tree[p].lzadd1;
        padd(2*p,x);
        padd(2*p+1,x);
        tree[p].lzadd1=-inf;
    }
}
void build(int l=1,int r=n,int p=1){
    tree[p].lzadd=inf;tree[p].lzadd1=-inf;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l,mid,2*p);
    build(mid+1,r,2*p+1);
}
void add(ll x,int L,int R,int l=1,int r=n,int p=1){
     if(l>R or L>r) return;
     if(L<=l and r<=R){
        padd(p,x);
        return;
     } 
       int mid=(l+r)>>1;
       push_down(p);
       add(x,L,R,l,mid,2*p);
       add(x,L,R,mid+1,r,2*p+1);
       tree[p].mxval=max(tree[2*p].mxval,tree[2*p+1].mxval);
       tree[p].mnval=min(tree[2*p].mnval,tree[2*p+1].mnval);
}
void remo(ll x,int L,int R,int l=1,int r=n,int p=1){
    if(l>R or L>r) return;
    if(L<=l and r<=R){
        pre(p,x);
        return;
    }
    int mid=(l+r)>>1;
    push_down(p);
    remo(x,L,R,l,mid,2*p);
    remo(x,L,R,mid+1,r,2*p+1);
    tree[p].mxval=max(tree[2*p].mxval,tree[2*p+1].mxval);
    tree[p].mnval=min(tree[2*p].mnval,tree[2*p+1].mnval);
}
ll query(int L,int R,int l=1,int r=n,int p=1){
    if(l>R or L>r) return 0;
    if(L<=l and r<=R) return tree[p].mnval;
    int mid=(l+r)>>1;
    push_down(p);
    return query(L,R,l,mid,2*p)+query(L,R,mid+1,r,2*p+1);
}
int main(){
    cin>>n>>q;
    build();
    for(int i=0;i<q;i++){
        ll t,u,v,x;
        cin>>t>>u>>v>>x;
        u++;v++;
        if(t==1) add(x,u,v);
        else remo(x,u,v);
    }
    for(int i=1;i<=n;i++){
         ll res=query(i,i);
         cout<<res<<endl;
     }
}