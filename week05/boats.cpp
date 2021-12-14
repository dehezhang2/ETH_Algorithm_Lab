#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
using namespace std;
int t, n;

void solve(){
    cin >> n;
    vector<pair<int, int>> boats;
    for(int i = 0; i < n; i++){
        int l, p; cin >> l >> p;
        boats.push_back(make_pair(p, l));
    }
    sort(boats.begin(), boats.end());
    int cnt = 1, last_pos = boats[0].first;
    for(int i = 1; i < n;){
        int min_next_pos = INT_MAX;
        int next_boat = -1;
        for(int j=i; j < n; j++){
            if(boats[j].first>=min_next_pos) break;         // break when the minimum end point of boat j is larger than current result
            if(boats[j].first >= last_pos){                 // no conflict
                int next_pos = max(boats[j].first, boats[j].second+last_pos);
                if(next_pos < min_next_pos){
                    min_next_pos = next_pos;
                    next_boat = j;
                }
            }
        }
        if(next_boat==-1) break;                            // break when all boats have conflict
        i = next_boat+1;
        cnt++;
        last_pos = min_next_pos;
    }
    cout << cnt << endl;
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