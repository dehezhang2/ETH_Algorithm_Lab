#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>
using namespace std;

#define MAX 30001
namespace boost
{
struct edge_component_t
{
    enum
    {
        num = 555
    };
    typedef edge_property_tag kind;
} edge_component;
}

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        boost::no_property, boost::property<boost::edge_component_t, int> > graph_t;
typedef boost::graph_traits<graph_t>::edge_descriptor                       edge_desc;
typedef boost::graph_traits<graph_t>::vertex_descriptor                     vertex_desc;
int c, n, m;

void solve(){
    cin >> n >> m;
    
    graph_t G(n);
    for(int i = 0; i < m; i++){
        int start, end;
        cin >> start >> end;
        boost::add_edge(start, end, G);
    }
    boost::property_map< graph_t, boost::edge_component_t >::type component
        = get(boost::edge_component, G);
    int num_comps = boost::biconnected_components(G,component);
    boost::graph_traits< graph_t >::edge_iterator ei, ei_end;
    vector<int> cnt(num_comps,0);
    for (boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei){
        cnt[component[*ei]]++;
    }
    vector< pair<int, int> > edge_list;
    for (boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei){
        if(cnt[component[*ei]] == 1){
            int src = boost::source(*ei, G);
            int tar = boost::target(*ei, G);
            edge_list.push_back(make_pair(min(src, tar), max(src, tar)));
        }
    }
    sort(edge_list.begin(), edge_list.end());
    cout << edge_list.size() << endl;
    for(auto edge : edge_list){
        cout << edge.first << " " << edge.second <<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> c;
    while(c--){
        solve();
    }
    return 0;
}