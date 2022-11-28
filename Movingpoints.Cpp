#include <bits/stdc++.h>
#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long int64;
const int sz = 4e5 + 1;
int n,q,p;
long long a[sz];
int64 v[sz];
int64 x[sz];
int64 bit[sz];
int bitcnt[sz];
vector<pair<int64,int64>>points;
long long queryv(int i){
	  long long c=0;
	  for(++i; i > 0 ; i -= (i & -i))
		    c= (c+bit[i]);
	  return c;
}
void updv(int i,long long dif)
{
	for(++i; i < sz ; i += (i & -i))
		bit[i] = (dif+bit[i]);
}
long long query(int i){
	  long long c=0;
	  for(++i; i > 0 ; i -= (i & -i))
		    c= (c+bitcnt[i]);
	  return c;
}
void upd(int i,long long dif)
{
	for(++i; i < sz ; i += (i & -i))
		bitcnt[i] = (dif+bitcnt[i]);
}
int main(){
      cin>>n;
      for(int i=1;i<=n;i++) cin>>x[i];
      vector<int64>velo;
      for(int i=1;i<=n;i++){
          cin>>v[i];
          velo.push_back(v[i]);
      }
      for(int i=1;i<=n;i++) points.push_back({x[i],v[i]});  
      sort(points.begin(),points.end());
      sort(velo.begin(),velo.end());
      map<int64,int>mp;
      velo.erase(unique(velo.begin(),velo.end()),velo.end());
      for(int i = 0; i < velo.size();i++) mp[velo[i]]=i+1;
      long long ans = 0;
      for(int i = 0; i < points.size(); i++){
            long long acc = queryv(mp[points[i].second]);
            long long cnt = query(mp[points[i].second]);
            ans += (1ll)*cnt*points[i].first - acc;
            updv(mp[points[i].second],points[i].first);
            upd(mp[points[i].second],1);
      }
      cout<<ans<<endl;
}
