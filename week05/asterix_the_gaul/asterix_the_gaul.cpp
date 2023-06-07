#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int t, n, m;
long D, T;

void compute_comb(vector< pair<long, long> >& moves, vector< pair<long, long> >& combs){
    for(int state = 0; state < (1<<(int)moves.size()); state++){
        long d_sum = 0, t_sum = 0;
        for(int i = 0; i < (int)moves.size(); i++){
            if((1<<i & state)){
                d_sum += moves[i].first;
                t_sum += moves[i].second;
            }
        }
        combs.push_back(make_pair(d_sum, t_sum));
    }
    sort(combs.begin(), combs.end(), [](auto& c1, auto& c2)->bool{
        if(c1.second == c2.second){
            return c1.first > c2.first;
        }
        return c1.second < c2.second;
    });
    long max_d = 0;
    for(auto& comb : combs){
        if(comb.first < max_d){
            comb.first = max_d;
        } else {
            max_d = comb.first;
        }
    }
}

bool feasible(vector< pair<long, long> > moves, vector<long>& gulps, int gulp){
    for(auto& move : moves){
        move.first += gulps[gulp];
    }
    vector< pair<long, long> > left_moves = vector< pair<long, long> >(moves.begin(), moves.begin() + (int)moves.size()/2);
    vector< pair<long, long> > right_moves = vector< pair<long, long> >(moves.begin() + (int)moves.size()/2, moves.end());
    vector< pair<long, long> > left_combs, right_combs;
    compute_comb(left_moves, left_combs); compute_comb(right_moves, right_combs);

    int ptr1 = 0, ptr2 = (int)right_combs.size()-1;
    while(ptr1 < (int)left_combs.size() && ptr2 >=0 ){
        if(left_combs[ptr1].first + right_combs[ptr2].first >= D){
            if(left_combs[ptr1].second + right_combs[ptr2].second < T) return true;
            ptr2--;
        } else {
            ptr1++;
        }
    }
    return false;
}

void solve(){
    cin >> n >> m >> D >> T;
    vector< pair<long, long> > moves(n);
    vector<long> gulps(m + 1);
    for(int i = 0; i < n; i++){
        cin >> moves[i].first >> moves[i].second;
    }
    gulps[0] = 0;
    for(int i = 1; i <= m; i++){
        cin >> gulps[i];
    }
    int l = 0, r = m;
    while(l < r){
        int mid = (l + r) / 2;
        if(feasible(moves, gulps, mid)){
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    if(feasible(moves, gulps, l)){
        cout << l << endl;
    } else {
        cout << "Panoramix captured\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}