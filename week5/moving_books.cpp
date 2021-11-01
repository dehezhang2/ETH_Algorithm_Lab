#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
#define UP_DOWN 3
#define DOWN 2
int t, n, m;


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
    sort(friends.begin(), friends.end()); 
    reverse(friends.begin(), friends.end());
    sort(books.begin(), books.end());
    reverse(books.begin(), books.end());
    if(friends[0] < books[0]){
        cout << "impossible\n";
        return;
    }
    int time = 0, book_pos = 0, friend_pos = 0, cnt = 0;
    while(cnt < m){
        if(books[book_pos] <= friends[friend_pos]){
            books.erase(books.begin() + book_pos);
            // cout <<friends[friend_pos]<<" get "<< books[book_pos] << " "<<book_pos<<" ";

            cnt++;
            if(cnt == m){
                time += DOWN;
                // cout << endl;
                break;
            }
            friend_pos++;
            if(book_pos == (int)books.size() || friend_pos == n){
                time += UP_DOWN;
                book_pos = 0;
                friend_pos = 0;
                // cout << endl;
            }
        } else {
            book_pos++;
            if(book_pos == (int)books.size() || friend_pos == n){
                time += UP_DOWN;
                book_pos=0;
                friend_pos = 0;
            }
        }

    }
    cout << time << endl;
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