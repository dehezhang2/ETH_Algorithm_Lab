///4
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <vector>
#include <algorithm>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::FT                                             FT;
using namespace std;

int t, n;
struct Biker{
    FT slope, abs_slope, y_0;
    int index;
    bool intersects(const Biker& b) const{
        // the bikers should be sorted from high to low;
        return slope > b.slope;
    }
    bool beats(const Biker& b) const{
        // the bikers should be sorted from high to low;
        return abs_slope <= b.abs_slope;
    }
    bool operator<(const Biker& b) const{
        return y_0 > b.y_0;
    }
};


void solve(){
    cin >> n;
    vector<Biker> bikers;
    for(int i = 0; i < n; i++){
        long y0, x1, y1;
        cin >> y0 >> x1 >> y1;
        P start(0, y0), end(x1, y1);
        auto slope = (end.y()-start.y())/end.x();
        bikers.push_back((Biker){slope, CGAL::abs(slope), y0, i});
    }
    sort(bikers.begin(), bikers.end());
    vector<Biker> results;
    for(Biker& biker : bikers){
        bool beated = false;
        while((int)results.size() > 0 && biker.intersects(results[(int)results.size()-1])){
            if(biker.beats(results[(int)results.size()-1])){
                results.pop_back();
            } else {
                beated = true;
                break;
            }
        }
        if(!beated) results.push_back(biker);
    }
    sort(results.begin(), results.end(), [](auto& b1, auto& b2)-> bool {
        return b1.index < b2.index;
    });
    for(Biker& result : results){
        cout << result.index << " ";
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