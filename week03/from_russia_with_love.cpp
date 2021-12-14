#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX_C 1001
#define MAX_P 501
int t, n, m, k, coins[MAX_C], dp[MAX_C][MAX_C];

int score(int head, int tail, int player){
    if(dp[head][tail]!=-1) return dp[head][tail];
    if(head==tail) return (dp[head][tail] = (player!=k?0:coins[head]));
    int score1 = (player!=k?0:coins[head]) + score(head+1, tail, (player+1)%m);
    int score2 = (player!=k?0:coins[tail]) + score(head, tail-1, (player+1)%m);
    return (dp[head][tail] = (player==k ? max(score1, score2):min(score1, score2)));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> m >> k;
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < n; i++) cin >> coins[i];
        cout << score(0,n-1,0) <<endl;
    }
    return 0;
}