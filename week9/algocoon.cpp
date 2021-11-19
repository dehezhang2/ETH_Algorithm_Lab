#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cmath>
#include <climits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor > > > > graph;
typedef traits::vertex_descriptor                               vertex_desc;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;
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

int t, n, m;

void solve(){
    cin >> n >> m;
    graph G(n);
    edge_adder adder(G);
    for(int i = 0; i < m; i++){
        int a, b, c; cin >> a >> b >> c;
        adder.add_edge(a, b, c);
    }
    auto rc_map = boost::get(boost::edge_residual_capacity, G);


    int res_src = 0, res_tar = 1;
    int min_cut = boost::push_relabel_max_flow(G, res_src, res_tar);
    for(int i = 1; i < n; i++){
        int src = i, tar = (i + 1)%n;
        int flow = boost::push_relabel_max_flow(G, src, tar);
        if(flow < min_cut){
            min_cut = flow;
            res_src = src;
            res_tar = tar;
        }

    }
    cout << min_cut << endl;
    vector<int> vis(n, false); // visited flags
	queue<int> Q; // BFS queue (from std:: not boost::)
	vis[res_src] = true; // Mark the source as visited
	Q.push(res_src);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		out_edge_it ebeg, eend;
		for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = boost::target(*ebeg, G);
			// Only follow edges with spare capacity
			if (rc_map[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			Q.push(v);
		}
	}
	// Output S
    int cnt = 0; 
    string out = "";
	for (int i = 0; i < n; ++i) {
		if (vis[i]){ out.append(" " + to_string(i));cnt++;}
        
	}
	cout << cnt << out<< "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        solve();
    }
}