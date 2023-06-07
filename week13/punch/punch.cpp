#include<vector>
#include<iostream>

using namespace std;

struct state{
    int cost;
    int count;
    bool used_ith;
};

void runTest(){
    int n,k; cin >> n >> k;
    vector<pair<int,int>> beverage(n);
    for(int i = 0; i < n; i++){
        int c,v;
        cin >> c >> v;
        beverage[i] = {v,c};
    }

    vector<vector<state>> dp(n+1,vector<state>(k+1));

    

    for(int j = 0; j < k+1; j++){
        dp[0][j] = {INT32_MAX,0,false};
    }
    for(int i = 0; i < n+1; i++){
        dp[i][0] = {0, 0, false};
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j<=k; j++){
            int price = beverage[i-1].second;
            int litre = beverage[i-1].first;
            
            int with_index = max(0,j-litre);
            int with_price = dp[i][with_index].cost + price;
            int with_count = dp[i][with_index].count + !dp[i][with_index].used_ith;

            int without_price = dp[i-1][j].cost;
            int without_count = dp[i-1][j].count;

            if(make_pair(with_price,-with_count)<make_pair(without_price,-without_count)){
                dp[i][j] = {with_price, with_count, true};
            }else{
                dp[i][j] = {without_price, without_count, false};
            }
        }
    }
    std::cout << dp[n][k].cost << " " << dp[n][k].count << std::endl;


}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--){
        runTest();
    }
}