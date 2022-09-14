#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,q;
ll c[sz];
ll bit[sz];
const int m=1e9+7;
using namespace __gnu_pbds;
template<class T> using Tree = tree<T, null_type, less<T>, 
	rb_tree_tag, tree_order_statistics_node_update>; 
int main() {
    cin>>n>>q;
    Tree<pair<int,int>>st;
    for(int i=1;i<=n;i++){
         cin>>c[i];
         st.insert({c[i],i});
    } for (int i=0;i<q;i++){
        char d;int a;int b;
        cin>>d>>a>>b;
        if (d=='?') cout <<-st.order_of_key({a-1,m})+st.order_of_key({b,m})<<endl;
        else {
            st.erase({c[a],a});c[a]=b;st.insert({c[a],a});
        }
    }
}    