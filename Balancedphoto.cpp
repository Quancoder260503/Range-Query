#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
const int sz=1001;
const int sz1=1e5+1;
int n,k,w,m,q;
ll ans;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
vector<array<ll,3>>query;
ll lf[sz1];
ll ri[sz1];
ll a[sz1];
ll dp[sz1];
int main(){
   cin>>n;
    Tree<ll>tr;
    Tree<ll>tr1;
   for(int i=0;i<n;i++){
       cin>>a[i];
   } for(int i=0;i<n;i++){
       lf[i]=i-tr.order_of_key(a[i]);
       tr.insert(a[i]);
   } 
     for(int i=n-1;i>=0;i--){
       ri[i]=n-i-1-tr1.order_of_key(a[i]);
       tr1.insert(a[i]);
   } 
    for(int i=0;i<n;i++){
      ll p1=max(lf[i],ri[i]);
      ll p2=2*min(lf[i],ri[i]);
      if (p1>p2) ans++; 
   } cout<<ans;
}
