#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int t, n;
void solve(){
    cin >> n;
    vector<int> locations(n);
    for(int i = 0; i < n; i++) cin >> locations[i];
    sort(locations.begin(), locations.end());
    int head = 0, tail = 0, max_customer = -1, min_max_dist = INT_MAX;
    vector<int> res;
    while(head < n && tail < n){
        int cnt = tail - head + 1 , diff = locations[tail] - locations[head];
        int dist = (diff % 2 ? diff/2 + 1 : diff/2), pos = locations[head] + dist;

        if(cnt > max_customer || cnt == max_customer && dist < min_max_dist){
            max_customer = cnt;
            min_max_dist = dist;
            res.clear();
            if(diff%2) res.push_back(pos - 1);
            res.push_back(pos);
        } else if(cnt == max_customer && dist == min_max_dist){
            if(diff%2) res.push_back(pos - 1);
            res.push_back(pos);
        }

        if(tail < n - 1 && locations[tail + 1] - locations[head] <= 200) tail++;
        else head++; 
    }
    cout << max_customer << " " << min_max_dist << endl;
    for(int location : res){
        cout << location << " ";
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}