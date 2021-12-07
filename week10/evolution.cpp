#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;
int t, n, q;

void dfs(
    int index, 
    vector<int>& ancestors, 
    vector< vector<int> >& tree,
    vector< pair<string, int> >& creatures, 
    vector< vector< pair<int, int> > >& queries,
    vector<string>& results){

        ancestors.push_back(index);
        for(int i = 0; i < queries[index].size(); i++){
            int l = 0, r = ancestors.size()-1;
            while(l < r){
                int mid = (l+r)/2;
                if(creatures[ancestors[mid]].second <= queries[index][i].first){
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            results[queries[index][i].second] = creatures[ancestors[l]].first;
        }

        for(int child : tree[index]){
            dfs(child, ancestors, tree, creatures, queries, results);
        }
        ancestors.pop_back();
}

void solve(){
    cin >> n >> q;
    unordered_map<string, int> to_int;
    vector< pair<string, int> > creatures(n);
    for(int i = 0; i < n; i++){
        cin >> creatures[i].first >> creatures[i].second;
        to_int[creatures[i].first] = i;
    }
    vector< vector<int> > tree(n);
    vector<bool> has_parent(n, false);
    for(int i = 0; i < n-1; i++){
        string s, p; cin >> s >> p;
        tree[to_int[p]].push_back(to_int[s]);
        has_parent[to_int[s]] = true;
    }
    int root = -1;
    for(int i = 0; i < int(has_parent.size()); i++){
        if(!has_parent[i]){
            root = i;
            break;
        }
    }
    vector< vector< pair<int, int> > > queries(n); 
    for(int i = 0; i < q; i++){
        string s; int b; cin >> s >> b;
        queries[to_int[s]].push_back(make_pair(b, i));
    }
    vector<int> ancestors;
    vector<string> results(q);
    dfs(root, ancestors, tree, creatures, queries, results);
    for(string result : results){
        cout << result << " ";
    }
    cout << endl;
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