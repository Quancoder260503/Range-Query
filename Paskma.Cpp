#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e6+1;
const int mod=1e9+7;
int p,n,q,timer;
long long d;
long long a[sz];
long long dp[sz];
int freq[sz];
int cnt[sz];
int cntr[sz];
long long bit[sz];
long long sum(int i){
	     long long c=0;
	     for(++i; i > 0 ; i -= (i & -i))
		     c= (c+bit[i]);
	     return c;
}
void upd(int i,int dif) {
	  for(++i; i < sz ; i += (i & -i))
		   bit[i] = (dif+bit[i]);
}
int main(){
      cin>>n;
      vector<long long>b;
      for(int i = 1; i <= n; i++){
          cin>>a[i];
          b.push_back(a[i]);
      }
      sort(b.begin(),b.end());
      for(int i = 1; i <= n; i++){
           int pos = lower_bound(b.begin(),b.end(),a[i])-b.begin();
           freq[i] = ++cnt[pos];
      }
      long long ans = 0;
      for(int i = n; i  > 0; i--){
           ans += (1ll)*sum(freq[i]-1);
           int pos = lower_bound(b.begin(),b.end(),a[i])-b.begin();
           cntr[pos]++;
           upd(cntr[pos],1);
      }
      cout<<ans<<endl;
}
