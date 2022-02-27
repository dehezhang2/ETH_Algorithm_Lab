#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;
// Graph Type with nested interior edge properties for flow algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor > > > > graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
using namespace std;

// Custom edge adder class, highly recommended
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

int t, l, p;
void solve(){
    cin >> l >> p;
    graph G(l);
    const vertex_desc v_src = boost::add_vertex(G);
    const vertex_desc v_tar = boost::add_vertex(G);
    edge_adder adder(G);
    vector< pair<int, int> > node_info(l);
    for(int i = 0; i < l; i++) cin >> node_info[i].first >> node_info[i].second;
    for(int i = 0; i < p; i++){
        int from, to, c, C; cin >> from >> to >> c >> C;
        adder.add_edge(from, to, C-c);
        node_info[from].second += c;
        node_info[to].first  += c;
    }
    long demands_sum = 0;
    for(int i = 0; i < l; i++){
        adder.add_edge(v_src, i, node_info[i].first);
        adder.add_edge(i, v_tar, node_info[i].second);
        demands_sum += node_info[i].second;
    }
    long flow = boost::push_relabel_max_flow(G, v_src, v_tar);
    cout << (flow==demands_sum? "yes\n":"no\n");

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