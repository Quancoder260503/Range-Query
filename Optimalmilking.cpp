#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=4e4+1;
int n,x,k,i,j,w,q,y;
ll res;
vector<ll>oddday;
vector<ll>evenday;
ll a[sz];
struct node{
    ll val;
    ll odd;
    ll even;
    ll null;
} tree[sz<<2];
void push(int p){
    tree[p].val=max(tree[2*p].val+tree[2*p+1].odd,tree[2*p].even+tree[2*p+1].val);
    tree[p].odd=max(tree[2*p].null+tree[2*p+1].val,tree[2*p].odd+tree[2*p+1].odd);
    tree[p].even=max(tree[2*p].val+tree[2*p+1].null,tree[2*p].even+tree[2*p+1].even);
    tree[p].null=max(tree[2*p].null+tree[2*p+1].even,tree[2*p].odd+tree[2*p+1].null);
}
void build(int l=1,int r=n,int p=1){
    if(l==r){
        tree[p].val=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,2*p);
    build(mid+1,r,2*p+1);
    push(p);
}
void update(int L,int R,int l=1,int r=n,int p=1){
    if(l>R or L>r) return;
    if(L<=l and r<=R){
        tree[p].val=a[l];
        return;
    }
    int mid=(l+r)>>1;
    update(L,R,l,mid,2*p);
    update(L,R,mid+1,r,2*p+1);
    push(p);
}
int main(){
     cin>>n>>q;
     for(int i=1;i<=n;i++) cin>>a[i];
     build();
     for(int i=0;i<q;i++){
        ll u,v;cin>>u>>v;
        a[u]=v;
        update(u,u);
        res+=tree[1].val;
     } 
     cout<<res<<endl;
}