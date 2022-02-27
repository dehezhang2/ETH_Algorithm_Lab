#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int t, n, k, w;

int sliding_window(vector<int>& costs, vector<int>& water_way, int query){
    int left = 0, right = 0, max_result = -1, sum = 0;
    while(left < (int)water_way.size() && right < (int)water_way.size()){
        while(sum < query && right < (int)water_way.size()) sum += costs[water_way[right++]];
        while(sum > query && left < (int)water_way.size()) sum -= costs[water_way[left++]];
        int num_of_island = right - left;
        if(sum==query){
            max_result = max(max_result, num_of_island);
            sum -= costs[water_way[left++]];
        }
    }
    return max_result;
}

void solve(){
    cin >> n >> k >> w;
    vector<int> costs(n);
    vector< vector<int> > water_ways(w, vector<int>());
    for(int i = 0; i < n; i++){
        cin >> costs[i];
    }
    for(int i = 0; i < w; i++){
        int l; cin >> l; water_ways[i] = vector<int>(l);
        for(int j = 0; j < l; j++){ 
            cin >> water_ways[i][j];
        }
    }
    int max_result = 0;
    for(auto& waterway:water_ways){
        max_result = max(max_result, sliding_window(costs, waterway, k));
    }
    unordered_map<int, int> max_result_for_cost;
    vector<int> partial_sum;
    partial_sum.reserve(n);
    for(auto& waterway : water_ways){
        partial_sum.resize(1); int sum = 0;
        for(int i = 1; i < (int)waterway.size(); i++){
            sum += costs[waterway[i]];
            if(sum > k) break;// important
            partial_sum.push_back(sum);
        }
        for(int i = 1; i < (int)partial_sum.size(); i++){
            auto other_half = max_result_for_cost.find(k - partial_sum[i] - costs[0]);
            if(other_half != max_result_for_cost.end()){
                max_result = max(max_result, i + other_half->second + 1);
            }
        }
        for(int i = 1; i < (int)partial_sum.size(); i++){
            auto this_half = max_result_for_cost.find(partial_sum[i]);
            if(this_half == max_result_for_cost.end() || this_half->second < i){
                max_result_for_cost[partial_sum[i]] = i;
            }
        }
    }
    cout << max_result << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}