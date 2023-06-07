#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

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

int t, m, n, k, c;
const bool in = 0;
const bool out = 1;

int get_node(int i, int j, bool node_type){ 
    int id = n*i + j;
    return node_type ? m*n+id : id;
}

void solve(){
    cin >> m >> n >> k >> c;
    graph G(2*m*n+2);
    const vertex_desc v_src = 2*m*n;
    const vertex_desc v_tar = 2*m*n + 1;
    edge_adder adder(G);
    for(int i=0;i<k;i++){
        int x, y; cin >> x >> y;
        adder.add_edge(v_src, get_node(x, y, in), 1);
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(i!=0) adder.add_edge(get_node(i, j, out), get_node(i-1, j, in), 1);
            if(i!=m-1) adder.add_edge(get_node(i, j, out), get_node(i+1, j, in), 1);
            if(j!=0) adder.add_edge(get_node(i, j, out), get_node(i, j-1, in), 1);
            if(j!=n-1) adder.add_edge(get_node(i, j, out), get_node(i, j+1, in), 1);
            adder.add_edge(get_node(i, j, in), get_node(i, j, out), c);
            if(i==0||i==m-1||j==0||j==n-1) 
                 adder.add_edge(get_node(i, j, out), v_tar, 1);
        }
    }
    long flow = boost::push_relabel_max_flow(G, v_src, v_tar);
    cout << flow << endl;
    
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