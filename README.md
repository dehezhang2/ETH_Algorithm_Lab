# ETH_Algorithm_Lab

Code of Algorithm Labs

## Assessment 1: From Russia with Love

### Problem Definition

* **Input**: 
  * $n$: number of coins
  * $m$: number of players
  * $k$: the player you are intereseted in
  * values $x_0, ...,x_{n-1}$ s.t. $x_i$ denotes the price of $i$-th coin
* **Rule**: $m$ players take turns from player $0$, pick up a coin from either the front or the end of the array of coins.  
* **Output**: Largest winnings that player $k$ can collect, **regardless of how other players play**. (even all other players play against player $k$, the maximum value $k$ can get)

### Mathematical Concept

* **Recursion**: The problem can be transformed recursively into subproblems. 

* **Reformulation**: This problem is similar to a zero-sum game, the difference is that there are more than two players, and all other players play against player $k$. We define the score that player $k$ can get when it is player $p$‘s turn and the remaining coins are from $l$ to $r$. 
  $$
  f(l,r,p) = 
  \begin{equation}  
  \left\{  
               \begin{array}{**lr**}
               x_l, & l=r \and p=k
               \\
               \\
               0, & l=r \and p \neq k
               \\
               \\
               max[x_l + f(l+1,r,(p+1)\ mod\ m),\ x_r + f(l,r-1,(p+1)\ mod\ m)], & l\neq r \and p=k\\  
               \\
               min[f(l+1,r,(p+1)\ mod\ m),\ f(l,r-1,(p+1)\ mod\ m)], & otherwise \\  
               
               \end{array}  
  \right.  
  \end{equation}
  $$
  

### Algorithm

* **Recursion**: Just from the mathematical formulation

  * Running time: $O(2^n)$ (For each decision, there are two possibilities)

  ```c++
  int score(int head, int tail, int player){
      if(head==tail) return (player!=k?0:coins[head]);
      int score1 = (player!=k?0:coins[head]) + score(head+1, tail, (player+1)%m);
      int score2 = (player!=k?0:coins[tail]) + score(head, tail-1, (player+1)%m);
      return (player==k ? max(score1, x):min(score1, score2));
  }
  ```

* **Dynamic Programming (Top-Down)**

  * Since the player is fixed for a specific array, we only need to record the state as `dp[head][tail]`.
  * Running time: $O(n^2)$ (For each `dp[head][tail]`, we only need to compute once. $\binom n2 $ in total.)

  ```c++
  int score(int head, int tail, int player){
      if(dp[head][tail]!=-1) return dp[head][tail];
      if(head==tail) return (dp[head][tail] = (player!=k?0:coins[head]));
      int score1 = (player!=k?0:coins[head]) + score(head+1, tail, (player+1)%m);
      int score2 = (player!=k?0:coins[tail]) + score(head, tail-1, (player+1)%m);
      return (dp[head][tail] = (player==k ? max(score1, x):min(score1, score2)));
  }
  ```

### Implementation & Testing

```c++
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX_C 1001
#define MAX_P 501
int t, n, m, k, coins[MAX_C], dp[MAX_C][MAX_C];

int score(int head, int tail, int player){
    if(dp[head][tail]!=-1) return dp[head][tail];
    if(head==tail) return (dp[head][tail] = 0);
    int score1 = (player!=k?0:coins[head]) + score(head+1, tail, (player+1)%m);
    int score2 = (player!=k?0:coins[tail]) + score(head, tail-1, (player+1)%m);
    return (dp[head][tail] = (player==k ? max(score1, score2):min(score1, score2)));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> m >> k;
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < n; i++) cin >> coins[i];
        cout << score(0,n-1,0) <<endl;
    }
    return 0;
}
```

* When $m=2$, it is equaivalent to a zero-sum game. Use min-max algorithm. 

```c++
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX_C 1001
#define MAX_P 501
int t, n, m, k, coins[MAX_C], sum[MAX_C], dp[MAX_C][MAX_C];

int score(int head, int tail, int player){
    if(dp[head][tail]!=-1) return dp[head][tail];
    if(head==tail) return (dp[head][tail] = 0);
    int score1 = (player!=k?0:coins[head]) + score(head+1, tail, (player+1)%m);
    int score2 = (player!=k?0:coins[tail]) + score(head, tail-1, (player+1)%m);
    return (dp[head][tail] = (player==k ? max(score1, score2):min(score1, score2)));
}

int score2(int head, int tail){
    if(dp[head][tail]!=-1) return dp[head][tail];
    if(head==tail) return (dp[head][tail] = 0);
    int scorea = coins[head] + score2(head+1, tail);
    int scoreb = coins[tail] + score2(head, tail-1);
    int total = sum[tail + 1] - sum[head];
    return (dp[head][tail] = total - max(scorea, scoreb));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> m >> k;
        memset(sum, 0, sizeof(sum));
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < n; i++){
            cin >> coins[i];
            sum[i+1] = sum[i] + coins[i];
        }
        cout << ((m==2)?score2(0, n-1):score(0,n-1,0)) <<endl;
    }
    return 0;
}
```

```c++
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
#define MAX_C 1001
#define MAX_P 501
int t, n, m, k, coins[MAX_C], dp[MAX_C][MAX_C];

int score(int head, int tail, int player){
    if(dp[head][tail]!=-1) return dp[head][tail];
    if(head==tail) return (dp[head][tail] = (player!=k?0:coins[head]));
    int score1 = (player!=k?0:coins[head]) + score(head+1, tail, (player+1)%m);
    int score2 = (player!=k?0:coins[tail]) + score(head, tail-1, (player+1)%m);
    return (dp[head][tail] = (player==k ? max(score1, score2):min(score1, score2)));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    while(t--){
        cin >> n >> m >> k;
        memset(dp, -1, sizeof(dp));
        for(int i = 0; i < n; i++) cin >> coins[i];
        cout << score(0,n-1,0) <<endl;
    }
    return 0;
}
```

### Overall

* Understand the question: I firstly understand this problem in a different way. (I thought it asks me to find the maximum score that player k can get, which means all the other players are helping him!)

* Find a bug when $m=2$. 

