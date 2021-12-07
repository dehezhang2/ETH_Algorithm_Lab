#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
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
    vector<IT> alcohol(n);

    Program lp(CGAL::SMALLER, true, 0, false, 0);
    
    for(int i = 0; i < n; i++){
        IT s; cin >> locations[i] >> s >> alcohol[i];
        lp.set_b(i, s);
    }

    for(int i = 0; i < m; i++){
        IT d, u; cin >> locations[n + i] >> d >> u;
        u *= 100; 
        lp.set_b(i + n, d);
        lp.set_b(i + n + m, -d);
        lp.set_b(i + n + 2*m, u);
    }

    vector< vector< pair<int, double> > > revenues(n, vector< pair<int, double> >(m));

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < m; j++){
    //         double revenue; cin >> revenue;
    //         revenues[i][j] = make_pair(i * n + j, -revenue);
    //         lp.set_a(i * n + j, i, 1);
    //         lp.set_a(i * n + j, j + n, 1);
    //         lp.set_a(i * n + j, j + n + m, -1);
    //         lp.set_a(i * n + j, j + n + 2*m, alcohol[i]);
    //     }
    // }
    int counter = -1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            counter++;
            double revenue; cin >> revenue;
            revenues[i][j] = make_pair(counter, -revenue);
            lp.set_a(counter, i, 1);
            lp.set_a(counter, j + n, 1);
            lp.set_a(counter, j + n + m, -1);
            lp.set_a(counter, j + n + 2*m, alcohol[i]);
        }
    }

    Triangulation tri;
    tri.insert(locations.begin(), locations.end());

    for(int i = 0; i < c; i++){
        Point center; long r; cin >> center >> r;
        r *= r;
        if(CGAL::squared_distance(tri.nearest_vertex(center)->point(), center) <= r) {
            for(int i = 0; i < n; i++){
                bool is_inside_i = (CGAL::squared_distance(center, locations[i]) <= r);
                for(int j = 0; j < m; j++){
                    bool is_inside_j = (CGAL::squared_distance(center, locations[n + j]) <= r);
                    if(is_inside_i != is_inside_j){
                        revenues[i][j].second += 0.01;
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            lp.set_c(revenues[i][j].first, ET(revenues[i][j].second));
        }
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    if(s.is_infeasible()) cout << "RIOT!\n";
    else cout << fixed << setprecision(0) << floor_to_double(( -1 * ET( s.objective_value_numerator() / s.objective_value_denominator() ) )) << "\n";
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