use std::io;

// СРАВНЕНИЕ ПОДМАТРИЦ С ПОМОЩЬЮ ХЕШЕЙ

/**
В первой строке подаются два числа n и m - размер матрицы, где n - кол-во строк, m - кол-во столбцов

В следующих n строках m чисел - матрица

В следующей строке число запросов q

В следующих 2q строках запросы вида:

`i1 j1 i2 j2`
`i3 j3 i4 j4`

В первой строке координаты верхнего левого и нижнего правого углов подматрицы (столбец строка)
Во второй аналогично для второй подматрицы

Выводится YES, если они равны, иначе NO
*/

fn get_number() -> i128 {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();
    string.trim().parse().unwrap_or(0)
}

fn get_numbers() -> Vec<i128> {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();

    let result = string
        .split(" ")
        .filter(|a: &&str| -> bool { a.len() > 0 })
        .map(|a: &str| -> i128 { a.trim().parse().unwrap_or(0) })
        .collect::<Vec<_>>().to_vec();

    return result;
}

// probably it is better to change them for some bigger numbers
const K: i128 = 7;
const M: i128 = 5;

fn main() {
    let out = get_numbers();
    let (n, m) = (out[0] as usize, out[1] as usize);
    let mut matrix = Vec::<Vec<i128>>::new();
    matrix.resize(n, Vec::<_>::new());

    for i in 0..n {
        let out = get_numbers();
        for j in 0..m {
            matrix[i].push(out[j]);
        }
    }

    let mut hashes = Vec::<Vec<i128>>::new();
    hashes.resize(n + 1, Vec::<_>::new());
    hashes[0].resize(m + 1, 0);

    for i in 1..=n {
        hashes[i].push(0);
        for j in 1..=m {
            let h = hashes[i - 1][j] + hashes[i][j - 1] - hashes[i - 1][j - 1] +
                matrix[i - 1][j - 1] * M.pow(i as u32) * K.pow(j as u32);
            hashes[i].push(h);
        }
    }

    let q = get_number();

    for _ in 0..q {
        let out = get_numbers();
        let (x1, y1, x2, y2) = (
            out[0] as usize, out[1] as usize, out[2] as usize, out[3] as usize
        );
        let out = get_numbers();
        let (x3, y3, x4, y4) = (
            out[0] as usize, out[1] as usize, out[2] as usize, out[3] as usize
        );

        let mut first_hash = hashes[x2][y2] - hashes[x1 - 1][y2] -
            hashes[x2][y1 - 1] + hashes[x1 - 1][y1 - 1];
        let mut second_hash = hashes[x4][y4] - hashes[x3 - 1][y4] -
            hashes[x4][y3 - 1] + hashes[x3 - 1][y3 - 1];

        if x1 < x3 {
            first_hash *= M.pow((x3 - x1) as u32);
        } else {
            second_hash *= M.pow((x1 - x3) as u32);
        }
        if y1 < y3 {
            first_hash *= K.pow((y3 - y1) as u32);
        } else {
            second_hash *= K.pow((y1 - y3) as u32);
        }

        if first_hash == second_hash {
            println!("YES");
        } else {
            println!("NO");
        }
    }
}

