#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int mod=1e9+7;
int n,q;
int trs[sz];
vector<int>adj[sz];
vector<int>ord;
bool vis[sz];
ll ans[sz];
int cnt[sz];
int a[sz]; 
ll bit[sz];
ll sum(int i)
{
	int c=0;
	for(++i; i > 0 ; i -= (i & -i))
		c+=bit[i];
	return c;
}
ll query(int l,int r){
    return sum(r)-sum(l-1);
}
void upd(int i,int dif)
{
	for(++i; i < sz ; i += (i & -i))
		bit[i] +=dif;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int pos=n;
    upd(a[pos],1);
    pos--;
    while(pos>=0 and a[pos]<a[pos+1]){
        upd(a[pos],1);
        pos--;
    }
    for(int i=1;i<=pos;i++){
        ans[i]=n-query(a[i],n)-1;
        upd(a[i],1);
    }
    cout<<pos<<endl;
    for(int i=1;i<=pos;i++) cout<<ans[i]<<' ';
}
