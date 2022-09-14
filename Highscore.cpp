#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef long long ll;
const int sz=5001;
const int sz1=1e6+1;
ll a[sz];
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
ll dis[sz];
vector<array<int,3>>edge;
int n,q,m;
ll ans=-1e18;
int main(){
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v,d;
        cin>>u>>v>>d;
        edge.push_back({u,v,-d});
    }
    const ll inf =1e18;
    for (int i=2;i<=n;i++){
        dis[i]=inf;
    }
    for (int i=1;i<=n;i++){
       for (auto e:edge){
            if (dis[e[0]]+e[2]<dis[e[1]]){
                dis[e[1]]=dis[e[0]]+e[2];
                if(e[1]==n) ans=max(ans,-dis[e[1]]);
            }
        }   
    } if(ans==-1e18) cout <<-1;
      else cout <<ans;
}