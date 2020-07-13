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

fn main(){
    input!{
        N: i32,
        K: i32,
        X: [i32; N],
    }

    let mut rev = vec![];

    for i in 0..N {
        rev.push(0i32);
    }

    for i in 0..N {
        rev[(X[i as usize] - 1) as usize] = i;
    }

    let mut que = std::collections::BinaryHeap::new();

    for i in 0..K {
        que.push(X[i as usize] - 1);
    }

    for i in K..N {
        println!("{}", rev[*que.peek().unwrap() as usize] + 1);
        que.push(X[i as usize] - 1);
        que.pop();
    }

    println!("{}", rev[*que.peek().unwrap() as usize] + 1);
}