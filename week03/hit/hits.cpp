#include<iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;
using namespace std;
int n;
long x, y, a, b, r, s, t, u;
bool res;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  while((cin >> n) && n){
    cin >> x >> y >> a >> b;
    P start(x, y), end(a, b);
    R ray(start, end);
    res = 0;
    for(int i = 0; i < n; i++){
      P left, right;
      cin >> left >> right;
      S segment(left, right);
      if(CGAL::do_intersect(ray, segment)) {
        res = 1;
        i++;
        while(i<n){
          i++;
          cin >> r >> s >> t >> u;
        }
      }
    }
    cout << (res ? "yes\n" : "no\n");
  }
  return 0;
}