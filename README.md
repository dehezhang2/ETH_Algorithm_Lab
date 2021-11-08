# ETH_Algorithm_Lab

Code and assessment of Algorithm Labs

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



## Assessment 2: Lannister

### Problem Definition

* **Input**: 
  * $n$ noble houses
  * $m$ common houses
  * Two canals (one for sewage one for fresh water) cross at right angles
  * sewage pipe: horizontal, fresh water pipe: vertical
  * Constraints
    * Cersei: noble houses at the LHS of the sewage cannal, common houses at the RHS of the sewage cannal.
    * Tywin: sum of sewage pipe length should be less than a threshold $s$.
    * Jaime: minimize the length of the longest fresh water pipe.
* **Output**: 
  * check the feasibility of Cersei’s and Tywin’s constraints
  * minimum length of the longest fresh water pipe

### Mathematical Concept

* Assume the sewage canal is $ax+by+c=0$, then the fresh canal can be represented as $bx-ay+d=0$, which is perpendicular to the sewage canal. $(x_i,y_i)$ is the position of house $i$. 

* Cersei’s constraint:
  $$
  \Bigg\{ \begin{align*}
    ax_i+by_i+c\leq\ 0\ &(i\ \in noble)\\
    ax_i+by_i+c\geq\ 0\ & (i\ \in common)\\
  \end{align*}\ , \ a>0\ (enforce\ the\ LHS\ RHS\ order)
  $$

* Tywin’s constraint:
  $$
  dist_{sewages}=\sum_{i\in\ houses}|x_i-(-{b\over a}y_i-{c\over a})| = \sum_{i\in\ houses}|x_i+{b\over a}y_i+{c\over a}| \\
  \leq s
  $$

* Jaime’s constraint: if we set the upperbound of lengths of fresh water pipes to be $l$
  $$
  dist_{fresh}(i) = |y_i-({b\over a}x_i + {d\over a})|\leq\ l \\
  minmize\ l
  $$

## Algorithm

* Linear programming: we can transform the constraints into a linear programming problem format.

  * object function: $l$ 
  * Variables: $a$, $b$, $c$, $d$ , $l$ 

* Transformed constraints

  * Cersei’s constraint
    $$
    \Bigg\{ \begin{align*}
      x_ia+y_ib+c\leq\ 0\ &(i\ \in noble)\\
      (-x_i)a+(-y_i)b+(-1)c\leq\ 0\ & (i\ \in common)\\
    \end{align*}\\
    \ a>0\ (enforce\ the\ LHS\ RHS\ order)
    $$

  * Tywin’s constraint:
    $$
    dist_{sewages}=\sum_{i\in\ houses}|x_i+{b\over a}y_i+{c\over a}| \\
    =\sum_{i\in\ noble\ houses}-(x_i+{b\over a}y_i+{c\over a})\  +  \sum_{i\in\ common\ houses}(x_i+{b\over a}y_i+{c\over a})\\
    =(\sum_{i\in\ common}x_i-\sum_{i\in\ noble}x_i) + {b\over a}((\sum_{i\in\ common}y_i-\sum_{i\in\ noble}y_i))+{c\over a}(m-n)
    \leq s \\
    a(\sum_{i\in\ common}x_i-\sum_{i\in\ noble}x_i-s) + b((\sum_{i\in\ common}y_i-\sum_{i\in\ noble}y_i))+c(m-n) \leq 0 \\
    $$

  * Jaime’s constraint: 
    $$
    dist_{fresh}(i) = |y_i-({b\over a}x_i + {d\over a})|\leq\ l \\
    
      max[ ({b\over a}x_i + {d\over a}) - y_i,\ y_i-({b\over a}x_i + {d\over a})]\leq l \\
      ({b\over a}x_i + {d\over a}) - y_i\leq l\ \and y_i-({b\over a}x_i + {d\over a}) \leq l \\
      minmize\ l
    $$

    * just add two constraint to fulfill this constraint.



## Implementation & Testing

* Set $a=1 > 0$

  ```c++
  lp.set_l(a, true, 1); lp.set_u(a, true, 1);
  ```

  * Tywin’s constraint:
    $$
    dist_{sewages}
    =(\sum_{i\in\ common}x_i-\sum_{i\in\ noble}x_i) + b((\sum_{i\in\ common}y_i-\sum_{i\in\ noble}y_i))+c(m-n)
    \leq s \\
    b((\sum_{i\in\ common}y_i-\sum_{i\in\ noble}y_i))+c(m-n)\leq s-(\sum_{i\in\ common}x_i-\sum_{i\in\ noble}x_i)
    $$

  * Jaime’s constraint: 
    $$
    (bx_i + d) - y_i\leq l\ \and y_i-(bx_i + d) \leq l\\
    (bx_i + d) - l\leq y_i\ \and -(bx_i + d)-l \leq -y_i
    $$

* Code

  * implement first two constraints then add Jaime’s constraint
  * Use of counter to count row in matrix $A$
  * use `long` instead of `int`

```c++
///3
#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int t, n, m;
long s;


void solve(){
    cin >> n >> m >> s;
    vector< pair<long, long> > nobles(n);
    vector< pair<long, long> > commons(m);

    int number_of_constraints = 0;
    long noble_sum_x = 0, noble_sum_y = 0;
    Program lp (CGAL::SMALLER, false, 0, false, 0);
    const int a = 0, b= 1, c = 2, d = 3, l = 4;
    for(int i = 0; i < n; i++){
        cin >> nobles[i].first >> nobles[i].second;
        noble_sum_x += nobles[i].first;
        noble_sum_y += nobles[i].second;
        lp.set_a(a, number_of_constraints, nobles[i].first);
        lp.set_a(b, number_of_constraints, nobles[i].second);
        lp.set_a(c, number_of_constraints, 1);
        number_of_constraints++;
    }
    long common_sum_x = 0, common_sum_y = 0;
    for(int i = 0; i < m; i++){
        cin >> commons[i].first >> commons[i].second;
        common_sum_x += commons[i].first;
        common_sum_y += commons[i].second;
        lp.set_a(a, number_of_constraints, -commons[i].first);
        lp.set_a(b, number_of_constraints, -commons[i].second);
        lp.set_a(c, number_of_constraints, -1);
        number_of_constraints++;
    }
    // set a = 1 to simplify the second constraint
    lp.set_l(a, true, 1); lp.set_u(a, true, 1);
    Solution sol = CGAL::solve_linear_program(lp, ET());
    if(sol.is_infeasible()) {cout << "Yuck!\n"; return;}

    if(s != -1){
        lp.set_a(b, number_of_constraints, common_sum_y - noble_sum_y);
        lp.set_a(c, number_of_constraints, m - n);
        lp.set_b(number_of_constraints, s - common_sum_x + noble_sum_x);
        number_of_constraints++;
        sol = CGAL::solve_linear_program(lp, ET());
        if(sol.is_infeasible()) {cout << "Bankrupt!\n"; return ;}
    }

    for(int i = 0; i < n; i++){
        lp.set_a(b, number_of_constraints, -nobles[i].first);
        lp.set_a(d, number_of_constraints, -1);
        lp.set_a(l, number_of_constraints, -1);
        lp.set_b(number_of_constraints, -nobles[i].second);
        number_of_constraints++;

        lp.set_a(b, number_of_constraints, nobles[i].first);
        lp.set_a(d, number_of_constraints, 1);
        lp.set_a(l, number_of_constraints, -1);
        lp.set_b(number_of_constraints, nobles[i].second);
        number_of_constraints++;
    }

    for(int i = 0; i < m; i++){
        lp.set_a(b, number_of_constraints, -commons[i].first);
        lp.set_a(d, number_of_constraints, -1);
        lp.set_a(l, number_of_constraints, -1);
        lp.set_b(number_of_constraints, -commons[i].second);
        number_of_constraints++;

        lp.set_a(b, number_of_constraints, commons[i].first);
        lp.set_a(d, number_of_constraints, 1);
        lp.set_a(l, number_of_constraints, -1);
        lp.set_b(number_of_constraints, commons[i].second);
        number_of_constraints++;
    }
    lp.set_l(l, true, 0);
    lp.set_c(l, 1);

    sol = CGAL::solve_linear_program(lp, ET());
    cout << fixed << setprecision(0) << ceil(CGAL::to_double(sol.objective_value())) << endl;
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
```

### Overall

* Understand the question: too long…
* Set up the constraints in linear programming format (need trick for all the constraints)
  * Cersei: linearly separable **but should be on the same side**
  * Tywin : **need to deal with the absolute sign properly.** (by dividing into two cases)
  * Jamie: 
    *  **need to deal with the absolute sign properly** (by adding two constraints)
    * **need to find special value for a** (otherwise becomes quadratic problem)
* Debug: use `long` instead of `int`
