///1
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX_H 1025
int t, n, m, a, b, P, H, W;
int dp[MAX_H][MAX_H];
// type A: increase P by p_i H by h_i decrease W by a
// type B: increase W by w_j decrease P by b

// bool has_solution(int num_of_potion,  vector<pair <int, int> > potions_A, vector<int> potions_B){
    
// }

void solve(){
    cin >> n >> m >> a >> b >> P >> H >> W;
    memset(dp, 0, sizeof(dp));
    vector<pair <long, long> > potions_A;
    vector<long> potions_B;
    for(int i = 0; i < n; i++){
        long p, h; cin >> p >> h;
        potions_A.push_back(make_pair(p, h));
    }
    for(int i = 0; i < m; i++){
        long w; cin >> w;
        potions_B.push_back(w);
    }
    sort(potions_A.rbegin(), potions_A.rend());
    sort(potions_B.rbegin(), potions_B.rend());
    long sum2 = 0;
    int cnt_b = 0;
    for(int p:potions_B){
        if(sum2 >= W) break;
        sum2 += p;
        cnt_b++;
    }
 
    // cout << ((sum1 >= r1 && sum2 >= r2)?cnt:-1 )<< endl;
    // int l = 0, r = n+m;
    // while(l < r){
    //     int mid = (l + r)/2;
    //     if(has_solution(mid, potions_A, potions_B)){
    //         r = mid;
    //     } else {
    //         l = mid + 1;
    //     }
    // }
    // cout << (has_solution(l, potions_A, potions_B)?l:-1) << endl;
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