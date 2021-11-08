///1
#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

using namespace std;
typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int t, n, m;
ET h, w;
void solve(){
    cin >> n >> m >> h >> w;
    vector< pair<ET, ET> > new_nails(n);
    vector< pair<ET, ET> > old_nails(m);
    Program lp (CGAL::SMALLER, true, 1, false, 0);
    for(int i = 0; i < n; i++){
        cin >> new_nails[i].first >> new_nails[i].second;
        lp.set_c(i, -2*(h+w));
    }
    for(int i = 0; i < m; i++){
        cin >> old_nails[i].first >> old_nails[i].second;
    }
    int num_constraints = 0;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            ET dx = abs(new_nails[i].first - new_nails[j].first);
            ET dy = abs(new_nails[i].second - new_nails[j].second);
            lp.set_a(i, num_constraints, 1);
            lp.set_a(j, num_constraints, 1);
            lp.set_b(num_constraints, max(2*(dx/w),2*(dy/h)) );
            num_constraints++;
        }
        ET min_upper_bound = -1;
        for(int j=0; j < m;j++){
            ET dx = abs(new_nails[i].first - old_nails[j].first);
            ET dy = abs(new_nails[i].second - old_nails[j].second);
            ET upper_bound = max(2*(dx/w)-1, 2*(dy/h)-1);
            if(min_upper_bound==-1 || min_upper_bound > upper_bound)
                min_upper_bound = upper_bound;
        }
        if(m > 0){
            lp.set_a(i, num_constraints, 1);
            lp.set_b(num_constraints, min_upper_bound);
            num_constraints++;
        }
    }
    Solution sol = CGAL::solve_linear_program(lp, ET());
    cout << fixed << setprecision(0) << ceil(CGAL::to_double(-sol.objective_value())) << endl;

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        solve();
    }
}
