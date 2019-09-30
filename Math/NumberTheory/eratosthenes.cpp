#include<vector>
#include<algorithm>

std::vector<int> primeNumbers = {2, 3};
std::vector<bool> isPrime;

void eratosthenes(int n){
    int i, j;
    int s = 4;

    isPrime.assign(std::max(n + 1, 2), true);
    isPrime[0] = false;
    isPrime[1] = false;

    for(i = 4 ; i <= n ; i += 2){
        isPrime[i] = false;
    }
    for(i = 9 ; i <= n ; i += 6){
        isPrime[i] = false;
    }

    for(i = 5 ; i * i <= n ; i += s){
        if(isPrime[i]){
            primeNumbers.emplace_back(i);
            for(j = i * i ; j <= n ; j += i){
                isPrime[j] = false;
            }
        }
        s ^= 6;
    }
    for( ; i <= n ; i += s){
        if(isPrime[i]){
            primeNumbers.emplace_back(i);
        }
        s ^= 6;
    }

    return;
}

/*

verify:https://onlinejudge.u-aizu.ac.jp/status/users/mhrb_minase/submissions/1/0009/judge/3900738/C++14
       https://atcoder.jp/contests/abc084/submissions/7799433

*/
