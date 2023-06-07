#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor > > > > graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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
int t, n, m;

void solve(){
    cin >> n >> m;
    graph G(n);
    const vertex_desc v_src = boost::add_vertex(G);
    const vertex_desc v_tar = boost::add_vertex(G);
    edge_adder adder(G);
    long total_balance = 0;
    for(int i = 0; i < n; i++) {
        long balance; cin >> balance;
        
        if(balance>0) {
            adder.add_edge(v_src, i, balance);
            total_balance += balance;
        }
        if(balance<0) adder.add_edge(i, v_tar, -balance);
    }
    for(int i = 0; i < m; i++){
        int from, to; long debt; cin >> from >> to >> debt;
        adder.add_edge(from, to, debt);
    }
    long excluded_balance_plus_cutted_debt = boost::push_relabel_max_flow(G, v_src, v_tar);
    cout << (total_balance > excluded_balance_plus_cutted_debt ? "yes\n":"no\n");
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