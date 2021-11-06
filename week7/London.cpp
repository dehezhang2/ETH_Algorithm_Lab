#include <iostream>
#include <string>
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
int t, h, w;

void solve(){
    cin >> h >> w;
    graph G(26*26 + 26);
    const vertex_desc v_src = boost::add_vertex(G);
    const vertex_desc v_tar = boost::add_vertex(G);
    edge_adder adder(G);

    vector<int> counter1(26);
    string evidance; cin >> evidance;
    for(int i=0; evidance[i]; i++){
        counter1[evidance[i]-'A']++;
    }
    for(int i=0; i < 26;i++){
        adder.add_edge(26*26 + i, v_tar, counter1[i]);
    }

    vector< pair<char, char> > pieces(h*w);
    for(int i=0; i<h; i++){
        for(int j=0; j < w; j++){
            cin >> pieces[i*w + j].first;
        }
    }
    for(int i=0; i<h; i++){
        for(int j=0; j < w; j++){
            cin >> pieces[i*w + w-j-1].second;
        }
    }

    vector< vector<int> > counter2(26, vector<int>(26, 0));
    for(pair<char, char> piece : pieces){
        counter2[(piece.first-'A')][ (piece.second-'A')]++;
    }

    for(int i=0; i<26; i++){
        for(int j=0; j<26; j++){
            adder.add_edge(v_src, i*26+j, counter2[i][j]);
            adder.add_edge(i*26+j, 26*26+i, counter2[i][j]);
            if(i!=j) adder.add_edge(i*26+j, 26*26+j, counter2[i][j]);
        }
    }
    long flow = boost::push_relabel_max_flow(G, v_src, v_tar);
    cout << (flow==evidance.length()? "Yes\n":"No\n");
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