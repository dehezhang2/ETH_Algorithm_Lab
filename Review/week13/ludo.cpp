#include <iostream>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;
using namespace std;

// Custom edge adder class
class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};
int t, e, w, m, d, p, l;

void solve(){
    cin >> e >> w >> m >> d >> p >> l;
    graph G(2*e + 2*w);
    edge_adder adder(G);
    const vertex_desc v_src = boost::add_vertex(G);
    const vertex_desc v_tar = boost::add_vertex(G);
    const vertex_desc v_e_free = boost::add_vertex(G);
    const vertex_desc v_w_free = boost::add_vertex(G);
    for(int i = 0; i < e; i++){
        adder.add_edge(v_src, i, l, 0);
        adder.add_edge(v_e_free, i, p - e*l, 0);
        adder.add_edge(v_e_free, e + w + i, p - e*l, 0);
    }
     adder.add_edge(v_src,v_e_free, p - e*l, 0);
    for(int i = e; i < e + w; i++){
        adder.add_edge(i, v_tar, l, 0);
        adder.add_edge(i, v_w_free, p - w*l, 0);
        adder.add_edge(e + w + i, v_w_free, p - w*l, 0);
    }
    adder.add_edge(v_w_free, v_tar, p - w*l, 0);
    for(int i = 0; i < m; i++){
        int u, v, r; cin >> u >> v >> r;
        adder.add_edge(u, e + v, 1, r);
    }
    for(int i = 0; i < d; i++){
        int u, v, r; cin >> u >> v >> r;
        adder.add_edge(e + w + u, 2*e + w + v, 1, r);
    }
    bool feasible = (p - e*l >= 0 && p - w * l >= 0 && 
        boost::push_relabel_max_flow(G, v_src, v_tar) == p
    );
    if(feasible){
        boost::successive_shortest_path_nonnegative_weights(G, v_src, v_tar);
        int cost2 = boost::find_flow_cost(G);
        cout << cost2 << endl;
    } else {
        cout << "No schedule!\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}