#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
int t, n;

// equivalent to move two marios at the same time
// each time go along x direction or y direction
// => four states (2 direction * 2 mario)

int dp(int total_steps, int x_to, int x_back, vector< vector<int> >& shelf, vector< vector< vector<int> > >& mem, int n){
    if(x_to > n - 1 || x_back > n - 1 || total_steps > 2*n - 2 || total_steps - x_to > n-1 || total_steps - x_back > n-1)
        return 0;
    if(mem[total_steps][x_to][x_back] != -1)
        return mem[total_steps][x_to][x_back];
    int current_score = shelf[total_steps - x_to][x_to] + shelf[total_steps - x_back][x_back];
    if(x_to==x_back) current_score = shelf[total_steps - x_to][x_to];
    int recurse_score = max( 
        max(
            dp(total_steps+1, x_to, x_back, shelf, mem, n),         // both go y
            dp(total_steps+1, x_to + 1, x_back, shelf, mem, n)      // to go x, back go y
        ), 
        max(
            dp(total_steps+1, x_to, x_back + 1, shelf, mem, n),     // to go y, back go x
            dp(total_steps+1, x_to + 1, x_back + 1, shelf, mem, n)  // both go x
        )
    );
    mem[total_steps][x_to][x_back] = current_score + recurse_score;
    return mem[total_steps][x_to][x_back];
}

void solve(){
    cin >> n;
    vector< vector<int> > shelf(n, vector<int>(n));
    vector<vector<vector<int>>> mem = vector<vector<vector<int>>>(n*2 - 1, vector<vector<int>>(n, vector<int>(n, -1)));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) 
            cin >> shelf[i][j];
    }
    cout << dp(0, 0, 0, shelf, mem, n) << endl;
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