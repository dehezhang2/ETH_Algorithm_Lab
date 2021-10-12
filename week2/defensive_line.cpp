///5
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define MAX_DEFENDER 100000
#define MAX_ATTACKER 100
int t, n, m, k, v[MAX_DEFENDER];
// groups[x] = 0 if there is no interval sums to k ends at x
// , or the number of elements in the interval(sums to k) ends at x
int groups[MAX_DEFENDER]; 
struct Item{
    int defender_num;
    int attacker_num;
    Item(int x, int y):defender_num(x), attacker_num(y) {}
};

void convert(){
    int head = 0, tail = 0, cnt = 0;
    while(head < n && tail < n){
        while(cnt < k && tail < n) cnt += v[tail++];
        while(cnt > k && head < n) cnt -= v[head++];
        if(cnt == k && head < n){
            groups[tail-1] = tail - head;
            cnt -= v[head++];
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> m >> k;
        for(int i = 0; i < n; i++) cin >> v[i];
        memset(groups, 0, sizeof(groups));
        vector< vector<Item> > dp(m+1, vector<Item>(n+1, Item(0,0)));
        convert();
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                // if take the current interval, then cannot take another interval ends after head
                int head_j = j - groups[j-1];
                int score1 = dp[i-1][head_j].defender_num + groups[j-1];
                int score2 = dp[i][j-1].defender_num;
                dp[i][j] = score1 > score2 ? Item(score1, dp[i-1][head_j].attacker_num + 1) : dp[i][j-1];
            }
        }
        if(dp[m][n].attacker_num == m) cout << dp[m][n].defender_num << endl;
        else cout <<"fail\n";
    }
    return 0;
}