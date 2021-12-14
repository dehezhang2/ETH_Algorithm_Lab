#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int t, n;

bool is_leaf(int index){ return index >= (n-1)/2;}

bool feasible(vector<int>& explode_times, int& used_time, vector<bool>& isok, int index){
    if(isok[index]) return isok[index];

    if(is_leaf(index)) {
        isok[index] = (used_time < explode_times[index]);
    } else{
        isok[index] = (used_time < explode_times[index]) && feasible(explode_times, used_time, isok, 2*index+1)
                  && feasible(explode_times, used_time, isok, 2*index+2) && (used_time < explode_times[index]) ;
    }
    if(isok[index]) used_time++;
    return isok[index];
}

void solve(){
    cin >> n;
    vector<int> explode_times(n);
    vector< pair<int, int> > bombs(n);
    vector<bool> isok(n, 0);
    for(int i = 0; i < n; i++){
        cin >> explode_times[i];
        bombs[i] = make_pair(explode_times[i], i);
    }
    sort(bombs.begin(), bombs.end());
    bool success = true;
    int used_time = 0;

    // deactivate according to the order
    for(int i = 0; success && i < n;i++)
        success = feasible(explode_times, used_time, isok, bombs[i].second);
    cout << (success ? "yes\n" : "no\n");
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