#include <iostream>
#include <vector>

using namespace std;
int t, n;

int dp( vector< vector<int> >& shelf, vector< vector< vector<int> > >& mem, int x_to, int x_back, int total){
    if(x_to > n-1 || x_back > n-1 || total - x_to > n-1 || total - x_back > n-1||total > 2*n - 2) return 0;
    if(mem[total][x_to][x_back] != -1) return mem[total][x_to][x_back];
    
    int current_score = shelf[x_to][total - x_to] + shelf[x_back][total - x_back];
    if(x_to == x_back) current_score = shelf[x_to][total - x_to];
    int recurse_score = max(
        max(
            dp(shelf, mem, x_to, x_back, total+1),
            dp(shelf, mem, x_to + 1, x_back, total+1)
        ),
        max(
            dp(shelf, mem, x_to, x_back + 1, total+1),
            dp(shelf, mem, x_to + 1, x_back + 1, total+1)
        )
    );
    return (mem[total][x_to][x_back] = current_score + recurse_score);
}

void solve(){
    cin >> n;
    vector< vector<int> > shelf(n, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) 
            cin >> shelf[i][j];
    vector< vector< vector<int> > > mem(2*n - 1, vector< vector<int> >(n, vector<int>(n, -1)));
    cout << dp(shelf, mem, 0, 0, 0) << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}