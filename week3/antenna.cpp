#include <iostream>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Algebraic_structure_traits.h>
#include <vector>
using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;
typedef K::FT FT;

int n;
double ceil_to_double(const K::FT& x){
    double a = ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> n && n){
        vector<P> points;
        for (int i = 0; i < n; ++i){
            long x, y;
            cin >> x >> y;
            points.push_back(P(x, y));
        }
        Min_circle mc(points.begin(), points.end(), true);
        Traits::Circle c = mc.circle();
        cout << fixed << setprecision(0) << ceil_to_double(sqrt(c.squared_radius())) << "\n";
    }
    return 0;
}