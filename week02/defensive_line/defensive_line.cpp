#include <iostream>
#include <vector>
using namespace std;
int t, n, m, k;

void sliding_window(vector<int>& defenders,  vector<int>& interval_end_at){
    int left = 0, right = 0, sum = 0;
    while(left < n && right < n){
        while(sum < k && right < n) sum += defenders[right++];
        while(sum > k && left < n) sum -= defenders[left++];
        if(sum==k && left < n){
            interval_end_at[right - 1] = right - left;
            sum -= defenders[left++];
        }
    }
}

void solve(){
    cin >> n >> m >> k;
    vector<int> defenders; defenders.reserve(n);
    for(int i = 0; i < n; i++){
        cin >> defenders[i];
    }
    vector<int> interval_end_at(n);
    sliding_window(defenders, interval_end_at);
    // mem[i][j] represents the state that there are i attackers left to attack j defenders
    // first value represents the attacker used, second value represents the maximum defenders
    vector< vector< pair<int, int> > > mem(m + 1, vector< pair<int, int> >(n + 1, make_pair(0, 0)));
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            int head_j = j - interval_end_at[j-1];
            int use_j = mem[i-1][head_j].second + interval_end_at[j-1];
            int not_use_j = mem[i][j-1].second;
            mem[i][j] = use_j > not_use_j ? make_pair(mem[i-1][head_j].first + 1, use_j) : mem[i][j-1];
        }
    }
    if(mem[m][n].first==m){
        cout << mem[m][n].second << endl;
    } else {
        cout << "fail\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}