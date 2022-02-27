#include <iostream>
// BGL include
#include <boost/graph/adjacency_list.hpp>

// BGL flow include *NEW*
#include <boost/graph/push_relabel_max_flow.hpp>
// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor > > > > graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
using namespace std;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};
int t, n, m, s, d;

void solve(){
    cin >> n >> m >> s >> d;
    graph G(2*n); 
    const vertex_desc v_src = boost::add_vertex(G);
    const vertex_desc v_tar = boost::add_vertex(G);
    edge_adder adder(G);
    for(int i = 0; i < m; i++){
        int u, v; cin >> u >> v;
        adder.add_edge(n + u, v, 1);
    }
    for(int i = 0; i < s; i++){
        int x; cin >> x;
        adder.add_edge(v_src, x, 1);
    }
    for(int i = 0; i < d; i++){
        int x; cin >> x;
        adder.add_edge(n + x, v_tar, 1);
    }
    for(int i = 0; i < n; i++){
        adder.add_edge(i, n + i, 1);
    }
    long flow =  boost::push_relabel_max_flow(G, v_src, v_tar);
    cout << flow << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}