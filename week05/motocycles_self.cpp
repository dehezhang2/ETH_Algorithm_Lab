///2
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;
typedef K::FT FT;

using namespace std;
#define MAX 500001
int t, n;
struct Player{
    long long y0;
    long long x1;
    long long y1;
    bool has_intersection(const Player& l) const{
      FT a = l.x1*(y1 - y0), b = x1*(l.y1-l.y0), c = (y0 - l.y0);
      return (a<b&&c>0)||(a>b&&c<0);
    }
    bool beat(const Player& l) const{
        FT a = l.x1*abs(y1-y0), b = x1*abs(l.y1-l.y0);
        return (a < b ||  (a==b && y0 < l.y0));
    }
};
Player player_list[MAX];

void solve(){
    cin >> n;
    // vector<bool> rec(n, 0);
    for(int i = 0; i < n; i++){
        long long y0, x1, y1;
        cin >> y0 >> x1 >> y1;
        player_list[i] = {y0, x1, y1};
    }
    vector<int> result_list;
    result_list.push_back(0);
    for(int i = 1; i < n; i++){
        bool beated = 0;
        for(int j = 0; j<(int)result_list.size(); j++){
            int index = result_list[j];
            if(player_list[i].has_intersection(player_list[index])){
              if(player_list[i].beat(player_list[index])){
                result_list.erase(result_list.begin()+j);
                j--;
              } else {
                beated = 1;
              }
            } 
        }
        if(!beated)result_list.push_back(i);
    }
    sort(result_list.begin(), result_list.end());
    for(auto index : result_list){
        cout << index<<" ";
    }
    cout << endl;
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
