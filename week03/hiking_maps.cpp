#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangle_2.h>
using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef K::Line_2 Line;
typedef K::Triangle_2 Triangle;

int c, m, n;
struct Indexpair{
    int triangle_id;
    int leg_id;
    bool operator<(const Indexpair &o) const {
        return triangle_id < o.triangle_id;
    }
};

Line get_line(const Point& p1, const Point& p2, const Point& p3){
    // return the line in correct direction
    Line result;
    result = Line(p1, p2);
    if(result.oriented_side(p3) < 0) result = Line(p2, p1);
    return result;
}

bool is_inside(const Point& p, const Line& l1, const Line& l2, const Line& l3){
    auto side1 = l1.oriented_side(p);
    auto side2 = l2.oriented_side(p);
    auto side3 = l3.oriented_side(p);
    return (side1 >= 0 && side2 >= 0 && side3 >= 0);
}

void solve(){
    cin >> m >> n; // m points, n triangles
    
    Point temp;
    vector<Point> points;
    for(int i = 0; i < m; i++){
        cin >> temp;
        points.push_back(temp);
    }

    Point q0, q1, q2, q3, q4, q5;
    Line l1, l2, l3;
    vector<Indexpair> search_table;                             // triangle - leg pairs
    vector< vector<int> > triangle_list(m-1, vector<int>());    // list of triangles that contains the leg
    for(int i = 0; i < n; i++){
        cin >> q0 >> q1 >> q2 >> q3 >> q4 >> q5;
        l1 = get_line(q0, q1, q2);
        l2 = get_line(q2, q3, q0);
        l3 = get_line(q4, q5, q2);

        bool prev_inside = is_inside(points[0], l1, l2, l3);
        for(int j = 1; j < m; j++){
            bool inside = is_inside(points[j], l1, l2, l3);
            if(prev_inside && inside){
                search_table.push_back({i, j-1});
                triangle_list[j-1].push_back(i);
            }
            prev_inside = inside;
        }
    }

    sort(search_table.begin(), search_table.end());

    // index of the last triangle s.t. from 0 to this triangle contains all legs
    int last_triangle_id = 0;                
    for (int j = 0; j < m - 1; j++){
        last_triangle_id = max(last_triangle_id , triangle_list[j][0]);
    }
    
    int head = 0, tail = 0, min_cost = INT_MAX, max_search = search_table.size();
    vector<int> legs_cnt(m-1, 0);               // number of triangles that contains this leg so far

    while(tail + 1 < max_search
    && search_table[tail + 1].triangle_id <= last_triangle_id){
        tail++;
    }

    // make sure each interval is legal
    while(head < max_search && tail < max_search){
        int head_leg_id = search_table[head].leg_id;
        int head_tri_id = search_table[head].triangle_id;
        int tail_tri_id = search_table[tail].triangle_id;
        min_cost = min(min_cost, tail_tri_id - head_tri_id + 1);

        bool move_head = 1;
        // break if all triangles are searched
        if (legs_cnt[head_leg_id] + 1 >= triangle_list[head_leg_id].size()) break;
        else{
            // the next legal triangle id of the leg for the head
            int next_triangle_id = triangle_list[head_leg_id][ legs_cnt[head_leg_id] + 1 ];
            // there exist a legal triangle after the current one for the head
            // that legal triangle 
            move_head = head_tri_id < next_triangle_id && next_triangle_id <= tail_tri_id;
        }
        if(move_head){
            head++; legs_cnt[head_leg_id]++;
        } else {
            tail++;
        }
    }
    cout << min_cost << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> c; 
    while(c--) solve();
    return 0;
}