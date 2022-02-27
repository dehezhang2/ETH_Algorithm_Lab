///1
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <stdint.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;
typedef K::FT FT;

using namespace std;
int t, n;

struct Player{
    K::FT y0;
    K::FT slope;
    K::FT abs_slope;
    int index;
    bool has_intersection(const Player& l) const{
        return slope > l.slope;
    }
    bool beated(const Player& l) const{
        return abs_slope > l.abs_slope;
    }
};

bool by_intercept(const Player &lhs, const Player &rhs){
    return lhs.y0 > rhs.y0;
}

bool by_index(const Player &lhs, const Player &rhs){
    return lhs.index < rhs.index;
}

void solve(){
    cin >> n;
    vector<Player> player_list;
    for(int i = 0; i < n; i++){
      long long y0, x1, y1;
      cin >> y0 >> x1 >> y1;
      P start(0, y0), end(x1, y1);
      auto slope = (end.y()-start.y())/end.x();
      player_list.push_back({y0, slope, CGAL::abs(slope), i});
    }
    sort(player_list.begin(), player_list.end(), by_intercept);
    
    vector<Player> result_list;
    result_list.push_back(player_list[0]);
    for(int i = 1; i < n; i++){
        bool beated = 0;
        for(int j=(int)result_list.size()-1; j>=0; j--){
            Player player = result_list[j];
            if(!player_list[i].has_intersection(player)) break;
            if(player_list[i].beated(player)){
                beated = 1;
                break;
            } else {
                result_list.erase(result_list.begin()+j);
            }
        }
        if(!beated)result_list.push_back(player_list[i]);
    }
    sort(result_list.begin(), result_list.end(), by_index);
    for(auto result : result_list){
        cout << result.index<<" ";
    }
    cout << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
