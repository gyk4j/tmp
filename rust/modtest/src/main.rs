mod first;

fn main() {
    println!("Hello, world!");
    first::function();
    first::second::function();
    first::second::amod::function();
}
