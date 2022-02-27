#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
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
typedef boost::graph_traits<graph>::vertex_descriptor             vertex_desc;
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
struct Request{
    int s, t, d, a, p;
};
using namespace std;
int t, n, s;

void solve(){
    cin >> n >> s;
    vector<int> stations(s);
    int total = 0;
    for(int i = 0; i < s; i++){
        cin >> stations[i];
        total += stations[i];
    }
    vector<Request> requests(n);
    vector< set<int> > timestamp_for_station(s, set<int>());
    int t_max = 0;
    for(int i = 0; i < n; i++){
        cin >> requests[i].s >> requests[i].t >> requests[i].d >> requests[i].a >> requests[i].p;
        requests[i].s--; requests[i].t--;
        timestamp_for_station[requests[i].s].insert(requests[i].d);
        timestamp_for_station[requests[i].t].insert(requests[i].a);
        t_max = max(t_max, requests[i].a);
    }
    for(int i = 0; i < s; i++){
        timestamp_for_station[i].insert(0);
        timestamp_for_station[i].insert(t_max);
    }

    vector< unordered_map<int, int> > time_to_idx(s);
    vector< vector<int> > sorted_timestamp_for_station(s, vector<int>());
    int idx = 0;
    for(int i = 0; i < s; i++){
        for(auto timestamp:timestamp_for_station[i]){
            time_to_idx[i][timestamp] = idx++;
            sorted_timestamp_for_station[i].push_back(timestamp);
        }
        sort(sorted_timestamp_for_station[i].begin(), sorted_timestamp_for_station[i].end());
    }

    graph G(idx);
    const vertex_desc v_src = boost::add_vertex(G);
    const vertex_desc v_tar = boost::add_vertex(G);
    edge_adder adder(G);
    for(int i = 0; i < s; i++){
        adder.add_edge(v_src, time_to_idx[i][0], stations[i], 0);
        adder.add_edge(time_to_idx[i][t_max], v_tar, total, 0);
        for(int j = 0; j < (int)sorted_timestamp_for_station[i].size()-1; j++){
            int from = time_to_idx[i][sorted_timestamp_for_station[i][j]];
            int to = time_to_idx[i][sorted_timestamp_for_station[i][j+1]];
            adder.add_edge(from, to, total, 100*(sorted_timestamp_for_station[i][j+1] - sorted_timestamp_for_station[i][j]));
        }
    }
    for(int i = 0; i < n; i++){
        adder.add_edge(
            time_to_idx[requests[i].s][requests[i].d],
            time_to_idx[requests[i].t][requests[i].a],
            1, 100*(requests[i].a - requests[i].d) - requests[i].p
        );
    }
    boost::successive_shortest_path_nonnegative_weights(G, v_src, v_tar);
    int cost = boost::find_flow_cost(G);
    cout << 100*total*t_max - cost << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--) solve();
    return 0;
}