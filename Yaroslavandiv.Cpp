#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=1e9+7;
int p,n,q,timer,m;
long long d;
long long a[sz];
long long ans[sz];
int pos[sz];
vector<int>dp[sz];
long long bit[sz*10];
vector<pair<pair<int,int>,int>>ql;
vector<pair<pair<int,int>,int>>qr;
long long sum(int i){
	   long long c=0;
	   for(++i; i > 0 ; i -= (i & -i))
		    c+=bit[i];
	   return c;
}
long long query(int l,int r){
     return sum(r)-sum(l-1);
}
void upd(int i,int dif)
{
	for(++i; i < sz*10 ; i += (i & -i))
		bit[i] +=dif;
}
bool cmp(pair<pair<int,int>,int>&a,pair<pair<int,int>,int>&b){
      return a.first.second < b.first.second;
}
int main(){
      cin>>n>>q;
      for(int i = 1; i <= n; i++){
           scanf("%d",a+i);
           pos[a[i]] = i;
      }
      for(int i = 1; i <= q; i++){
           int u,v; scanf("%d%d",&u,&v);
           ql.push_back({{u,v},i});
           qr.push_back({{u,v},i});
      }
      sort(ql.begin(),ql.end());
      sort(qr.begin(),qr.end(),cmp);
      int lf = 0;
      int ri = 0;
      for(int i = 1; i <= n; i++){
           while(lf < ql.size() and ql[lf].first.first == i){
                ans[ql[lf].second] -= query(ql[lf].first.first,ql[lf].first.second);
                lf++;
           }
           for(int j = a[i]; j <= n; j+=a[i]) upd(pos[j],1);
           while (ri < qr.size() and qr[ri].first.second == i){
                ans[qr[ri].second] += query(qr[ri].first.first,qr[ri].first.second);
                ri++;
           }
           
      }
      for(int i = 1; i <= q; i++) cout<<ans[i]<<endl;
}
