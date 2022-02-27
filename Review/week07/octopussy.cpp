#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int t, n;

bool feasible(vector<int>& explosion_times, vector<bool>& isok, int& used_time, int index){
    if(isok[index]) return true;
    if(index >= (n-1)/2){
        isok[index] = (used_time < explosion_times[index]);
    } else {
        isok[index] = (used_time < explosion_times[index] && feasible(explosion_times, isok, used_time, 2*index + 1)
                    &&feasible(explosion_times, isok, used_time, 2*index + 2) &&  used_time < explosion_times[index]);
    }
    if(isok[index]) used_time++;
    return isok[index];
}

void solve(){
    cin >> n;
    vector<int> explosion_times(n);
    vector< pair<int, int> > bombs(n);
    for(int i = 0; i < n; i++){
        cin >> explosion_times[i];
        bombs[i] = make_pair(explosion_times[i], i);
    }
    sort(bombs.begin(), bombs.end());
    int used_time = 0;
    vector<bool> isok(n, false);
    bool success = true;
    for(auto& bomb : bombs){
        success = feasible(explosion_times, isok, used_time, bomb.second);
        if(!success) break;
    }
    cout << (success ? "yes":"no") << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}