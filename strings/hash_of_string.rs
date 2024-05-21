use std::io;

// СРАВНЕНИЕ ПОДСТРОК С ПОМОЩЬЮ ХЕШЕЙ

/**
В первой строке ввода два числа n, q - длина строки и число запросов

В следующих q строках запросы вида `a b l`, где a - начало первой подстроки, b - начало второй, l - длина обеих подстрок

Выводится YES, если они равны, иначе NO
*/


fn get_numbers() -> Vec<i64> {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();

    let result = string
        .split(" ")
        .filter(|a: &&str| -> bool { a.len() > 0 })
        .map(|a: &str| -> i64 { a.trim().parse().unwrap_or(0) })
        .collect::<Vec<_>>().to_vec();

    return result;
}

fn get_string() -> String {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();

    string.trim().to_string()
}

// probably it is better to change it for some bigger number
const M: i64 = 7;

fn main() {
    let out = get_numbers();
    let (_n, q) = (out[0], out[1]);
    let first_word = get_string().chars().collect::<Vec<_>>();

    let mut hash_array = Vec::<i64>::new();
    hash_array.push(0i64);

    for i in 0..first_word.len() {
        hash_array.push(hash_array[i] + (first_word[i] as i64) * M.pow(i as u32));
    }

    for _ in 0..q {
        let out = get_numbers();
        let (mut a, mut b, len) = (out[0] as usize, out[1] as usize, out[2] as usize);
        a -= 1; b -= 1;

        let mut first_hash = hash_array[a + len] - hash_array[a];
        let mut second_hash = hash_array[b + len] - hash_array[b];

        if a < b {
            first_hash *= M.pow((b - a) as u32);
        } else {
            second_hash *= M.pow((a - b) as u32);
        }

        if first_hash == second_hash {
            // additional checking
            // if first_word[a..a + len] == first_word[b..b + len] {
            //     println!("NO");
            //     continue;
            // }
            println!("YES");
        } else {
            println!("NO");
        }
    }
}

