///1
#include<iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <stdint.h>
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
typedef K::FT FT;
using namespace std;

int n;
int64_t x, y, a, b;
bool have_intersect, have_better_intersect;
 
double floor_to_double(const FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  while((cin >> n) && n){
    cin >> x >> y >> a >> b;
    P start(x, y), end(a, b);
    R ray(start, end);
    S best_segment;
    P intersect_point;

    have_intersect = 0;
    vector<S> segments;
    FT min_distance = -1;

    for(int i = 0; i < n; i++){
      cin >> x >> y >> a >> b;
      S segment(P(x, y), P(a, b));
      segments.push_back(segment);
    }
    random_shuffle(segments.begin(), segments.end());

    for(int i = 0; i < n; i++){
        have_better_intersect = 0;
        if(have_intersect) have_better_intersect = CGAL::do_intersect(segments[i], best_segment);
        else have_better_intersect = CGAL::do_intersect(segments[i], ray);
        if(have_better_intersect){
            have_intersect = 1;
            auto o = CGAL::intersection(ray,segments[i]);
            if (const P* op = boost::get<P>(&*o))
                intersect_point = *op;
            else if (const S* os = boost::get<S>(&*o)) {
                if(CGAL::squared_distance(start, os->source()) < CGAL::squared_distance(start, os->target())) intersect_point = os->source();
                else intersect_point = os->target();
            }
            S seg(start, intersect_point);
            best_segment = seg;
        }
    }

    if(!have_intersect) cout << "no\n";
    else  cout << setiosflags(ios::fixed) << setprecision(0) << floor_to_double(intersect_point.x()) << " " << floor_to_double(intersect_point.y()) << endl;


  }
  return 0;
}