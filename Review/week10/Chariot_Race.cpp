#include <iostream>
#include <vector>
using namespace std;

int t, n;

int dp(vector< vector<int> >& tree, vector<int>& costs, vector< vector<int> >& mem, int index, bool parent_repaired){
    if(mem[index][parent_repaired] != -1) return mem[index][parent_repaired];
    int res = -1;
    int cost_of_subtree_with_this_repaired = costs[index], cost_of_subtree_without_this_repaired = 0;
    for(int child : tree[index]){
        cost_of_subtree_with_this_repaired += dp(tree, costs, mem, child, true);
        cost_of_subtree_without_this_repaired += dp(tree, costs, mem, child, false);
    }
    if(parent_repaired) res = min(cost_of_subtree_with_this_repaired, cost_of_subtree_without_this_repaired);
    else {
        res = cost_of_subtree_with_this_repaired;
        for(int child : tree[index]){
            int cost_of_subtree_with_child_repaired = costs[child];
            for(int grandchild : tree[child]){
                cost_of_subtree_with_child_repaired += dp(tree, costs, mem, grandchild, true);
            }
            cost_of_subtree_with_child_repaired += (cost_of_subtree_without_this_repaired - dp(tree, costs, mem, child, false));
            res = min(res, cost_of_subtree_with_child_repaired);
        }
    }
    return mem[index][parent_repaired] = res;
}
void solve(){
    cin >> n;
    vector< vector<int> > tree(n, vector<int>());
    vector<int> costs(n);
    vector< vector<int> > mem(n, vector<int>(2, -1));
    for(int i = 0; i < n - 1; i++){
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
    }
    for(int i = 0; i < n; i++){
        cin >> costs[i];
    }
    cout << dp(tree, costs, mem, 0, false) << endl; 
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}