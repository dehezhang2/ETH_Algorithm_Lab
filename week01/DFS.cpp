#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX 1000
int t, n, m, v, stamp;

struct Node{
    int val;
    vector<int> next;
};

Node map[MAX];
int rec1[MAX], rec2[MAX];
void dfs(int s){
    if(rec1[s] != -1)return;
    rec1[s] = stamp;
    stamp++;
    for(int i=0;i<map[s].next.size();i++){
        int tar = (map[s].next)[i];
        if(rec1[tar] == -1) dfs(tar);
    }
    rec2[s] = stamp;
    stamp++;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin >> t;
  while(t--){
    cin >> n >> m >> v;
    
    stamp = 0;
    
    memset(map, 0, sizeof(map));
    memset(rec1, -1, sizeof(rec1));
    memset(rec2, -1, sizeof(rec2));
    
    for (int i = 0; i < m; i++){
      int a, b; cin >> a >> b;
      map[a].next.push_back(b);
      map[b].next.push_back(a);
    }
    dfs(v);
    for (int i=0;i < n;i++){
      if(i) cout << " ";
      cout << rec1[i];
    }
    cout << endl;
    for (int i=0;i < n;i++){
      if(i) cout << " ";
      cout << rec2[i];
    }
    cout << endl;
  }

  return 0;
}