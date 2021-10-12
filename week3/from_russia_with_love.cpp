#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX 1001
int t, n, m, k, coins[MAX], sum[MAX], dp[MAX][MAX];


int score(int head, int tail, int player){
    if(dp[head][tail]!=-1) return dp[head][tail];
    if(head==tail) return (dp[head][tail] = 0);
    int score1 = (player!=k?0:coins[head]) + score(head+1, tail, (player+1)%m);
    int score2 = (player!=k?0:coins[tail]) + score(head, tail-1, (player+1)%m);
    return (dp[head][tail] = (player==k ? max(score1, score2):min(score1, score2)));

}

int score2(int head, int tail){
    if(dp[head][tail]!=-1) return dp[head][tail];
    if(head==tail) return (dp[head][tail] = 0);
    int scorea = coins[head] + score2(head+1, tail);
    int scoreb = coins[tail] + score2(head, tail-1);
    int total = sum[tail + 1] - sum[head];
    return (dp[head][tail] = total - max(scorea, scoreb));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> m >> k;
        memset(sum, 0, sizeof(sum));
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < n; i++){
            cin >> coins[i];
            sum[i+1] = sum[i] + coins[i];
        }

        cout << ((m==2)?score2(0, n-1):score(0,n-1,0)) <<endl;
    }

    return 0;
}