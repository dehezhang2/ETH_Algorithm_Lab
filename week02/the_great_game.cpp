#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX 100000
#define INF 1000000

int t, n, m, r, b, u, v, min_dist[MAX], max_dist[MAX];
struct Node{ vector<int> next; };
Node map[MAX];

int dfs(int s, bool is_player){
    if(is_player){
        if(min_dist[s] != -1) return min_dist[s];
        else min_dist[s] = INF;
    } 
    if(!is_player && max_dist[s] != -1) return max_dist[s];
    if(s==n) return min_dist[s] = max_dist[s] = 0;
    for(int i=0; i<map[s].next.size(); i++){
        int tar = (map[s].next)[i];
        int res = dfs(tar, !is_player) + 1;
        if(is_player) min_dist[s] = min(min_dist[s], res);
        else max_dist[s] = max(max_dist[s], res);
    }
    return is_player ? min_dist[s] : max_dist[s];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> m >> r >> b;
        memset(map,0,sizeof(map));
        memset(min_dist, -1, sizeof(min_dist));
        memset(max_dist, -1, sizeof(max_dist));
        for(int i = 0; i < m; i++){
            cin >> u >> v;
            map[u].next.push_back(v);
        }
        int x = dfs(r, 1), y = dfs(b, 1);
        cout << (x > y || (x == y && x%2==0) ) << endl;
    }
    return 0;
}