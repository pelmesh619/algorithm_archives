use std::io;

// ХЕШМАП С ОТКРЫТОЙ АДРЕСАЦИЕЙ

const SIZE: usize = 100013;

fn hash1(a: i64, m: usize) -> i64 {
    (a * 455033 + 1831) % m as i64
}

#[derive(Debug)]
#[derive(Clone)]
enum MyOption<T> {
    Some(T),
    Deleted,
    None,
}

#[derive(Debug)]
#[derive(Clone)]
struct HashMap {
    table_size: usize,
    table: Vec<MyOption<(i64, i64)>>,
    size: usize
}

impl HashMap {
    pub fn new(table_size: usize) -> Self {
        let mut s = Self { table_size, table: Vec::<MyOption<(i64, i64)>>::new(), size: 0usize };
        s.table.resize(table_size as usize, MyOption::None);
        s
    }

    pub fn insert(&mut self, key: i64, value: i64) {
        let mut hash_1 = hash1(key, self.table_size) as usize;

        loop {
            match &self.table[hash_1] {
                MyOption::None | MyOption::Deleted => {
                    self.table[hash_1] = MyOption::Some((key, value));
                    self.size += 1;
                    return;
                }
                MyOption::Some((k, _)) => {
                    if *k == key {
                        self.table[hash_1] = MyOption::Some((key, value));
                        return;
                    }
                    hash_1 = (hash_1 + 1) % self.table_size;
                }
            }
        }
    }

    pub fn find(&mut self, key: i64) -> MyOption<(i64, i64)> {
        let mut hash_1 = hash1(key, self.table_size) as usize;

        loop {
            match &self.table[hash_1] {
                MyOption::None => {
                    return MyOption::None
                }
                MyOption::Deleted => {
                    hash_1 = (hash_1 + 1) % self.table_size;
                }
                MyOption::Some((k, _)) => {
                    if *k == key {
                        return self.table[hash_1].clone()
                    }
                    hash_1 = (hash_1 + 1) % self.table_size;
                }
            }
        }
    }

    pub fn contains(&mut self, key: i64) -> bool {
        match self.find(key) {
            MyOption::Deleted | MyOption::None => false,
            MyOption::Some(_) => true
        }
    }

    pub fn remove(&mut self, key: i64) {
        let mut hash_1 = hash1(key, self.table_size) as usize;

        loop {
            match &self.table[hash_1] {
                MyOption::None => {
                    return
                }
                MyOption::Deleted => {
                    hash_1 = (hash_1 + 1) % self.table_size;
                }
                MyOption::Some((k, _)) => {
                    if *k == key {
                        self.table[hash_1] = MyOption::Deleted;
                    }
                    hash_1 = (hash_1 + 1) % self.table_size;
                }
            }
        }
    }

}

fn get_number() -> i64 {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();
    string.trim().parse().unwrap_or(0)
}

fn get_operation() -> Vec<String> {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();

    let result = string
        .split(" ")
        .filter(|a: &&str| -> bool { a.len() > 0 })
        .map(|a: &str| -> String { a.trim().to_string() })
        .collect::<Vec<_>>().to_vec();

    result
}


/**
В первой строке ввода число запросов n, в следующих n строках запросы вида (k - число <= 1e9, v - число <= 1e9):

+ k x - вставка в хешмап элемента x с ключом k (или заменить его на x)
- k - удаление из хешмапа ключа k
? k - проверка на наличие ключа k (значение, если ключ в хешмапе, иначе none)
 */


fn main() {
    let q = get_number();

    let mut hashmap = HashMap::new(SIZE);

    for _ in 0..q {
        let operation = get_operation();
        match operation[0].as_str() {
            "+" => {
                let (key, value) =
                    (operation[1].parse::<i64>().expect("Not a number!"),
                     operation[2].parse::<i64>().expect("Not a number!"));

                hashmap.insert(key, value);
            }
            "-" => {
                let key = operation[1].parse::<i64>().expect("Not a number!");
                hashmap.remove(key);
            }
            "?" => {
                let key = operation[1].parse::<i64>().expect("Not a number!");
                if hashmap.contains(key) {
                    let MyOption::Some((_, value)) = hashmap.find(key) else { continue; };
                    println!("{}", value);
                } else {
                    println!("none");
                }
            }
            _ => {}
        }
    }
}




