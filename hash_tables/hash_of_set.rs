use std::io;

// ХЕШ МНОЖЕСТВА

fn get_number() -> i64 {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();
    string.trim().parse().unwrap_or(0)
}

fn hash_f(x: i64) -> i64 { (x * x - x) ^ 45205493372688877i64 }

/**
В первой строке ввода число n - размер множества
В следующих n строках ввода - элементы первого множества
В следующих n строках ввода - элементы второго множества

Выводит YES, если множества равны, иначе NO
*/

fn main() {
    let mut h1 = 0i64;
    let mut h2 = 0i64;

    let size = get_number();

    for _ in 0..size {
        h1 = (h1 + hash_f(get_number())) % 314299671481i64;
    }
    for _ in 0..size {
        h2 = (h2 + hash_f(get_number())) % 314299671481i64;
    }

    println!("{}", if h1 == h2 { "YES" } else { "NO" });
}

