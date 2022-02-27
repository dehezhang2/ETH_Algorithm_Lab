#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n,m,H;
long a,b,P,W;

long dp(int i, int j, int k, vector<vector<vector<long>>>& mem, vector<pair<long,int>>& potion_a){
    
    if(j==0){
        if(k==0) return 0;  
        else return -1; // quota used but still have h => not feasible
    }
    if(i<0) return -1;  
    if (k > H) return -1;

    if(mem[i][j][k]!=-2){
        return mem[i][j][k];
    }

    long p = potion_a[i].first;
    int h = potion_a[i].second;
    
    // use i: consider first i-1 with only j-1 quota to achieve k-h
    long use_i = dp(i-1,j-1,max(0,k-h),mem,potion_a);
    // not use i: consider first i-1 with only j quota to achieve k
    long not_use_i = dp(i-1,j,k,mem,potion_a);

    if(use_i!=-1){
        use_i+=p;
    }
    mem[i][j][k] = max(use_i,not_use_i);
    return mem[i][j][k];
}

void runTest(){
    cin >>n>>m>>a>>b>>P>>H>>W;
    vector<pair<long,int>> potion_a; //[P,H]
    for(int i = 0; i< n; i++){
        long p; int h;
        cin >> p >> h;
        potion_a.push_back({p,h});
    }
    vector<long> potion_b(m); //[W]
    for(int i = 0; i< m; i++){
        cin >>potion_b[i];
    }
    sort(potion_b.rbegin(),potion_b.rend());

    vector<vector<vector<long>>> mem(n,vector<vector<long>>(n+1,vector<long>(H+1,-2)));
    vector<long> max_power(n+1);
    for(int i = 0; i<=n; i++){
        max_power[i] = dp(n-1,i,H,mem,potion_a);    //max power with number of i bottles of A that is legal
    }

    int result = INT32_MAX;

    for(int i = 0; i<=n; i++){
        int num_a = i;
        long p = max_power[i];
        if(p==-1){continue;}
        long w = -num_a*a;
        for(int j =0; j<m;j++){
            int num_b = j+1;
            w += potion_b[j];
            p -= b;
            if(p<P){
                break;
            }
            if(w >= W){
                result = min(num_a+num_b, result);
            }
        }
    }
    if(result == INT32_MAX){
        cout << -1 << endl;
    }else{
        cout << result << endl;
    }

}

int main(){
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t-- ){
        runTest();
    }
}
