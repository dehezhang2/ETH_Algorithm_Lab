#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Line_2  Line;

using namespace std;
int t, m, n;

Line getline(Point& q0, Point& q1, Point& q2){
    Line l(q0, q1);
    return (l.oriented_side(q2) < 0) ? Line(q1, q0) : l;
}

bool inside(Line& l1, Line& l2, Line& l3, Point& p){
    return l1.oriented_side(p) >= 0 && l2.oriented_side(p) >= 0 && l3.oriented_side(p) >= 0;
}

void solve(){
    cin >> m >> n;
    vector<Point> locations(m);
    for(int i = 0; i < m; i++) cin >> locations[i];
    vector< vector<int> > contained_in_triangle(n, vector<int>());
    for(int i = 0; i < n; i++){
        Point q0, q1, q2, q3, q4, q5; 
        cin >> q0 >> q1 >> q2 >> q3 >> q4 >> q5;
        Line l1 = getline(q0, q1, q2);
        Line l2 = getline(q2, q3, q4);
        Line l3 = getline(q4, q5, q0);
        for(int j = 0; j < m - 1; j++){
            if(inside(l1, l2, l3, locations[j]) && inside(l1, l2, l3, locations[j + 1]))
                contained_in_triangle[i].push_back(j);
        }
    }
    int l = 0, r = 0, total_leg = 0, res = INT_MAX; 
    vector<int> leg_cnt(m - 1, 0);
    while(l < n && r < n){
        while(total_leg < m - 1 && r < n){
            for(int leg : contained_in_triangle[r]){
                if(leg_cnt[leg]==0) total_leg++;
                leg_cnt[leg]++;
            }
            r++;
        }
        while(total_leg == m - 1 && l < n){
            res = min(res, r - l);
            for(int leg : contained_in_triangle[l]){
                leg_cnt[leg]--;
                if(leg_cnt[leg]==0) total_leg--;
            }
            l++;
        }
    }
    cout << res << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();    
    return 0;
}