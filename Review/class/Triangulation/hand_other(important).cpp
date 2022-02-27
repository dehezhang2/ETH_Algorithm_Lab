///1
#include <vector>
#include <tuple>
#include <algorithm>
#include <set>
#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef std::size_t                                            Index;
typedef CGAL::Triangulation_vertex_base_with_info_2<Index,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;
typedef K::Point_2                                             Point;
typedef Tds::Vertex_handle                                     Vh;

typedef std::tuple<Index,Index,K::FT> Edge;
typedef std::vector<Edge> EdgeV;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS    // Use vecS for the VertexList! Choosing setS for the OutEdgeList disallows parallel edges.
    >          graph;
typedef boost::graph_traits<graph>::vertex_descriptor    vertex_desc;    // Vertex Descriptor: with vecS vertex list, this is really just an int in the range [0, num_vertices(G)).  
typedef boost::graph_traits<graph>::edge_iterator    edge_it;    // to iterate over all edges

using namespace std;
int t, n, k, f_0;
K::FT s_0;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int count_families(vector<int>& size_cnt, int k){
    int res = size_cnt[k];
    if(k==4){
        if(size_cnt[3] <= size_cnt[1]){
            res += size_cnt[3];
            res += ((size_cnt[1] - size_cnt[3])/2 + size_cnt[2])/2;
        } else {
            res += size_cnt[1];
            res += ((size_cnt[3] - size_cnt[1]) + size_cnt[2])/2;
        }
    } else if(k==3){
        if(size_cnt[2] <= size_cnt[1]){
            res += size_cnt[2];
            res += (size_cnt[1] - size_cnt[2])/3;
        } else {
            res += size_cnt[1];
            res += (size_cnt[2] - size_cnt[1])/2;
        }
    } else if(k==2){
        res += size_cnt[1]/2;
    }
    return res;
}

void solve(){
    cin >> n >> k >> f_0 >> s_0;
    vector<  pair<Point, int> > tents(n);
    for(int i = 0; i < n; i++){
        cin >> tents[i].first;
        tents[i].second = i;
    }
    Triangulation t; t.insert(tents.begin(), tents.end());
    EdgeV edges;
    edges.reserve(3*n); // there can be no more in a planar graph
    for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
        Index i1 = e->first->vertex((e->second+1)%3)->info();
        Index i2 = e->first->vertex((e->second+2)%3)->info();
        // ensure smaller index comes first
        if (i1 > i2) std::swap(i1, i2);
        edges.emplace_back(i1, i2, t.segment(e).squared_length());
    }
    std::sort(edges.begin(), edges.end(),[](const Edge& e1, const Edge& e2) -> bool {
        return std::get<2>(e1) < std::get<2>(e2);
    });

    boost::disjoint_sets_with_storage<> uf(n);
    Index n_components = n;
    int f_max = -1; K::FT s_max = -1;
    vector<int> size_cnt(k+1, 0); vector<int> size_of_component(n, 1); size_cnt[1] = n;
    for (EdgeV::const_iterator e = edges.begin(); e != edges.end(); ++e) {
        Index c1 = uf.find_set(std::get<0>(*e));
        Index c2 = uf.find_set(std::get<1>(*e));
        if (c1 != c2) {
            int current_f = count_families(size_cnt, k);
            if(current_f >= f_0) s_max = std::get<2>(*e);
            if(std::get<2>(*e) >= s_0) f_max = max(current_f, f_max);
            uf.link(c1, c2);
            int c = uf.find_set(c1);
            size_cnt[size_of_component[c1]]--; size_cnt[size_of_component[c2]]--;
            size_of_component[c] = min(k, size_of_component[c1] + size_of_component[c2]);
            size_cnt[size_of_component[c]] ++;
            if(--n_components==1) break;
        }
    }
    f_max = max(f_max, count_families(size_cnt, k));
    cout << floor_to_double(s_max) << " " << f_max << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    size_t t;
    for (std::cin >> t; t > 0; --t) solve();
    return 0;
}