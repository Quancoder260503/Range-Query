#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=4e5+1;
const int inf=1e7+5;
int n;
vector<ll>ord;
array<ll,3>dp[sz];
array<ll,2>a[sz];
ll ans[sz];
ll bit[sz];
map<int,int>mp;
ll sum(int i){
	     ll c=0;
	     for(++i; i > 0 ; i -= (i & -i))
		     c= (c+bit[i]);
	     return c;
}
ll query(int l,int r){
    return sum(r)-sum(l-1);
}
void upd(int i,int dif) {
	for(++i; i < sz ; i += (i & -i))
		bit[i] = (dif+bit[i]);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i][0]>>a[i][1];
        ord.push_back(a[i][0]);
        ord.push_back(a[i][1]);
    }
    sort(ord.begin(),ord.end());
    for(int i=0;i<ord.size();i++) mp[ord[i]]=i+1;
    for(int i=1;i<=n;i++){
        //cout<<mp[a[i][0]]<<' '<<mp[a[i][1]]<<endl;
        dp[i][0]=mp[a[i][0]];
        dp[i][1]=mp[a[i][1]];
        dp[i][2]=i;
    }
    for(int i=1;i<=n;i++) upd(dp[i][1],1);
    sort(dp+1,dp+n+1);
    for(int i=1;i<=n;i++){
        upd(dp[i][1],-1);
        ans[dp[i][2]]=query(dp[i][0],dp[i][1]);
    }
    for(int i=1;i<=n;i++){
        cout<<ans[i]<<endl;
    }
}
