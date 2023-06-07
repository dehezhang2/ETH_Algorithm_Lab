#include <iostream>
#include <vector>

using namespace std;
int t, n, m, k;
long x;

long dfs(vector< vector< pair<int, long> > >& graph, vector< vector<long> >& mem, int index, int move){
    if(mem[index][move]!=-1) return mem[index][move];
    if(move==0) return mem[index][move] = 0;
    long max_dist = -1;
    for(auto next_node : graph[index]){
        if(next_node.second == -1) max_dist = max(max_dist, dfs(graph, mem, next_node.first, move));
        else max_dist = max(max_dist, next_node.second + dfs(graph, mem, next_node.first, move-1));
    }
    return mem[index][move] = max_dist;
}

void solve(){
    cin >> n >> m >> x >> k;
    vector< vector< pair<int, long> > > graph(n, vector< pair<int, long> >());
    vector< vector<long> > mem(n, vector<long>(k+1, -1));
    
    for(int i = 0; i < m; i++){
        int u, v; long p; cin >> u >> v >> p;
        graph[u].push_back(make_pair(v, p));
    }
    for(int i = 0; i < n; i++){
        if(graph[i].size()==0) graph[i].push_back(make_pair(0, -1));
    }
    
    bool feasible = false;
    long moves = -1;
    for(int i = 0; i <=k ; i++){
        if( dfs(graph, mem, 0, i) >= x){
            feasible = true;
            moves = i;
            break;
        }
    }
    if(feasible){
        cout << moves << endl;
    } else {
        cout << "Impossible\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}