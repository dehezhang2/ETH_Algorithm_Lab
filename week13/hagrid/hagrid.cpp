#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int t, n;

struct Chamber{
    int number_of_node = 1;
    int time_cost = 0;
    int number_of_galleons = 0;
    vector< pair<int, long> > child_list;
};

void preprocess(vector<Chamber>& chamber_list, int chamber_id){
    for(auto child : chamber_list[chamber_id].child_list){
        preprocess(chamber_list, child.first);
        chamber_list[chamber_id].number_of_node += chamber_list[child.first].number_of_node;
        chamber_list[chamber_id].time_cost += child.second + chamber_list[child.first].time_cost;
    }
    sort(chamber_list[chamber_id].child_list.begin(), chamber_list[chamber_id].child_list.end(),
        [&chamber_list, chamber_id](auto& left, auto& right)-> bool {
            long time_cost1 = chamber_list[left.first].time_cost + left.second;
            long number_of_node1 = chamber_list[left.first].number_of_node;
            long time_cost2 = chamber_list[right.first].time_cost + right.second;
            long number_of_node2 = chamber_list[right.first].number_of_node;
            return time_cost1 * number_of_node2 < time_cost2 * number_of_node1;
        }
    );
}

long dfs(vector<Chamber>& chamber_list, int chamber_id, long current_time){
    long current_gallons = chamber_list[chamber_id].number_of_galleons - current_time;
    for(auto child : chamber_list[chamber_id].child_list){
        current_gallons += dfs(chamber_list, child.first, current_time + child.second);
        current_time += 2 * (child.second + chamber_list[child.first].time_cost);
    }
    return current_gallons;
}

void solve(){
    cin >> n;
    vector<Chamber> chamber_list(n + 1);
    for(int i = 1; i < n + 1; i++){
        cin >> chamber_list[i].number_of_galleons;
    }
    for(int i = 0; i < n; i++){
        int u, v, l; cin >> u >> v >> l;
        chamber_list[u].child_list.push_back(make_pair(v, l));
    }
    preprocess(chamber_list, 0);
    cout << dfs(chamber_list, 0, 0) << endl;
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