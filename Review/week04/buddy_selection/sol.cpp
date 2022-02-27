#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<graph>::vertex_descriptor          vertex_desc;
using namespace std;
int t, n, c, f;

bool cmp(const pair<string, int>& s1, const pair<string, int>& s2){
    return s1.first.compare(s2.first) < 0;
}

bool maximum_matching(const graph &G) {
  int n = boost::num_vertices(G);
  std::vector<vertex_desc> mate_map(n);  // exterior property map
  const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();
 
  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  vector<bool> checker(n);
  for (int i = 0; i < n; ++i) {
    // mate_map[i] != NULL_VERTEX: the vertex is matched
    // i < mate_map[i]: visit each edge in the matching only once
    if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) {
        checker[i] = true;
        checker[mate_map[i]] = true;
    }
  }
  for(auto item:checker){
      if(item==false) return false;
  }
  return true;
}

void solve(){
    cin >> n >> c >> f;
    graph G(n);
    vector< pair<string, int> > characters;
    vector< vector<int> > map(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c; j++){
            string character; cin >> character; 
            characters.push_back(make_pair(character, i));
        }
    }
    stable_sort(characters.begin(), characters.end(), cmp);
    for(int i = 0; i < characters.size()-1; i++){
        for(int j = i+1; j < characters.size() && characters[j].first.compare(characters[i].first)==0; j++){
            if(++map[characters[i].second][characters[j].second]==f+1){
                boost::add_edge(characters[i].second, characters[j].second, G);
            }
        }
    }
    cout << (maximum_matching(G)?"not optimal":"optimal") << endl;
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
