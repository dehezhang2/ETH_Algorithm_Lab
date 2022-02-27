#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int t, n, m;

bool feasible(vector<int>& friends, vector<int>& boxes, int round){
    int moved_sum = 0;
    for(int s : friends){
        if(moved_sum >= m) return true;
        // equal sign important
        if(s >= boxes[moved_sum]){
            moved_sum += round;
        } else break;
    }
    return moved_sum >= m;
}

void solve(){
    cin >> n >> m;
    vector<int> friends(n), boxes(m);
    for(int i = 0; i < n; i++) cin >> friends[i];
    for(int i = 0; i < m; i++) cin >> boxes[i];
    sort(friends.rbegin(), friends.rend());
    sort(boxes.rbegin(), boxes.rend());
    if(boxes[0] > friends[0]) {cout << "impossible\n"; return;}
    int l = 0, r = m;
    while(l < r){
        int mid = (l + r) / 2 ;
        if(feasible(friends, boxes, mid)){
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << 3*l - 1 << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}