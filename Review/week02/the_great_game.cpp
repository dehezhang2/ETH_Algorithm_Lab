#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
int t, n, m, r, b;

int dp(int index, bool is_player, vector< vector<int> >& map, vector<int>& max_dist, vector<int>& min_dist){
    if(is_player){
        if(min_dist[index] != -1) return min_dist[index];
        else min_dist[index] = INT_MAX;
    } else {
        if(max_dist[index] != -1) return max_dist[index];
    }
    if(index == n - 1) return min_dist[index] = max_dist[index] = 0; 
    for(int child : map[index]){
        int next_dist = dp(child, !is_player, map, max_dist, min_dist) + 1;
        if(is_player)min_dist[index] = min(min_dist[index], next_dist);
        else max_dist[index] = max(max_dist[index], next_dist);
    }
    return is_player ? min_dist[index] : max_dist[index];
}

void solve(){
    cin >> n >> m >> r >> b; r--; b--;
    vector< vector<int> > map(n);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        map[u-1].push_back(v-1);
    }
    vector<int> max_dist(n, -1), min_dist(n, -1);
    int x = dp(r, true, map, max_dist, min_dist);
    int y = dp(b, true, map, max_dist, min_dist);
    cout << (y < x || (y==x && y%2==0)) << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}