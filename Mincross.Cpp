#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=1e9+7;
int p,n,mx_d,q,timer;
int bit[sz];
ll dp[sz];
long long sum(int i){
	  long long c=0;
	  for(++i; i > 0 ; i -= (i & -i))
		    c= (c+bit[i]);
	  return c;
}
void upd(int i,int dif){
	for(++i; i < sz ; i += (i & -i))
		bit[i] = (dif+bit[i]);
}
long long solve(vector<int>&a,vector<int>&b){
      vector<int>posl; vector<int>posr;
      posl.resize(n+1);
      posr.resize(n+1);
      for(int i = 1; i < a.size(); i++) posl[a[i]] = i;
      long long ans = 0;
      memset(bit,0,sizeof(bit));
      for(int i = 1; i < a.size(); i++){
           ans += sum(n)-sum(posl[b[i]]);
           upd(posl[b[i]],1);
      }
      for(int i = 1 ; i < b.size(); i++) posr[b[i]] = i;
      long long res = ans;
      for(int i = b.size()-1; i > 0; i--){
           ans += (long long)((1ll)*(2 * posr[a[i]]) - n - 1);
           res = min(ans,res);
      }
      return res;
}
int main(){
       cin>>n;
       vector<int>a{0};
       vector<int>b{0};
       for(int i=1;i<=n;i++){
           int x ; cin>>x;
           a.push_back(x);
       }
       for(int i=1;i<=n;i++){
           int y ; cin>>y;
           b.push_back(y);
       }
       cout<<(1ll)*min(solve(a,b),solve(b,a))<<endl;
}
