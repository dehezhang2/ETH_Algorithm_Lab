#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
    cin >> n;
    vector< pair<int, int> > shifts;
    shifts.push_back(make_pair(-2, -1));shifts.push_back(make_pair(-2, 1));
    shifts.push_back(make_pair(2, -1));shifts.push_back(make_pair(2, 1));
    shifts.push_back(make_pair(1, 2));shifts.push_back(make_pair(-1, 2));
    shifts.push_back(make_pair(1, -2));shifts.push_back(make_pair(-1, -2));
    vector< vector<int> > board(n, vector<int>(n));
    graph G(n*n);
    const vertex_desc v_src = boost::add_vertex(G);
    const vertex_desc v_tar = boost::add_vertex(G);
    edge_adder adder(G);
    int node_num = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> board[i][j];
            if(board[i][j]){
                node_num ++;
                if((i+j)%2) adder.add_edge(i * n + j, v_tar, 1);
                else adder.add_edge(v_src, i * n + j, 1);
            }
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i][j] && (i+j)%2==0){
                for(auto shift : shifts){
                    int ni = i + shift.first, nj = j + shift.second;
                    if(ni >= 0 && ni < n && nj >= 0 && nj < n && board[ni][nj]){
                        adder.add_edge(i * n + j, ni * n + nj, 1);
                    }
                }
            }
        }
    }
    int max_flow = boost::push_relabel_max_flow(G, v_src, v_tar);
    cout << node_num - max_flow << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        solve();
    }
}