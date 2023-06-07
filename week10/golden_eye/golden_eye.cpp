///1
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <climits>

// Epic kernel is enough, no constructions needed, provided the squared distance
// fits into a double (!)
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
// we want to store an index with each vertex
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2                                             Point;
typedef K::FT                                                  FT;
using namespace std;

struct Query{
    int from, to;
    FT max_dist_to_jammer;
    bool success;
};

struct Edge{
    int from, to;
    FT distance;
    bool operator<(const Edge& e) const{
        return distance < e.distance;
    }
};

double ceil_to_double(const K::FT &x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a < x)
        a += 1;
    while (a - 1 >= x)
        a -= 1;
    return a;
}

int n, m;
FT p;

void solve(){
    cin >> n >> m >> p;
    vector< pair<Point, int> > jammers(n);
    for(int i = 0; i < n; i++){
        cin >> jammers[i].first;
        jammers[i].second = i;
    }

    Triangulation t; t.insert(jammers.begin(), jammers.end());
    vector<Edge> edges;
    boost::disjoint_sets_with_storage<> emst1(n);
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second+1)%3)->info();
        Index i2 = e->first->vertex((e->second+2)%3)->info();
        if (i1 > i2) std::swap(i1, i2);
        FT distance = t.segment(e).squared_length();
        if( distance <= p){
            emst1.union_set(i1, i2);
        }
        edges.push_back((Edge){i1, i2, distance});
        
    }
    std::sort(edges.begin(), edges.end());

    vector<Query> queries(m);
    Point start, end;
    for(int i = 0; i < m; i++){
        cin >> start >> end;
        auto from = t.nearest_vertex(start);
        auto to = t.nearest_vertex(end);
        FT distance = CGAL::max(
            CGAL::squared_distance(from->point(), start),
            CGAL::squared_distance(to->point(), end)
        ) * 4;
        bool success = (distance <= p && emst1.find_set(from->info()) == emst1.find_set(to->info()));
        cout << (success ? "y":"n");
        queries.push_back((Query){from->info(), to->info(), distance, success});
    }
    cout << endl;

    boost::disjoint_sets_with_storage<> emst2(n);    
    FT a = 0;
    int j = 0;
    for(auto& query : queries){
        a = max(a, query.max_dist_to_jammer);
        for(; j < (int)edges.size() && emst2.find_set(query.from) != emst2.find_set(query.to); j++){
            Index c1 = emst2.find_set(edges[j].from);
            Index c2 = emst2.find_set(edges[j].to);
            if (c1 != c2) {
                emst2.link(c1, c2);
                a = max(a, edges[j].distance);
            }
        }
    }

    boost::disjoint_sets_with_storage<> emst3(n);    
    FT b = 0;
    j = 0;
    for(auto& query : queries){
        if(query.success){
            b = max(b, query.max_dist_to_jammer);
            for(; j < (int)edges.size() && emst3.find_set(query.from) != emst3.find_set(query.to); j++){
                Index c1 = emst3.find_set(edges[j].from);
                Index c2 = emst3.find_set(edges[j].to);
                if (c1 != c2) {
                    emst3.link(c1, c2);
                    b = max(b, edges[j].distance);
                }
            }
        }
    }
    cout << ceil_to_double(a) << endl << ceil_to_double(b) << endl;
}

int main() 
{
  std::ios_base::sync_with_stdio(false);
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
  std::size_t t;
  for (std::cin >> t; t > 0; --t) solve();
  return 0;
}