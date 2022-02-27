#include <iostream>
#include <vector>
using namespace std;
int t, n, k;

void solve(){
    cin >> n >> k;
    vector<int> cards(n);
    for(int i = 0; i < n; i++){
        cin >> cards[i];
    }
    int left = 0, right = 1, sum = cards[0], min_dist = abs(k - sum);
    pair<int, int> sol = make_pair(left, right - 1);
    while(true){
        if(sum==k) {
            sol = make_pair(left, right - 1);
            break;
        }
        if(abs(k - sum) < min_dist){
            min_dist = abs(k - sum);
            sol = make_pair(left, right - 1);
        }
        if(sum < k){
            if(right == cards.size()) break;
            sum += cards[right++];
        } else {
            sum -= cards[left++];
        }

    }
    cout << sol.first << " " << sol.second << endl;
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