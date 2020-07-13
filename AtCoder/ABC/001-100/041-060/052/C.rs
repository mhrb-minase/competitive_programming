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

const MOD: i64 = 1000000007;

fn main(){
    input!{
        N: i32,
    }

    let mut f: Vec<i64> = Vec::new();

    for i in 0..N+1 {
        f.push(0);
    }

    for i in 1..N+1 {
        let mut t: i32 = i;
        let mut j: i32 = 2;
        while j * j <= t {
            while t % j == 0 {
                f[j as usize] += 1;
                t /= j;
            }
            j += 1;
        }
        if t > 1 {
            f[t as usize] += 1;
        }
    }

    let mut ans: i64 = 1;
    for x in f.iter() {
        ans = ans * (x + 1) % MOD;
    }

    println!("{}", ans);
}