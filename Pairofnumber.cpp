#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=3e5+5;
const int lg=21;
int n,ans,curval;
int a[sz];
set<int>opt[sz];
int st[sz][lg];
int gcd_query(int l,int r){
    int d=r-l+1;
    int ans=curval;
    for(int i=0;i<lg;i++){
        if(d&(1<<i)){
           ans=__gcd(ans,st[l][i]);
           l+=(1<<i);
        }
    }
    return ans;
}
int main(){
     cin>>n;
     for(int i=1;i<=n;i++) cin>>st[i][0];
     for(int j=1;j<lg;j++){
         for(int i=1;i+(1<<j)<=n+1;i++){
              st[i][j]=__gcd(st[i][j-1],st[i+(1<<(j-1))][j-1]);
         }
     } 
     for(int i=1;i<=n;i++){ 
          int l=i; int r=n;
          int lb,rb; lb=rb=i;
          curval=st[i][0];
          while(l<=r){
             int mid=(l+r)>>1;
             if(gcd_query(i,mid)==st[i][0]){
                 l=mid+1;
                 rb=mid;               
             }
             else r=mid-1;
          }
          l=1; r=i;
          while(l<=r){
              int mid=(l+r)>>1;
              if(gcd_query(mid,i)==st[i][0]){
                   r=mid-1;
                   lb=mid;
              }
              else l=mid+1;
          }
          //cout<<lb<<' '<<rb<<endl; 
          ans=max(ans,rb-lb);
          opt[rb-lb].insert(lb);
     }
     cout<<opt[ans].size()<<' '<<ans<<endl;
     for(auto x:opt[ans]) cout<<x<<' ';  
}
