#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>
using namespace std;

typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
int n, d;


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> n && n){
        Program lp (CGAL::SMALLER, false, 0, false, 0);
        cin >> d;
        for(int i = 0; i < n; i++){
            int sum_of_square = 0;
            for(int x = 0; x < d; x++){
                int a; cin >> a;
                sum_of_square += a*a;
                lp.set_a(x, i, a);
            }
            lp.set_a(d, i, (int)sqrt(sum_of_square));
            int b; cin >> b;
            lp.set_b(i, b);
        }
        lp.set_l(d, true, 0);
        lp.set_c(d, -1);

        Solution s = CGAL::solve_linear_program(lp, ET());

        if(s.is_infeasible()){
            cout << "none\n";
        } else if(s.is_unbounded()){
            cout <<"inf\n";
        } else {
            int res = CGAL::to_double(-s.objective_value());
            cout << fixed << setprecision(0)<< res << endl;
        }
    }
    return 0;
}
