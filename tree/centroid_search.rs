use std::io;

// ПОИСК ЦЕНТРОИДА

/**
В первой строке числа n - кол-во вершин
Далее n - 1 строка вида `a b`, где a и b - номера соединенных вершин

Программа выводит 1 или 2 центроида у данного дерева
*/

fn get_number() -> i32 {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();
    string.trim().parse().unwrap_or(0)
}

fn get_numbers() -> Vec<i32> {
    let mut string = String::new();
    io::stdin().read_line(&mut string).unwrap();

    let result = string
        .split(" ")
        .filter(|a: &&str| -> bool { a.len() > 0 })
        .map(|a: &str| -> i32 { a.trim().parse().unwrap_or(0) })
        .collect::<Vec<_>>().to_vec();

    return result;
}

fn dfs(vertex: i32, graph: &Vec<Vec<i32>>, parent: i32) -> i32 {
    let mut counter = 1;
    for i in &graph[vertex as usize] {
        if *i == parent {
            continue;
        }
        counter += dfs(*i, &graph, vertex);
    }
    return counter;
}

fn centroid(vertex: i32, graph: &Vec<Vec<i32>>, sizes: &Vec<i32>, parent: i32) -> i32 {
    for i in &graph[vertex as usize] {
        if *i == parent {
            continue;
        }
        if sizes[*i as usize] as usize > graph.len() / 2usize {
            return centroid(*i, graph, sizes, vertex);
        }
    }
    return vertex;
}

fn centroid_search(graph: &Vec<Vec<i32>>, sizes: &Vec<i32>) -> (i32, Option<i32>) {
    let mut result: (i32, Option<i32>) = (0, None);

    result.0 = centroid(0, graph, sizes, -1);

    if graph.len() % 2 == 0 {
        'outer:
        for i in &graph[result.0 as usize] {
            for j in &graph[*i as usize] {
                if dfs(*j, &graph, *i) as usize > graph.len() / 2 {
                    continue 'outer;
                }
            }
            result.1 = Some(*i);
            break;
        }
    }

    result
}

fn tree_size(vertex: i32, graph: &Vec<Vec<i32>>, parent: i32, sizes: &mut Vec<i32>) -> i32 {
    sizes[vertex as usize] = 1;
    for i in &graph[vertex as usize] {
        if *i == parent {
            continue;
        }
        sizes[vertex as usize] += tree_size(*i, &graph, vertex, sizes);
    }
    return sizes[vertex as usize];
}



fn main() {
    let n = get_number();

    let mut tree1 =  Vec::<Vec<i32>>::new();
    let mut sizes1 = Vec::<i32>::new();

    sizes1.resize(n as usize, 0);
    tree1.resize(n as usize, Vec::<i32>::new());

    for _ in 1..n {
        let input = get_numbers();
        if input.is_empty() { continue; }
        let a = input[0] - 1;
        let b = input[1] - 1;

        tree1[a as usize].push(b);
        tree1[b as usize].push(a);
    }

    tree_size(0, &tree1, -1, &mut sizes1);
    let centroid1 = centroid_search(&tree1, &sizes1);

    match centroid1 {
        (a, Some(b)) => println!("{} {}", a + 1, b + 1),
        (a, None) => println!("{}", a + 1)
    }

}


