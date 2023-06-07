#include <iostream>
#include <stdio.h>
using namespace std;
int arr[10], t, n, temp;

int main(){
  cin >> t;
  while(t--){
    cin >> n;
    int res = 0;
    for(int i = 0; i <n; i++){
      cin >> temp;
      res += temp;
    }
    cout << res << endl;
  }
  
  return 0;
}