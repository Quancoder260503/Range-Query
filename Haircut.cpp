#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T> using Tree = tree<T, null_type, less<T>,
	rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
const int sz=2e5+1;
int n,x,y;
ll t;
ll a[sz];
ll pre=0;
ll ans1,ans;
ll num[sz];
bool pick[sz];
vector<ll>to[sz];
int main(){
     cin>>n;
     Tree<ll>tr;
     for(int i=0;i<n;i++){
         cin>>a[i];
         to[a[i]].push_back(i);
     } 
      for(int i=n;i>=0;i--){
         for(auto t:to[i]) num[i+1]+=tr.order_of_key(t);
         for(auto t:to[i]) tr.insert(t);
     } 
     for(int i=1;i<=n;i++){
          num[i]+=num[i-1];
     } for(int i=0;i<n;i++){
         cout<<num[i]<<endl;
     }
}