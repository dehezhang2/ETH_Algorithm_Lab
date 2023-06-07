#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int t, n, m;
long a, b, P, H, W;
// i: consider first i-th bottles
// j: j bottles quota left
// k: to achieve k happiness
// -1: not feasible
// -2: not computed
long dp(int i, int j, int k, vector< vector< vector<long> > >& mem, vector< pair<long, long> >& potions_a){
    if(j==0) return ( k==0 ? 0 : -1);   // run out of quota should have zero left
    if(i <0) return -1;                 // if no bottles considered, still have quota left => not feasible
    if(mem[i][j][k] != -2) return mem[i][j][k];
    long use_i = dp(i-1, j-1, max((long)0, k-potions_a[i].second), mem, potions_a);
    long not_use_i = dp(i-1, j, k, mem, potions_a);
    if(use_i != -1) use_i += potions_a[i].first;
    return mem[i][j][k] = max(use_i, not_use_i);
}

void solve(){
    cin >> n >> m >> a >> b >> P >> H >> W;
    vector< pair<long, long> > potions_a(n);
    vector<long> potions_b(m);
    for(int i = 0; i < n; i++) cin >> potions_a[i].first >> potions_a[i].second;
    for(int i = 0; i < m; i++) cin >> potions_b[i];
    sort(potions_b.rbegin(), potions_b.rend());
    vector< vector< vector<long> > > mem(n, vector< vector<long> >(n+1, vector<long>(H+1, -2)));

    int res = INT_MAX;
    for(int i = 0; i <= n; i++){
        int num_a = i;
        long current_power = dp(n-1, i, H, mem, potions_a);
        long current_witness = -a*num_a;
        for(int j = 0; j < m; j++){
            int num_b = j + 1;
            current_witness += potions_b[j];
            current_power -= b;
            if(current_power < P) break;
            if(current_witness >= W) res = min(res, num_a + num_b);
        }
    }
    cout << (res==INT_MAX ? -1 : res) << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}