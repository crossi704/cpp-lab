#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <cstring>
using namespace std;

int find_highest_number(int n) {
    char buffer[n+1];
    // cout << "\nN " << n;
    memset(buffer, '5' , n);
    buffer[n+1] = '\0';
    // cout << "\nBuffer " << buffer;
    int tmp = atoi(buffer);
    string s;
    int div_by_three;
    int div_by_five;
    // cout << " tmp = " << tmp << endl; 
    for(size_t i = tmp; i >= 555; i--) {
        s = to_string(i);
        div_by_three = count(s.begin(), s.end(), '3');
        div_by_five = count(s.begin(), s.end(), '5');

        if(s.size() == div_by_three + div_by_five) {
            if(div_by_three == 0 || div_by_three % 5 == 0) {
                if (div_by_five == 0 || div_by_five % 3 == 0) {
                    tmp = i;
                    // cout << endl << "I = " << i << endl;
                    // cout << "3s = " << div_by_three << endl;
                    // cout << "5s = " << div_by_five << endl;
                    break;   
                }
            }
        }
    }

    return tmp;
}

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        
        if(n < 3){
            cout << -1 << endl;
        } else {
            int div = find_highest_number(n);
            cout << div << endl;
        }
    }
    return 0;
}