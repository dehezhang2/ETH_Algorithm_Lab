#include <iostream>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
struct Edge{
    int from, to, weight;
    bool operator<(const Edge& e) const{
        return weight < e.weight;
    }
};
int t, n, x;

int find_mst(vector<Edge>& graph, vector<int>& edge_used, int edge_ignored, bool record){
    boost::disjoint_sets_with_storage<> uf(n);
    int n_components = n, index = 0, cost = 0;
    for(auto edge : graph){
        if(index++ == edge_ignored) continue;
        int c1 = uf.find_set(edge.from);
        int c2 = uf.find_set(edge.to);
        if (c1 != c2) {
            uf.link(c1, c2);
            if(record) edge_used.push_back(index - 1);
            cost += edge.weight;
            if (--n_components == 1) break;
        }
    }
    return cost;
}

void solve(){
    cin >> n >> x;
    vector<Edge> graph;
    vector<int> edge_used;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            int weight; cin >> weight;
            graph.push_back((Edge){i, j, weight});
        }
    }
    sort(graph.begin(), graph.end());
    find_mst(graph, edge_used, -1, true);
    int res = INT_MAX;
    for(int edge : edge_used){
        int cost = find_mst(graph, edge_used, edge, false);
        res = min(cost, res);
    }
    cout << res << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}