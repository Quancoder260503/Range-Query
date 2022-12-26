#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz =2e5+1;
const int ssz=5e3+1;
const int mod=1e9+7;
int p,n,q,timer,m;
long long k;
long long a[sz];
long long sf[sz];
vector<long long>val;
struct fewwick{
   long long bit[sz];
   long long sum(int i){
	     long long c=0;
	     for(++i; i > 0 ; i -= (i & -i))
		     c= (c+bit[i]);
	     return c;
   }
   long long query(int l,int r){
      return sum(r) - sum(l-1);
   }
   void upd(int i,int dif) {
	   for(++i; i < sz ; i += (i & -i))
		   bit[i] = (dif+bit[i]);
   }
} bit0,bit1;
int main(){
      cin>>n>>k;
      for(int i = 1; i <= n; i++){
          cin>>a[i];
          val.push_back(a[i]);
      }
      sort(val.begin(),val.end());
      val.erase(unique(val.begin(),val.end()),val.end());
      long long tot = 0; 
      for(int i = 1; i <= n; i++){
           int pos = lower_bound(val.begin(),val.end(),a[i]) - val.begin() + 1;
           tot += bit0.query(pos + 1,n);
           bit0.upd(pos,1);
      }
      int j = 1;
      long long ans = 0;
      for(int i = 1; i <= n; i++){
           int posl = lower_bound(val.begin(),val.end(),a[i]) - val.begin() + 1;
           tot += bit0.query(1,posl - 1) + bit1.query(1,n - posl); 
           bit1.upd(n - posl + 1, 1);
           while((j <= i or tot > k) and j <= n){
                int posr = lower_bound(val.begin(),val.end(),a[j]) - val.begin() + 1;
                tot= tot - bit0.query(1,posr - 1) - bit1.query(1,n - posr);
                bit0.upd(posr, -1);
                j++;
           }
           ans+= n - j + 1;
      }
      cout<<ans<<endl;
}
