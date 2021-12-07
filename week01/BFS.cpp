#include <iostream>
#include <queue>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX 1000
int t, n, m, v, dist[MAX];

struct Node{
  int val;
  vector<int> next;
};

struct Path{
    int id;
    int depth;
    Path(int i,int l):id(i),depth(l){}
};

Node map[MAX];

// important: record the node before dequeue
void bfs(int src){
    memset(dist,-1,sizeof(dist));
    queue<Path*> path;
    path.push(new Path(src,0));dist[src]=0;
    while(!path.empty()){
        int id = path.front()->id, depth = path.front()->depth; path.pop();
        for(int i=0; i<map[id].next.size(); i++){
            int next_id = (map[id].next)[i], next_depth = depth + 1;
            if(dist[next_id]==-1){
                path.push(new Path(next_id, next_depth));
                dist[next_id] = depth + 1;
            }
        }
    }
}

int main(){
  ios_base::sync_with_stdio(false);
  cin >> t;
  while(t--){
    cin >> n >> m >> v;
    memset(map, 0, sizeof(map));
    for (int i = 0; i < m; i++){
      int a, b; cin >> a >> b;
      map[a].next.push_back(b);
      map[b].next.push_back(a);
    }
    bfs(v);
    for (int i=0;i < n;i++){
      if(i) cout << " ";
      cout << dist[i];
    }
    cout << endl;
  }
  return 0;
}