use std::io;

// ХЕШМАП С МЕТОДОМ КУКУШКИ

const SIZE: usize = 100013;

fn hash1(a: &String, m: usize) -> i64 {
    let mut h = 0i64;
    for i in a.chars() {
        h = ((h % (1i64 << 60)) * 3543523 + (i as i64)) % (m as i64);
    }
    h
}
fn hash2(a: &String, m: usize) -> i64 {
    let mut h = 0i64;
    for i in a.chars().rev() {
        h = ((h % (1i64 << 60)) * 16823 + (i as i64)) % (m as i64);
    }
    h
}


#[derive(Debug)]
#[derive(Clone)]
struct HashMap {
    table_size: usize,
    table: Vec<Option<(String, i64)>>,
}

impl HashMap {
    pub fn new(table_size: usize) -> Self {
        let mut s = Self { table_size, table: Vec::<Option<(String, i64)>>::new() };
        s.table.resize(table_size as usize, None);
        s
    }

    pub fn _insert(&mut self, key: &String, value: i64, mut start_hash: i64, prev_hash: i64) {
        let hash_1 = hash1(&key, self.table_size) as usize;
        let hash_2 = hash2(&key, self.table_size) as usize;

        match &mut self.table[hash_1] {
            None => {
                self.table[hash_1] = Some((key.to_string(), value));
                return;
            }
            Some((k, v)) => {
                if *key == *k {
                    *v = value;
                    return;
                }
                match &mut self.table[hash_2] {
                    None => {
                        self.table[hash_2] = Some((key.to_string(), value));
                        return;
                    }
                    Some((k, v)) => {
                        if *key == *k {
                            *v = value;
                            return;
                        }

                        let new_hash = if hash_1 == prev_hash as usize { hash_2 } else { hash_1 };
                        if (new_hash as i64) == start_hash {
                            panic!("I went into the cycle, i give up!");
                        }
                        if start_hash == -1 {
                            start_hash = new_hash as i64;
                        }
                        let Some((key2, value2)) = self.table[new_hash].clone() else { return };
                        self.table[new_hash] = Some((key.to_string(), value));
                        self._insert(&key2, value2, start_hash, new_hash as i64);
                    }
                }
            }

        }
    }

    pub fn insert(&mut self, key: &String, value: i64) {
        self._insert(key, value, -1, -1);
    }

    pub fn contains(&mut self, key: &String) -> bool {
        match self.find(key) {
            Some(_) => true,
            None => false
        }
    }
    pub fn find(&mut self, key: &String) -> Option<(String, i64)> {
        let hash_1 = hash1(&key, self.table_size) as usize;
        let hash_2 = hash2(&key, self.table_size) as usize;

        if let Some((key2, _)) = &mut self.table[hash_1] {
            if *key2 == *key {
                return self.table[hash_1].clone();
            }
        } else if let Some((key2, _)) = &mut self.table[hash_2] {
            if *key2 == *key {
                return self.table[hash_2].clone();
            }
        }
        return None
    }
    pub fn remove(&mut self, key: &String) {
        let hash_1 = hash1(&key, self.table_size) as usize;
        let hash_2 = hash2(&key, self.table_size) as usize;

        if let Some((key2, _)) = &mut self.table[hash_1] {
            if *key2 == *key {
                self.table[hash_1] = None;
            }
        } else if let Some((key2, _)) = &mut self.table[hash_2] {
            if *key2 == *key {
                self.table[hash_2] = None;
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
В первой строке ввода число запросов n, в следующих n строках запросы вида (k - строка, v - число <= 1e9):

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
                let (key, value) = (&operation[1], operation[2].parse::<i64>().expect("Not a number!"));

                hashmap.insert(&key, value);
            }
            "-" => {
                let key = &operation[1];

                hashmap.remove(&key);
            }
            "?" => {
                let key = &operation[1];
                if hashmap.contains(&key) {
                    let Some((_, value)) = hashmap.find(&key) else { continue; };
                    println!("{}", value);
                } else {
                    println!("none");
                }
            }
            _ => {}
        }
    }
}




