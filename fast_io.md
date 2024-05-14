# О том, как можно ускорить ввод/вывод

* [C++](#c)
* [Rust](#rust)

## C++

На `C++` можно воспользоваться вот этими двумя магическими строчками:

```c++
#include <iostream>

int main() {
    // вот они
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    // magic goes here
    
    return 0;
}
```

По сути эти строчки делает рассинхронизацию потоков `cin` и `cout`, поэтому они работают быстрее. 
Также советуется не использовать `std::endl`, так как он делает дорогой flush

Если же вам нужна МАКСИМАЛЬНАЯ производительность, то используйте замечательный [blazingio.hpp](https://github.com/purplesyringa/blazingio)

```c++
#include <iostream>

// здесь идет blazingio

int main() {
    // magic goes here
    
    return 0;
}
```

При этом `std::cin` и `std::cout` получат существенный буст к производительности

## Rust

На Rust можно воспользоваться подобным сниппетом:

```rust
use std::io::{Read, Write, stdout, stdin};
use std::io::{StdinLock, StdoutLock, BufWriter, BufReader};

struct FastIO {
    // thanks mrsobakin
    writer: BufWriter<StdoutLock<'static>>,
    reader: BufReader<StdinLock<'static>>
}

impl FastIO {
    fn new(capacity: usize) -> Self {
        Self {
            writer: BufWriter::with_capacity(capacity, stdout().lock()),
            reader: BufReader::with_capacity(capacity, stdin().lock())
        }
    }
    fn is_whitespace(ch: u8) -> bool {
        ch == 9 || ch == 10 || ch == 32 || ch == 13
    }
    fn ch(&mut self, skip_whitespace: bool) -> char {
        let mut ch = [0];
        self.reader.read_exact(&mut ch).unwrap();
        while FastIO::is_whitespace(ch[0]) && skip_whitespace {
            if let Err(_) = self.reader.read_exact(&mut ch) { break; }
        }
        char::from_u32(ch[0] as u32).unwrap()
    }
    fn i64(&mut self) -> i64 {
        let mut ch = [0];
        let mut neg = false;

        while !(ch[0] >= 48 && ch[0] <= 57 || ch[0] == 45) {
            self.reader.read_exact(&mut ch).unwrap();
        }
        if ch[0] == 45 { neg = true; self.reader.read_exact(&mut ch).unwrap(); }

        let mut i: i64 = 0;
        while ch[0] >= 48 && ch[0] <= 57 {
            i = i * 10 + ((ch[0] - 48) as i64);
            if let Err(_) = self.reader.read_exact(&mut ch) {
                break;
            }
        }

        if neg { -i } else { i }
    }
    fn string(&mut self) -> String {
        let mut ch = [0];
        self.reader.read_exact(&mut ch).unwrap();

        let mut s = "".to_string();
        while FastIO::is_whitespace(ch[0]) {
            if let Err(_) = self.reader.read_exact(&mut ch) {
                break;
            }
        }
        while !FastIO::is_whitespace(ch[0]) {
            s += &(ch[0] as char).to_string();
            if let Err(_) = self.reader.read_exact(&mut ch) {
                break;
            }
        }
        return s;
    }
}

fn main() {
    let io = FastIO::new(1000000);

    let char = io.ch(true); // символ
    let string = io.string(); // строка
    let int = io.i64(); // число
    
    // так как print! делает flush, используем write!
    writeln!(io.writer, "{} {} {}", char, string, int);
}
```
