#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int t, n, k;

void solve(){
    cin >> n >> k;
    vector<int> cards(n);
    int min_card = INT_MAX;
    int pos = -1;
    for(int i = 0; i < n; i++){
        cin >> cards[i];
       if(min_card  > cards[i]){
        pos = i; min_card = cards[i];
       }
    }
    if(k==0) {cout << pos << " " << pos << endl; return;}
    int left = 0, right = 0, sum = 0, min_dist = INT_MAX;
    pair<int, int> sol = make_pair(0, 0);
    while(true){
        if(sum < k){
            if(right == cards.size()) break;
            sum += cards[right++];
        } else {
            sum -= cards[left++];
        }
        if(abs(k - sum) < min_dist){
            min_dist = abs(k - sum);
            sol = make_pair(left, right - 1);
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