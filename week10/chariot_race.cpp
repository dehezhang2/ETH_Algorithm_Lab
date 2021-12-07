#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int t, n;

int dfs(vector< vector<int> >& graph, vector< vector<int> >& dp, vector<int> & cost, int index, bool parent_repaired){
    if(dp[index][parent_repaired] != -1) return dp[index][parent_repaired];
    int res = -1;
    int cost_of_subtree_with_this_repaired = cost[index];
    for(int child : graph[index]) 
        cost_of_subtree_with_this_repaired += dfs(graph, dp, cost, child, true);
    int cost_of_subtree_without_this_repaired = 0;
    for(int child : graph[index]) 
        cost_of_subtree_without_this_repaired += dfs(graph, dp, cost, child, false);
    // 1. parent repaired => self repaired / self not repaired
    if(parent_repaired)
        res = min(cost_of_subtree_with_this_repaired, cost_of_subtree_without_this_repaired);
    // 1. parent not repaired => self repaired / child repaired
    else{
        // self repaired
        res = cost_of_subtree_with_this_repaired;
        // child repaired (cost = one child(true) + all other child(false))
        for(int child_repaired : graph[index]){
            int cost_of_subtree_with_child_repaired = cost[child_repaired];
            for(int grand_child : graph[child_repaired]) 
                cost_of_subtree_with_child_repaired += dfs(graph, dp, cost, grand_child, true);
            cost_of_subtree_with_child_repaired += (cost_of_subtree_without_this_repaired - dfs(graph, dp, cost, child_repaired, false));
            res = min(res, cost_of_subtree_with_child_repaired);
        }
    }
    return (dp[index][parent_repaired] = res);
}

void solve(){
    cin >> n;
    vector< vector<int> > graph(n);
    vector< vector<int> > dp(n, vector<int>(2, -1));
    vector<int> cost(n);
    for(int i = 0; i < n-1; i++){
        int from, to; cin >> from >> to;
        graph[from].push_back(to);
    }
    for(int i = 0; i < n; i++) cin >> cost[i];
    cout << dfs(graph, dp, cost, 0, false) << "\n";
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}