#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX 201
int t, n, cnt, res;
bool temp[MAX], sum[MAX][MAX];

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n;
        memset(sum, 0, sizeof(sum));
        res = 0;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cin >> sum[i][j];
                sum[i][j] ^= (sum[i][j-1] ^ sum[i-1][j] ^ sum[i-1][j-1] );
            }
        }

        for(int i1 = 1; i1 <= n; i1++){
            for(int i2 = i1; i2 <= n; i2++){
                // for(int j1 = 1; j1 <= n; j1++){
                //     for(int j2 = j1; j2 <= n; j2++){
                //         if(sum[i2][j2]^sum[i1-1][j2]^sum[i2][j1-1]^sum[i1-1][j1-1] == 0){
                //             res++;
                //         }
                //     }
                // }
                memset(temp, 0, sizeof(temp));
                cnt = 0;
                for(int j = 1; j<=n; j++){
                    temp[j] = sum[i2][j]^sum[i1-1][j]^sum[i2][j-1]^sum[i1-1][j-1];
                    temp[j] ^= temp[j-1];
                    if(!temp[j]) cnt++;
                }
                res += (cnt-1)*cnt/2 + (n-cnt)*(n-cnt-1)/2 + cnt;
            }
        }
        cout << res << endl;
    }
    return 0;
}