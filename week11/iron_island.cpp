#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int t, n, k, w;

int sliding_window(vector<int>& costs, vector<int>& waterway, int query){
    int max_result = -1, sum = 0, left = 0, right = 0;
    while(true){
        int island_num = right - left;
        if(sum == query){
            max_result = max(max_result, island_num);
            sum -= costs[waterway[left++]];
        } else if (sum < query){
            if(right == (int)waterway.size()) break;
            sum += costs[waterway[right++]];
        } else{
            sum -= costs[waterway[left++]];
        }
    }
    return max_result;
}

void solve(){
    cin >> n >> k >> w;
    vector<int> costs(n);
    vector< vector<int> > waterways(w);
    for(int i = 0; i < n; i++) cin >> costs[i];
    for(int i = 0; i < w; i++){
        int l; cin >> l; waterways[i] = vector<int>(l);
        for(int j = 0; j < l; j++) cin >> waterways[i][j];
    }
    int max_result = 0;
    for(auto& waterway:waterways)
        max_result = max(max_result, sliding_window(costs, waterway, k));
    
    unordered_map<int, int> max_result_for_num_of_men;
    std::vector<int> cost_of_num_island;
    cost_of_num_island.reserve(n);
    for(auto& waterway:waterways){
        cost_of_num_island.resize(1);
        for(int i = 1, sum = 0; i < (int)waterway.size(); i++){
            sum += costs[waterway[i]];
            if(sum > k) break;
            cost_of_num_island.push_back(sum);
        }
        for(int i = 1; i < (int)cost_of_num_island.size(); i++){
            auto iter = max_result_for_num_of_men.find(k - cost_of_num_island[i] - costs[0]);
            if(iter != max_result_for_num_of_men.end()){
                max_result = max(max_result, iter->second + i + 1);
            }
        }
        for(int i = 1; i < (int)cost_of_num_island.size(); i++){
            auto iter = max_result_for_num_of_men.find(cost_of_num_island[i]);
            if(iter == std::end(max_result_for_num_of_men) || iter->second < i){
                max_result_for_num_of_men[cost_of_num_island[i]] = i;
            }
        }
        
    }
    cout << max_result << endl;

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