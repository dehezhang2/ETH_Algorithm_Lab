#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX 2501
int t, n, coins[MAX], sum[MAX];
int mem[MAX][MAX];

int score(int head, int tail, int player){
    if(mem[head][tail]!=-1) return mem[head][tail];
    if(head==tail) return (mem[head][tail] = 0);
    int score1 = (player?coins[head]:0) + score(head+1, tail, !player);
    int score2 = (player?coins[tail]:0) + score(head, tail-1, !player);
    int total = sum[tail + 1] - sum[head];
    return (mem[head][tail] = player?max(score1, score2):min(score1, score2));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n;
        memset(sum, 0, sizeof(sum));
        memset(mem, -1, sizeof(mem));
        for(int i = 0; i < n; i++){
            cin >> coins[i];
            sum[i + 1] = sum[i] + coins[i];
        } 
        cout << score(0, n-1, 1) << endl;
    }

    return 0;
}