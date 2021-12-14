#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long>>>>> graph;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;

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
// either flow from 0 to tmax, or flow from one station to another
int t, n, m;
void solve(){
    cin >> n >> m;
    vector<int> stations(m);
    int total_cars = 0;
    for(int i = 0; i < m; i++){
        cin >> stations[i];
        total_cars += stations[i];
    }
    vector< set<int> > timestamp_for_stations(m);

    vector<int> s(n); // source
    vector<int> t(n); // target
    vector<int> d(n); // departure time
    vector<int> a(n); // arrival time
    vector<int> p(n); // profit

    int tMax = 0;
    for(int i = 0; i < n; i++){
        cin >> s[i] >> t[i] >> d[i] >> a[i] >> p[i];
        s[i]--; t[i]--; // convert 1-based to 0-based indices
        timestamp_for_stations[s[i]].insert(d[i]);
        timestamp_for_stations[t[i]].insert(a[i]);
        tMax = max(tMax, a[i]);
    }

    // insert start and end timestamp
    for(int i = 0; i < m; i++){
        timestamp_for_stations[i].insert(0);
        timestamp_for_stations[i].insert(tMax);
       
    }

    // Assign vertex id and sort timestamps
    vector< unordered_map<int, int> > timeToIndex(m);
    vector < vector<int> > sorted_timestamp_for_stations(m);
    int id = 0;
    for(int i = 0; i < m; i++){
        for(int timestamp:timestamp_for_stations[i]){
            timeToIndex[i][timestamp] = id++;
            sorted_timestamp_for_stations[i].push_back(timestamp);
        }
        sort(sorted_timestamp_for_stations[i].begin(), sorted_timestamp_for_stations[i].end());
    }

    graph G(id);
    edge_adder adder(G);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < sorted_timestamp_for_stations[i].size()-1;j++){
            int timestamp_from = sorted_timestamp_for_stations[i][j];
            int timestamp_to = sorted_timestamp_for_stations[i][j+1];
            adder.add_edge(timeToIndex[i][timestamp_from], timeToIndex[i][timestamp_to], total_cars, 100*(timestamp_to - timestamp_from));
        }
    }

    for(int i = 0; i < n; i++){
        adder.add_edge(timeToIndex[s[i]][d[i]], timeToIndex[t[i]][a[i]], 1, 100*(a[i]-d[i])-p[i]);
    }

    int v_src = boost::add_vertex(G);
    int v_tar = boost::add_vertex(G);

    for(int i = 0; i < m; i++){
        adder.add_edge(v_src, timeToIndex[i][0], stations[i], 0);
        adder.add_edge( timeToIndex[i][tMax], v_tar,total_cars, 0);
    }

    boost::successive_shortest_path_nonnegative_weights(G, v_src, v_tar);
    int cost = boost::find_flow_cost(G);
    cost = 100 * total_cars * tMax - cost;
    cout << cost << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    while(t--){
        solve();
    }
    return 0;
}