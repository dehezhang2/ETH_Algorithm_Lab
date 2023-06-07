#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX 1000000
int t, n;
long max_p, current_p, current_height;

int main(){
  scanf("%d\n", &t);
  while(t--){
    scanf("%d\n", &n);
    current_p = max_p = 0;
    for(int i = 0; i < n; i++){
      scanf("%ld", &current_height);
      if(!(i!=0 && i >= max_p)){
        current_p = i + current_height;
        max_p = current_p > max_p ? current_p : max_p;
      }
    }
    printf("%ld\n", max_p < n ? max_p : n);
  }
  
  return 0;
}