///1
#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
// choose input type (input coefficients must fit)
typedef int IT;
// choose exact type for solver (CGAL::Gmpz or CGAL::Gmpq)
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
using namespace std;
int t, n, m;
ET h, w;

void solve(){
    cin >> n >> m >> h >> w;
    vector< pair<ET, ET> > new_nails;
    vector< pair<ET, ET> > old_nails;
    Program lp (CGAL::SMALLER, true, 1, false, 0);
    for(int i = 0 ; i < n; i++){
        ET x, y; cin >> x >> y;
        new_nails.push_back(make_pair(x, y));
        lp.set_c(i, -2*(h+w));
    }
    for(int i = 0; i < m; i++){
        ET x, y; cin >> x >> y;
        old_nails.push_back(make_pair(x, y));
    }
    int num_of_constraint = 0;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            ET dx = abs(new_nails[i].first - new_nails[j].first);
            ET dy = abs(new_nails[i].second - new_nails[j].second);
            if(dx*h < dy*w){
                lp.set_a(i, num_of_constraint, h);
                lp.set_a(j, num_of_constraint, h);
                lp.set_b(num_of_constraint, 2*abs(new_nails[i].second - new_nails[j].second));
            } else {
                lp.set_a(i, num_of_constraint, w);
                lp.set_a(j, num_of_constraint, w);
                lp.set_b(num_of_constraint, 2*abs(new_nails[i].first - new_nails[j].first));
            }
            num_of_constraint++;
        }
        ET min_upper_bound = -1; int min_pos = -1; int is_y = -1;
        for(int j = 0; j < m; j++){
            ET dx = abs(new_nails[i].first - old_nails[j].first);
            ET dy = abs(new_nails[i].second - old_nails[j].second);
            ET upper_bound;
            if(dx * h < dy * w){
                upper_bound = dy * w;
            } else {
                upper_bound = dx * h;
            }
            if(min_upper_bound == -1 || min_upper_bound > upper_bound ){
                min_upper_bound = upper_bound;
                min_pos = j;
                is_y = (dx * h < dy * w);
            }
        }
        if(m>0){
            if(is_y){
                lp.set_a(i, num_of_constraint, h);
                lp.set_b(num_of_constraint, 2*abs(new_nails[i].second - old_nails[min_pos].second) - h);
            } else {
                lp.set_a(i, num_of_constraint, w);
                lp.set_b(num_of_constraint, 2*abs(new_nails[i].first - old_nails[min_pos].first) - w);
            }
            num_of_constraint++;
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
    return 0;
}