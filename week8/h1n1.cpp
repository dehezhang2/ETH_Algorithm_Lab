#include <iostream>
#include <vector>
#include <climits>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<long, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef K::Point_2 Point;

typedef boost::property<boost::edge_weight_t, long> EdgeWeightProperty;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property, EdgeWeightProperty>
    weighted_graph;

typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

using namespace std;
int n, m;

double floor_to_double(const K::FT &x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x)
        a -= 1;
    while (a + 1 <= x)
        a += 1;
    return a;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(cin >> n && n){
        vector<Point> pts(n);
        for(int i = 0; i < n; i++) cin >> pts[i];
        Triangulation t;
        t.insert(pts.begin(), pts.end());
        int face_idx = 0;
        for(auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f, face_idx++)
            f->info() = face_idx;

        const int infinite = t.number_of_faces();
        weighted_graph G(infinite+ 1);
        const long MAX_VAL = (numeric_limits<long>::max() / 2);

        for(auto f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f){
            for(int i = 0; i < 3; i++){
                const auto p1 = f->vertex((i+1)%3);
                const auto p2 = f->vertex((i+2)%3);
                const long weight = (long)floor_to_double(CGAL::squared_distance(p1->point(), p2->point())/4);
                const auto neighbor = f->neighbor(i);
                if(t.is_infinite(neighbor)){
                    boost::add_edge(f->info(), infinite, EdgeWeightProperty(MAX_VAL-weight), G);
                } else if(f->info() < neighbor->info()){
                    boost::add_edge(f->info(), neighbor->info(), EdgeWeightProperty(MAX_VAL-weight), G);
                }
            }
        }
        vector<vertex_desc> predMap(infinite+1);
        vector<long> weightToPredecessorMap(infinite+1);
        boost::prim_minimum_spanning_tree(G, 
            boost::make_iterator_property_map(
                predMap.begin(), 
                boost::get(boost::vertex_index, G)
            ),
            boost::root_vertex(infinite).distance_map(
                boost::make_iterator_property_map(
                    weightToPredecessorMap.begin(), 
                    boost::get(boost::vertex_index, G)
                )
            )
        );
        cin >> m;
        for(int i = 0; i < m; i++){
            Point query; cin >> query;
            long disk_width; cin >> disk_width;
            auto start = t.nearest_vertex(query);
            auto start_dist = CGAL::squared_distance(start->point(), query);
            if(start_dist >= disk_width){cout <<"n"; continue;}
            auto start_face = t.locate(query);
            if(t.is_infinite(start_face)){cout<<"y"; continue;}
            vertex_desc current;
            for(current = start_face->info(); 
                current != infinite && ( MAX_VAL-weightToPredecessorMap[current]) >= disk_width; 
                current=predMap[current]
            );
            cout << (current==infinite) ? "y" : "n";
        }
        cout << endl;
    }
    return 0;
}