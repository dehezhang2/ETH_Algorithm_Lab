#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAX 1000001
int t, n, loc[MAX];
vector<int> res;
int head, tail, max_cnt, min_dist;

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n;
        for(int i = 0; i < n; i++) cin >> loc[i];
        sort(loc, loc+n);
        head = tail = 0;
        max_cnt = -1;
        res.clear();
        min_dist = 200;
        while(head < n && tail < n){

            int cnt = tail - head + 1, pos = (loc[tail] + loc[head])/2, diff = loc[tail] - loc[head];
            int dist = diff%2 ? diff/2 + 1 : diff/2;

            if(cnt > max_cnt || (cnt == max_cnt && dist <= min_dist)){
                
                if(cnt > max_cnt||dist<min_dist) {
                    res.clear();
                    min_dist = dist;
                }
                
                max_cnt = cnt; 
                res.push_back(pos);
                if(diff%2) res.push_back(pos + 1);
            }
            if(loc[tail+1] - loc[head]<=200 && tail < n - 1 ) tail++;
            else head++;
        }
        cout << max_cnt << " " << min_dist << endl;
        for(int i = 0; i < res.size(); i++){
            if(i) cout <<" ";
            cout << res[i];
        }
        cout << endl;
    }

    return 0;
}