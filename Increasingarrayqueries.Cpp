#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+10;
const int inf=1e6+1;
int n,k,m,q,add,dis;
ll timer=1;
long long  a[sz];
long long  pf[sz];
long long  d[sz];
long long bit[sz];
vector<pair<int,int>>que[sz];
long long ans[sz];
long long sum(int i){
	   long long c=0;
	   for(++i; i > 0 ; i -= (i & -i))
	     	c= (c+bit[i]);
	   return c;
}
long long query(int l, int r){
     return sum(r) - sum(l-1);
}
void upd(int i,long long dif)
{
	for(++i; i < sz ; i += (i & -i))
		bit[i] = (dif+bit[i]);
}
int main(){
     cin>>n>>q;
     for(int i = 1; i <= n; i++) cin>>a[i];
     for(int i = 1; i <= n; i++) pf[i] = pf[i - 1] + a[i];
     for(int i = 1; i <= q; i++){
          int u,v; cin>>u>>v;
          que[u].push_back({v,i});
     }
     deque<int>stk;
     a[n + 1] = LLONG_MAX;
     stk.push_front(n + 1);
     for(int i = n ; i > 0; i--){
           while(!stk.empty() and a[stk.front()] <= a[i]){
                upd(stk.front(),-d[stk.front()]);
                stk.pop_front();
           }
           int j = stk.front();
           d[i] = (1ll)*(j - i - 1)*a[i] - pf[j - 1] + pf[i];
           upd(i,d[i]);
           stk.push_front(i);
           for(int j = 0; j < que[i].size(); j++){
                 int pos = upper_bound(stk.begin(),stk.end(),que[i][j].first) - stk.begin() - 1;
                 int idx = que[i][j].second;
                 int rb = que[i][j].first;
                 ans[idx] += (rb - stk[pos]) * a[stk[pos]] + pf[stk[pos]] - pf[rb];
                 if(pos) ans[idx] += query(i,stk[pos - 1]);
           }
     }
     for(int i = 1; i <= q; i++) cout<<ans[i]<<endl;
}