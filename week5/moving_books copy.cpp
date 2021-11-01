#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define UP_DOWN 3
#define DOWN 2
int t, n, m;


bool can_move_all_in_round(vector<int>& friends, vector<int>& books,int rounds){
    int moved_cnt = 0;
    for(int s:friends){
        if(moved_cnt >= m) return true;
        if(s >= books[moved_cnt]) moved_cnt += rounds;      // if larger than, increase moved books by total round
        else break;
    }
    return moved_cnt >= m;
}

void solve(){
    
    cin >> n >> m;
    vector<int> friends;
    vector<int> books;
    for(int i = 0;i < n;i++){
        int s; cin >> s;
        friends.push_back(s);
    }
    for(int i = 0;i < m;i++){
        int w; cin >> w;
        books.push_back(w);
    }
    sort(friends.rbegin(), friends.rend()); 
    sort(books.rbegin(), books.rend());
    if(friends[0] < books[0]){
        cout << "impossible\n";
        return;
    }
    // we search for the number of round that can move all the books
    int l = 1, r = m;
    while(l<r){
        int mid = (l+r)/2;
        if(can_move_all_in_round(friends, books, mid)) r = mid;
        else l = mid + 1;
    }
    cout << 3*l -1 << endl;
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