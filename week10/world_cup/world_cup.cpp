///3
#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 Point;
typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;
int t, n, m, c;

double floor_to_double(const ET& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void solve(){
    cin >> n >> m >> c;
    vector<Point> locations(n + m);
    vector<IT> alchole(n);
    Program lp (CGAL::SMALLER, true, 0, false, 0); 
    for(int i = 0; i < n; i++){
        IT s; cin >> locations[i] >> s >> alchole[i];
        lp.set_b(i, s);
    }
    for(int i = 0; i < m; i++){
        IT d, u; cin >> locations[n + i] >> d >> u;
        lp.set_b(n + i, d);
        lp.set_b(n + m + i, -d);
        lp.set_b(n + 2*m + i, u*100);
    }
    vector< vector<double> > revenues(n, vector<double>(m));
    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> revenues[i][j];
            lp.set_a(cnt, i, 1);
            lp.set_a(cnt, n + j, 1);
            lp.set_a(cnt, n + m + j, -1);
            lp.set_a(cnt, n + 2*m + j, alchole[i]);
            cnt++;
        }
    }
    Triangulation t; t.insert(locations.begin(), locations.end());
    Point center; IT r;
    while(c--){
        cin >> center >> r;
        r *= r;
        if(CGAL::squared_distance(t.nearest_vertex(center)->point(), center) <= r){
            for(int i = 0; i < n; i++){
                bool is_inside_i = CGAL::squared_distance(locations[i], center) <= r;
                for(int j = 0; j < m; j++){
                    bool is_inside_j = CGAL::squared_distance(locations[n + j], center) <= r;
                    if(is_inside_i != is_inside_j){
                        revenues[i][j] -= 0.01;
                    }
                }
            }
        }
    }
    cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            lp.set_c(cnt++, -revenues[i][j]);
        }
    }
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if(sol.is_infeasible()){
        cout << "RIOT!\n";
    } else {
        cout << fixed << setprecision(0) << floor_to_double(-1 *ET(sol.objective_value_numerator() / sol.objective_value_denominator())) << endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}

