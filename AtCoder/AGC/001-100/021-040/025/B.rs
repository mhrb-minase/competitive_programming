macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        let mut iter = $s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
    ($($r:tt)*) => {
        let mut s = {
            use std::io::Read;
            let mut s = String::new();
            std::io::stdin().read_to_string(&mut s).unwrap();
            s
        };
        let mut iter = s.split_whitespace();
        input_inner!{iter, $($r)*}
    };
}

macro_rules! input_inner {
    ($iter:expr) => {};
    ($iter:expr, ) => {};

    ($iter:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($iter, $t);
        input_inner!{$iter $($r)*}
    };
}

macro_rules! read_value {
    ($iter:expr, ( $($t:tt),* )) => {
        ( $(read_value!($iter, $t)),* )
    };

    ($iter:expr, [ $t:tt ; $len:expr ]) => {
        (0..$len).map(|_| read_value!($iter, $t)).collect::<Vec<_>>()
    };

    ($iter:expr, chars) => {
        read_value!($iter, String).chars().collect::<Vec<char>>()
    };

    ($iter:expr, usize1) => {
        read_value!($iter, usize) - 1
    };

    ($iter:expr, $t:ty) => {
        $iter.next().unwrap().parse::<$t>().expect("Parse error")
    };
}

const MOD: i64 = 998244353;

fn modpow(mut x: i64, mut n: i64) -> i64 {
    let mut ret: i64 = 1;
    while n > 0 {
        if (n & 1) == 1 {
            ret = ret * x % MOD;
        }
        x = x * x % MOD;
        n >>= 1;
    }
    return ret;
}

fn main(){
    input!{
        N: i64,
        A: i64,
        B: i64,
        K: i64,
    }

    let mut fact = vec![];
    let mut inv = vec![];
    fact.push(1i64);
    inv.push(1i64);

    for i in 0..N {
        fact.push(fact[i as usize] * (i + 1) % MOD);
        inv.push(modpow(fact[(i + 1) as usize], MOD - 2));
    }

    let mut ans: i64 = 0;

    for a in 0..N+1 {
        if (K - a * A) % B != 0 {
            continue;
        }
        let b = (K - a * A) / B;
        if b < 0 || N < b {
            continue;
        }

        ans += fact[N as usize] % MOD * inv[a as usize] % MOD * inv[(N - a) as usize] % MOD * fact[N as usize] % MOD * inv[b as usize] % MOD * inv[(N - b) as usize] % MOD;
        ans %= MOD;
    }

    println!("{}", ans);
}