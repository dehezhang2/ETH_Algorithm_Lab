#include <iostream>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int t, n, src; 
struct Edge{
    int from, to, cost;
    bool operator<(const Edge& other) const{
        return cost < other.cost;
    }
};

int find_mst(vector<Edge>& edge_list, vector<int>& edge_used, bool record_edge, int ignore_edge){
    int cnt = 0, cost = 0;
    boost::disjoint_sets_with_storage<> mst(n);
    for(int i = 0; i < (int)edge_list.size() && cnt < n - 1; i++){
        if( i!=ignore_edge && mst.find_set(edge_list[i].from) != mst.find_set(edge_list[i].to)){
            mst.union_set(edge_list[i].from, edge_list[i].to);
            if(record_edge) edge_used.push_back(i);
            cost += edge_list[i].cost; cnt++;
        }
    }
    return cost;
}

void solve(){
    cin >> n >> src;
    vector<Edge> edge_list;
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            int c; cin >> c;
            edge_list.push_back((Edge){i, j, c});
        }
    }
    sort(edge_list.begin(), edge_list.end());
    vector<int> edge_used;
    find_mst(edge_list, edge_used, true, -1);
    int min_cost = INT_MAX;
    for(auto edge:edge_used){
        min_cost = min(min_cost, find_mst(edge_list, edge_used, false, edge));
    }
    cout << min_cost <<endl;
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