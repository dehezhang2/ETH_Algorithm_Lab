#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <climits>
#include <algorithm>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Line_2 L;

void runTest(){
    int m,n;
    cin >> m >> n;

    vector<P> hiking_points;
    for (int i =0; i<m;i++){
        int x,y; cin>>x>>y;
        hiking_points.push_back(P(x,y));
    } 

    vector<vector<bool>> maps_points(n,vector<bool>(m,false));
    for(int i =0; i<n;i++){
        int x11,y11,x12,y12,x21,y21,x22,y22,x31,y31,x32,y32;
        cin >>x11>>y11>>x12>>y12
            >>x21>>y21>>x22>>y22
            >>x31>>y31>>x32>>y32;
        P p11(x11,y11),p12(x12,y12),
          p21(x21,y21),p22(x22,y22),
          p31(x31,y31),p32(x32,y32); //ideally clockwise

        if (!CGAL::right_turn(p11,p12,p21)) swap(p11,p12);
        if (!CGAL::right_turn(p21,p22,p31)) swap(p21,p22);
        if (!CGAL::right_turn(p31,p32,p11)) swap(p31,p32);

        for (int j=0;j<m;j++){
            bool b1,b2,b3;
            b1 = CGAL::right_turn(p11,p12,hiking_points[j])||CGAL::collinear(p11,p12,hiking_points[j]);
            b2 = CGAL::right_turn(p21,p22,hiking_points[j])||CGAL::collinear(p21,p22,hiking_points[j]);
            b3 = CGAL::right_turn(p31,p32,hiking_points[j])||CGAL::collinear(p31,p32,hiking_points[j]);
            maps_points[i][j] = b1&&b2&&b3;
        }
    }

    vector<vector<int>> maps_legs(n,vector<int>());
    for (int i =0; i<n;i++){
        for(int j=0;j<m-1;j++){
            if(maps_points[i][j]&&maps_points[i][j+1])
                maps_legs[i].push_back(j);
        }
    }
    // maps_legs[i]: list of legs contained by triangle i
    int l = 0, r = 0;
    int count =0;
    int res = n+2;
    // how many time the leg is contained in current interval
    vector<int> legs_count(m-1,0);

    for(int leg:maps_legs[0]){
        count += 1;
        legs_count[leg] += 1;
    }
    if (r-l+1 < res && count==m-1){
        res = r-l+1;
    }

    while (l < n && r < n && l <= r){
        if (count < m-1){
            if (r + 1 < n){
                r++;
                for(int leg:maps_legs[r]){
                    if (legs_count[leg]==0) count ++;
                    legs_count[leg]++;
                }
            }
        }
        else if (count = m-1){
                for(int leg:maps_legs[l]){
                    legs_count[leg]--;
                    if (legs_count[leg]==0) count --;
                }
                l++;

        }

        if (r-l+1 < res && count==m-1){
            res = r-l+1;
        }
    }
    cout << res <<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    int c; cin >> c;
    for (int i =0; i<c;i++){
        runTest();
    }
}