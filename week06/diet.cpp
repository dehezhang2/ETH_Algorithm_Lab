#include <iostream>
#include <cmath>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
using namespace std;
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int n, m;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> n >> m && n && m){
        Program lp (CGAL::SMALLER, true, 0, false, 0);

        for(int i = 0; i < n; i++){
            int C_min, C_max; cin >> C_min >> C_max;
            lp.set_b(i, -C_min);
            lp.set_b(n+i, C_max);
        }

        for(int j = 0; j < m; j++){
            int p; cin >> p;
            lp.set_c(j, p);
            for(int i = 0; i < n; i++){
                int C; cin >> C;
                lp.set_a(j, i, -C);
                lp.set_a(j, n+i, C);
            }
        }
        Solution s = CGAL::solve_linear_program(lp, ET());
        if(s.is_infeasible()){
            cout << "No such diet.\n";
        } else {
            int res = CGAL::to_double(s.objective_value());
            cout << fixed << setprecision(0)<< res << endl;
        }

    }
    return 0;
}