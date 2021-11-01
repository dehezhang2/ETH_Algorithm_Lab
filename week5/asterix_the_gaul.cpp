#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
int t, n, m;
long D, T;

bool by_time_dist(pair<long, long> &x, pair<long, long> &y){
    return x.second == y.second ? x.first > y.first : x.second < y.second;
}

void calculate_split(vector< pair<long, long> >& half_moves, vector< pair<long, long> >& half_combinations){
    for(int state = 0; state < (1<<half_moves.size()); state++){
        long D_sum = 0, T_sum = 0;
        for(int digit = 0; digit < (int)half_moves.size(); digit++){
            if(state & (1 << digit)){
                D_sum += half_moves[digit].first;
                T_sum += half_moves[digit].second;
            }
        }
        half_combinations.push_back(make_pair(D_sum, T_sum));
    }
    // sort(half_combinations.begin(), half_combinations.end(), by_time_dist);
    // // if use more time result in less distance, update to the maximum distance before
    // // => make sure the list is increasing for linear search
    // long max_d = 0; 
    // for (auto & p : half_combinations) {
    //     if (max_d > p.first) {
    //         p.first = max_d;
    //     } else {
    //         max_d = p.first;
    //     }
    // }
}

bool has_solution(long gulp, vector< pair<long, long> > moves){
    for(auto &move : moves){
        move.first += gulp;
    }
    vector< pair<long, long> > left_moves = vector< pair<long, long> >(moves.begin(), moves.begin() + m/2);
    vector< pair<long, long> > right_moves = vector< pair<long, long> >(moves.begin() + m/2, moves.end());
    vector< pair<long, long> > left_combinations, right_combinations;
    // calculate_split(left_moves, left_combinations);
    // calculate_split(right_moves, right_combinations);
    for(int state = 0; state < (1<<left_moves.size()); state++){
        long D_sum = 0, T_sum = 0;
        for(int digit = 0; digit < (int)left_moves.size(); digit++){
            if(state & (1 << digit)){
                D_sum += left_moves[digit].first;
                T_sum += left_moves[digit].second;
            }
        }
        left_combinations.push_back(make_pair(D_sum, T_sum));
    }
    for(int state = 0; state < (1<<right_moves.size()); state++){
        long D_sum = 0, T_sum = 0;
        for(int digit = 0; digit < (int)right_moves.size(); digit++){
            if(state & (1 << digit)){
                D_sum += right_moves[digit].first;
                T_sum += right_moves[digit].second;
            }
        }
        right_combinations.push_back(make_pair(D_sum, T_sum));
    }
    
    for(auto left_combination : left_combinations){
        for(auto right_combination : right_combinations){
            long D_sum = left_combination.first + right_combination.first;
            long T_sum = left_combination.second + right_combination.second;
            if(D_sum>=D && T_sum < T) return true;
        }
    }
    return false;
}

void solve(){
    cin >> n >> m >> D >> T;
    vector< pair<long, long> > moves;
    for(int i = 0 ; i < n; i++){
        long d, t; cin >> d >> t;
        moves.push_back(make_pair(d,t));
    }
    vector<long> gulps;
    for(int i = 0; i < m; i++){
        long s; cin >> s;
        gulps.push_back(s);
    }
    int l = 0, r = m-1;
    while(l<r){
        int mid = (l+r)/2;
        if(has_solution(gulps[mid], moves)){
            r = mid;
        } else{
            l = mid + 1;
        }
    } 
    if(has_solution(gulps[l], moves)){
        cout << l << endl;
    } else {
        cout << "Panoramix captured\n";
    }
    
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