#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
#define MAX 100000
#define INF 1073741824
int t, n, k, sum[MAX + 1];
int min_ans, min_i, min_j;

int binarySearch(int l, int r, int x, int n){
  if (r > l) {
    int mid = l + (r - l) / 2;
    if (sum[mid] == x)
      return mid;
    if (sum[mid] > x)
      return binarySearch(l, mid - 1, x);
    return binarySearch(mid + 1, r, x);
  }
  int result = l;
  if(l!=0) result =  abs(x-sum[l-1]) > abs(x-sum[l])?l:l-1;
  else if (l!=n-1) result =  abs(x-sum[l]) > abs(x-sum[l+1])?l+1:l;
  return result;
}


int main(){
  scanf("%d\n", &t);
  while(t--){
    min_ans = INF + 1;
    scanf("%d %d\n", &n, &k);
    sum[0] = 0;
    for (int i = 0; i < n; i++){
      scanf("%d", sum + i + 1);
      sum[i+1] += sum[i];
      // for (int j = 0; j <= i; j++){
      //   int temp_ans = abs(k - sum[i+1] + sum[j]);
      //   if(temp_ans < min_ans) {
      //     min_ans = temp_ans;
      //     min_i = i;
      //     min_j = j;
      //   }
      // }
      int temp_j = binarySearch(0, i, sum[i+1] - k);
      int temp_ans = abs(k - sum[i+1] + sum[temp_j]);
      if(temp_ans < min_ans) {
        min_ans = temp_ans;
        min_i = i;
        min_j = temp_j;
      }
      
    }
    printf("%d %d\n", min_j, min_i);
  }
  return 0;
}