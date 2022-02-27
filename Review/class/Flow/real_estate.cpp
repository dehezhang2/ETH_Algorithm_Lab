#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs
typedef traits::vertex_descriptor                               vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator
using namespace std;

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

int t, n, m, S;

void solve(){
    cin >> n >> m >> S;
    graph G(n + m + S);
    const vertex_desc v_src = boost::add_vertex(G);
    const vertex_desc v_tar = boost::add_vertex(G);
    edge_adder adder(G);
    for(int i = 0; i < S; i++){
        int l; cin >> l;
        adder.add_edge(n+m+i,v_tar, l, 0);
    }
    for(int i = 0; i < m; i++){
        int s; cin >> s;
        // notice s is from 1
        adder.add_edge(n+i, n+m+(s-1), 1, 0);
    }
    for(int i = 0; i < n; i++){
        adder.add_edge(v_src, i, 1, 0);
        for(int j = 0; j < m; j++){
            int b; cin >> b;
            // transform to minimum cost problem
            adder.add_edge(i, n + j, 1, 100 - b);
        }
    }
    auto c_map = boost::get(boost::edge_capacity, G);
    auto rc_map = boost::get(boost::edge_residual_capacity, G);

    boost::successive_shortest_path_nonnegative_weights(G, v_src, v_tar);
    int cost = boost::find_flow_cost(G);

    // Iterate over all edges leaving the source to sum up the flow values.
    int s_flow = 0;
    out_edge_it e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(v_src,G), G); e != eend; ++e) {
        s_flow += c_map[*e] - rc_map[*e];     
    }
    cout << s_flow << " " << (100*s_flow - cost) << endl;
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