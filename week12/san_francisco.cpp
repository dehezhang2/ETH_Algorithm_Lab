#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int t, n, m, x, k;

long dfs(vector< vector < pair<int, long> > >& graph, vector< vector<long> >& dp, int index, int moves){
    if(dp[index][moves] != -1) return dp[index][moves];
    long max_dist = -1;
    for(int i = 0; i < (int)graph[index].size(); i++){
        if(graph[index][i].second==-1) max_dist = max(max_dist, dfs(graph, dp, 0, moves));
        else max_dist = max(max_dist, graph[index][i].second + dfs(graph, dp, graph[index][i].first, moves-1));
    }
    return (dp[index][moves] = max_dist);
}

void solve(){
    cin >> n >> m >> x >> k;
    vector< vector < pair<int, long> > > graph(n);
    for(int i = 0; i < m; i++){
        int u, v; long p; cin >> u >> v >> p;
        graph[u].push_back(make_pair(v, p));
    }
    for(int i = 0; i < n; i++){
        if(graph[i].size() == 0)
            graph[i].push_back(make_pair(0, -1));
    }

    vector< vector<long> > dp(n, vector<long>(k+1, -1));
    for(int i = 0; i < n; i++) dp[i][0] = 0;
    // int l = 1, r = k;
    // while(l < r){
    //     int mid = (l+r)/2;
    //     if(dfs(graph, dp, 0, mid) >= x){
    //         r = mid;
    //     } else {
    //         l = mid + 1;
    //     }
    // }
    // bool possible = (dfs(graph, dp, 0, l) >= x);
    // if(possible){
    //     cout << l << endl;
    // } else{
    //     cout << "Impossible" << endl;
    // }
    // bool possible = false;
    // for(int i = 1; i <= k; i++) {
    //     if(dfs(graph, dp, 0, i) >= x) {
    //         cout << i << "\n";
    //         possible = true;
    //         i = k;
    //     }
    // }
    // if(!possible) cout << "Impossible\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}