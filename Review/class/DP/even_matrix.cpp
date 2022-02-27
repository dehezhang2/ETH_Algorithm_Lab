#include <iostream>
#include <vector>

using namespace std;
int t, n;

void solve(){
    cin >> n;
    vector< vector<int> > mat(n + 1, vector<int>(n + 1, 0));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> mat[i][j]; 
            mat[i][j] += (mat[i-1][j-1]-mat[i][j-1]-mat[i-1][j]);
        }
    }    
    int res = 0;
    for(int i1 = 1; i1 <= n; i1++){
        for(int i2 = i1; i2 <= n; i2++){
            int cnt = 0, sum = 0;
            for(int j = 1; j <= n; j++){
                sum += (mat[i2][j] - mat[i1 - 1][j] - mat[i2][j-1] + mat[i1 - 1][j-1]);
                if(sum % 2==0) cnt++;
            }
            res += (cnt + cnt*(cnt-1)/2 + (n - cnt)*(n-cnt-1)/2);
        }
    }
    cout << res << endl;
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