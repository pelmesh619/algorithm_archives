use std::io;
use std::cmp::min;

// АЛГОРИТМ МАНАКЕРА

/**
В первой строке вводится строка

Выводится количество непустых подстрок, которые являются палиндромами
*/

fn get_string() -> String {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();

    string.trim().to_string()
}

fn calculate_odd(s: &Vec<u8>) -> Vec<i32> {
    let mut result = Vec::<i32>::new();
    result.resize(s.len(), 0);
    let n = s.len() as i32;
    let mut l = 0i32;
    let mut r = -1i32;
    for i in 1..(s.len() as i32) {
        let mut k = 0;
        if i <= r {
            k = min(r - i, result[(r - i + l) as usize]);
        }
        while i + k + 1 < n && i - k - 1 >= 0 && s[(i + k + 1) as usize] == s[(i - k - 1) as usize] {
            k += 1;
        }
        result[i as usize] = k;
        if i + k > r {
            l = i - k;
            r = i + k;
        }

    }
    return result;
}

fn calculate_even(s: &Vec<u8>) -> Vec<i32> {
    let mut result = Vec::<i32>::new();
    result.resize(s.len(), 0);
    let n = s.len() as i32;
    let mut l = 0i32;
    let mut r = -1i32;
    for i in 1..(s.len() as i32) {
        let mut k = 0i32;
        if i <= r {
            k = min(r - i + 1, result[(r - i + l + 1) as usize]);
        }
        while i + k < n && i - k - 1 >= 0 && s[(i + k) as usize] == s[(i - k - 1) as usize] {
            k += 1;
        }
        result[i as usize] = k;
        if i + k - 1 > r {
            l = i - k;
            r = i + k - 1;
        }

    }
    return result;
}

fn main() {
    let s = get_string().as_bytes().to_vec();

    let odd = calculate_odd(&s);
    let even = calculate_even(&s);

    let mut counter = 0;

    for i in &odd {
        counter += *i;
    }
    for i in &even {
        counter += *i;
    }

    println!("{}", counter + (s.len() as i32));

}

