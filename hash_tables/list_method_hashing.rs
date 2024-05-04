use std::io;

// ХЕШМАП С МЕТОДОМ СПИСКОВ

const SIZE: usize = 100013;

fn hash_f(mut a: i64) -> i64 {
    a = a % (1 << 31);
    let m = 2654435769i64 * (a * a - a) ^ 314299671481i64 / 4294967296i64;
    if m > 0 { m } else { -m }
}


#[derive(Debug)]
#[derive(Clone)]
struct HashMap {
    table_size: usize,
    table: Vec<Vec<(i64, i64)>>
}

impl HashMap {
    pub fn new(table_size: usize) -> Self {
        let mut s = Self { table_size, table: Vec::<Vec<(i64, i64)>>::new()};
        s.table.resize(table_size as usize, Vec::<(i64, i64)>::new());
        s
    }

    pub fn insert(&mut self, key: i64, value: i64) {
        let hash = hash_f(key) % (self.table_size as i64);

        for i in self.table[hash as usize].iter_mut() {
            if i.0 == key {
                i.1 = value;
                return;
            }
        }
        self.table[hash as usize].push((key, value));
    }

    pub fn remove(&mut self, key: i64) {
        let hash = hash_f(key) % (self.table_size as i64);

        let line = &mut self.table[hash as usize];

        for i in 0usize..line.len() {
            if line[i].0 == key {
                line.swap_remove(i);
                return;
            }
        }
    }

    pub fn find(&mut self, key: i64) -> Option<(i64, i64)> {
        let hash = hash_f(key) % (self.table_size as i64);

        let line = &mut self.table[hash as usize];

        for i in 0usize..line.len() {
            if line[i].0 == key {
                return Some(line[i].clone());
            }
        }
        return None;
    }

    pub fn contains(&mut self, key: i64) -> bool {
        match self.find(key) {
            None => false,
            Some(_) => true
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
                    let Some((_, value)) = hashmap.find(key) else { continue; };
                    println!("{}", value);
                } else {
                    println!("none");
                }
            }
            _ => {}
        }
    }
}






