#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

using namespace std;
int t, n;
long x, y;

void solve(){
    cin >> x >> y >> n;
    Program lp (CGAL::SMALLER, false, 0, false, 0); 
    const int px = 0, py = 1, lower_bound = 2;
    for(int i = 0; i < n; i++){
        long a, b, c, v; cin >> a >> b >> c >> v;
        if(a*x + b*y + c > 0) {
            a *= -1; b *= -1; c *= -1;
        }
        long norm = sqrt(a*a + b*b);
        lp.set_a(px, i, a); lp.set_a(py, i, b); lp.set_a(lower_bound, i, norm * v);
        lp.set_b(i, -c);
    }
    lp.set_c(lower_bound, -1);
    lp.set_l(lower_bound, true, 0);
    Solution s = CGAL::solve_linear_program(lp, ET());
    // round_down
    cout << (-s.objective_value_numerator() / s.objective_value_denominator()) << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}