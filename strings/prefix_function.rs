use std::io;

// ПРЕФИКС-ФУНКЦИЯ

/**
На ввод подается строка

Выводится массив префикс-функции
*/


fn get_string() -> String {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();

    string.trim().to_string()
}

fn main() {
    let string = get_string();
    let string = string.chars().collect::<Vec<_>>();

    let mut pref = Vec::<i32>::new();
    pref.resize(string.len(), 0);
    pref[0] = 0;

    for i in 1..string.len() {
        let mut k = pref[i - 1] as usize;
        while k > 0 && string[i] != string[k] {
            k = pref[k - 1] as usize;
        }
        if string[i] == string[k] {
            k += 1;
        }
        pref[i] = k as i32;
    }

    for i in pref {
        print!("{} ", i);
    }
}




