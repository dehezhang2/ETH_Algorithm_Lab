///3
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

int t, n, m;
long s;


void solve(){
    cin >> n >> m >> s;
    vector< pair<long, long> > nobles(n);
    vector< pair<long, long> > commons(m);

    int number_of_constraints = 0;
    long noble_sum_x = 0, noble_sum_y = 0;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    const int a = 0, b= 1, c = 2, d = 3, l = 4;
    for(int i = 0; i < n; i++){
        cin >> nobles[i].first >> nobles[i].second;
        noble_sum_x += nobles[i].first;
        noble_sum_y += nobles[i].second;
        lp.set_a(a, number_of_constraints, nobles[i].first);
        lp.set_a(b, number_of_constraints, nobles[i].second);
        lp.set_a(c, number_of_constraints, 1);
        number_of_constraints++;
    }
    long common_sum_x = 0, common_sum_y = 0;
    for(int i = 0; i < m; i++){
        cin >> commons[i].first >> commons[i].second;
        common_sum_x += commons[i].first;
        common_sum_y += commons[i].second;
        lp.set_a(a, number_of_constraints, -commons[i].first);
        lp.set_a(b, number_of_constraints, -commons[i].second);
        lp.set_a(c, number_of_constraints, -1);
        number_of_constraints++;
    }
    // set a = 1 to simplify the second constraint
    lp.set_l(a, true, 1); lp.set_u(a, true, 1);
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if(sol.is_infeasible()) {cout << "Yuck!\n"; return;}

    if(s != -1){
        lp.set_a(b, number_of_constraints, common_sum_y - noble_sum_y);
        lp.set_a(c, number_of_constraints, m - n);
        lp.set_b(number_of_constraints, s - common_sum_x + noble_sum_x);
        number_of_constraints++;
        sol = CGAL::solve_linear_program(lp, ET());
        if(sol.is_infeasible()) {cout << "Bankrupt!\n"; return ;}
    }

    for(int i = 0; i < n; i++){
        lp.set_a(b, number_of_constraints, -nobles[i].first);
        lp.set_a(d, number_of_constraints, -1);
        lp.set_a(l, number_of_constraints, -1);
        lp.set_b(number_of_constraints, -nobles[i].second);
        number_of_constraints++;

        lp.set_a(b, number_of_constraints, nobles[i].first);
        lp.set_a(d, number_of_constraints, 1);
        lp.set_a(l, number_of_constraints, -1);
        lp.set_b(number_of_constraints, nobles[i].second);
        number_of_constraints++;
    }

    for(int i = 0; i < m; i++){
        lp.set_a(b, number_of_constraints, -commons[i].first);
        lp.set_a(d, number_of_constraints, -1);
        lp.set_a(l, number_of_constraints, -1);
        lp.set_b(number_of_constraints, -commons[i].second);
        number_of_constraints++;

        lp.set_a(b, number_of_constraints, commons[i].first);
        lp.set_a(d, number_of_constraints, 1);
        lp.set_a(l, number_of_constraints, -1);
        lp.set_b(number_of_constraints, commons[i].second);
        number_of_constraints++;
    }
    lp.set_l(l, true, 0);
    lp.set_c(l, 1);

    sol = CGAL::solve_linear_program(lp, ET());
    cout << fixed << setprecision(0) << ceil(CGAL::to_double(sol.objective_value())) << endl;
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