#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int t, n;
long x, y;
void solve(){
    cin >> x >> y >> n;
    const int px = 0, py = 1, lower = 2;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    for(int i = 0; i < n; i++){
        long a, b, c, v; cin >> a >> b >> c >> v;
        long sign = (a*x + b*y + c > 0 ? -1 : 1);
        a *= sign; b *= sign; c *= sign;
        long norm = long(sqrt(a*a + b*b));
        lp.set_a(px, i, a);
        lp.set_a(py, i, b);
        lp.set_a(lower, i, v*norm);
        
        lp.set_b(i, -c);
    }
    lp.set_c(lower, -1);
    lp.set_l(lower, true, 0);
    Solution s = CGAL::solve_linear_program(lp, ET());
    cout << (- s.objective_value_numerator() / s.objective_value_denominator()) << endl;
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