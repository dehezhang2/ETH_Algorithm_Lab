#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
#define MAX 50000
int t,n,temp,sum[MAX], cnt, res;
int main(){
  scanf("%d\n", &t);
  while(t--){
    scanf("%d\n", &n);
    memset(sum, 0, sizeof(sum));
    cnt = 0;
    for(int i = 0; i < n; i++){
      scanf("%d", sum+i);
      if(i!=0) sum[i]+=sum[i-1];
      if(sum[i]%2==0) cnt++;
    }
    res = cnt*(cnt-1)/2 + (n-cnt)*(n-cnt-1)/2 + cnt;
    printf("%d\n", res);
  }
  
  return 0;
}