#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int t, n, k, m;
bool rec[4];

int cal_single(const vector<int>& players){
    int cnt = 0, score = 0, tail = players.size();
    int num = min(m, (int)players.size());
    memset(rec, 0, sizeof(rec));
    while(score < k && cnt < num){
        int player = players[--tail];
        cnt++;
        if(!rec[player]){
            rec[player]=1;
            score++;
        }
    }
    return score;
}

int cal_both(const vector<int>& north, const vector<int>& south, bool is_north){
    int p = north.size(), q = south.size();
    return (is_north ? cal_single(north):cal_single(south))*1000 - (1<<abs(p-q));
}

int score(int head, const vector<int>& players, vector<int>& north, vector<int>& south){
    if(head == players.size()) return 0;
    north.push_back(players[head]);
    int score1 = score(head+1, players, north, south) + cal_both(north, south, 1);
    north.pop_back();

    south.push_back(players[head]);
    int score2 = score(head+1, players, north, south) + cal_both(north, south, 0);
    south.pop_back();
    // cout <<  score1 << " " << score2 << endl;
    return max(score1, score2);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> k >> m;
        vector<int> players, north, south;
        for(int i = 0; i < n; i++){
            int type; cin >> type;
            players.push_back(type);
        }
        north.push_back(players[0]);
        cout << score(1, players, north, south) + 998 << endl;
    }
    return 0;
}