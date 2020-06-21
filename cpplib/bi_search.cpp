long long meguru_search(long long ok, long long ng, std::function<bool(long long)> check){
    while(1 < std::abs(ok - ng)){
        long long mid = (ok + ng) >> 1;
        if(check(mid)){
            ok = mid;
        }else{
            ng = mid;
        }
    }
    return ok;
}

long double bi_search(long double ok, long double ng, std::function<bool(long double)> check, int loop = 100){
    for(int i = 0 ; i < loop ; ++i){
        long double mid = (ok + ng) * 0.5;
        if(check(mid)){
            ok = mid;
        }else{
            ng = mid;
        }
    }
    return ok;
}

/*
verify
https://atcoder.jp/contests/abc026/submissions/14514517
https://atcoder.jp/contests/arc050/submissions/14514575
*/