#include <iostream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
using namespace std;

#define MAX 401
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        boost::no_property, boost::no_property >                graph;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor           vertex_desc;

int t, n, c, f;

bool by_string(const pair<string, int> &s1, const pair<string, int> &s2){
    return s1.first.compare(s2.first) < 0;
}

bool maximum_matching(const graph &G) {
    int n = boost::num_vertices(G);
    vector<vertex_desc> mate_map(n); // exterior property map
    vector<bool> checker(n, false);
    const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();
    boost::edmonds_maximum_cardinality_matching(G,
        boost::make_iterator_property_map(
            mate_map.begin(),
            boost::get(boost::vertex_index, G)
        )
    );
    for (int i = 0; i < n; ++i) {
        if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) {
            checker[i] = true;
            checker[mate_map[i]] = true;
        }
    }
    for(int i = 0; i < n; ++i) {
        if(!checker[i]) return false;
    }
    return true;
}

void solve(){
    cin >> n >> c >> f;
    int map[MAX][MAX]; memset(map, 0, sizeof(map));
    vector< pair<string, int> > characters;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c; j++){
            string temp_ch; cin >> temp_ch;
            characters.push_back(make_pair(temp_ch, i));
        }
    }
    stable_sort(characters.begin(),characters.end(), by_string);
    graph G(n);
    for(int i = 0; i < characters.size()-1; i++){
        for(int j = i + 1; j < characters.size() && (characters[j].first).compare(characters[i].first)==0;j++){
            if(++map[characters[i].second][characters[j].second] == f+1){
                boost::add_edge(characters[i].second, characters[j].second, G);
            }
        }
    }
    cout << (maximum_matching(G) ? "not optimal" : "optimal" )<<endl;
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