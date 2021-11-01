#include <iostream>
#include <cmath>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;
int p, a, b;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> p >> a >> b){
        
        // set the coefficients of A and b
        const int X = 0;
        const int Y = 1;
        const int Z = 2;
        Solution s;
        if(p==1){
          Program lp (CGAL::SMALLER, true, 0, false, 0);
          lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 4);   // x + y <= 4
          lp.set_a(X, 1, 4); lp.set_a(Y, 1, 2); lp.set_b(1, a*b); // 4x + 2y <= 1
          lp.set_a(X, 2, -1); lp.set_a(Y, 2, 1); lp.set_b(2, 1);  // -x + y <= 1
          lp.set_c(X, a); // ax
          lp.set_c(Y, -b); // -by
          s = CGAL::solve_linear_program(lp, ET());
        } else {
          Program lp (CGAL::SMALLER, false, 0, true, 0);
          lp.set_a(X, 0, -1); lp.set_a(Y, 0, -1); lp.set_b(0, 4);   // -x - y <= 4
          lp.set_a(X, 1, -4); lp.set_a(Y, 1, -2); lp.set_a(Z, 1, -1); lp.set_b(1, a*b); // -4x - 2y - z <= ab
          lp.set_a(X, 2, 1); lp.set_a(Y, 2, -1); lp.set_b(2, 1);  // x - y <= 1
          lp.set_c(X, a); // ax
          lp.set_c(Y, b); // by
          lp.set_c(Z, 1); // z
          s = CGAL::solve_linear_program(lp, ET());
        }

        // objective function
        if(s.is_infeasible()){
            cout << "no\n";
        } else if (s.is_unbounded()){
            cout << "unbounded\n";
        } else {
            int res = ceil(CGAL::to_double(s.objective_value()));
            if(p==1) res = -res;
            cout << fixed << setprecision(0)<< res << endl;
        }

    }
    return 0;
}