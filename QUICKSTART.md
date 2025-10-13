# Quick Start Guide

## Your First Steps

### 1. Verify Rust Installation
```bash
rustc --version
cargo --version
```

You should see: `rustc 1.85.0` (or similar)

### 2. Run Your First Example
```bash
cd 01-basics/hello_world
cargo run
```

Expected output:
```
Hello, World!
Welcome to Rust learning!
Hello, Rustacean!
...
```

### 3. Explore and Modify
Open `01-basics/hello_world/src/main.rs` in your editor and:
- Change the messages
- Add new println! statements
- Run again with `cargo run`

### 4. Follow the Learning Path

#### Week 1: Foundations
- Day 1-2: `01-basics/` - Complete all 5 examples
- Day 3-4: Focus deeply on `ownership` - this is critical!
- Day 5-7: `02-intermediate/traits_generics` and `error_handling`

#### Week 2: Functional & Collections
- Day 1-3: `collections`, `iterators`, `closures`
- Day 4-5: Revisit and combine concepts
- Day 6-7: Start `03-advanced/`

#### Week 3: Advanced Concepts
- Day 1-3: `async_programming`, `concurrency`
- Day 4-5: `smart_pointers`
- Day 6-7: Review and build small project

#### Week 4: Blockchain & DeFi
- Day 1-3: `04-blockchain-foundations/` all examples
- Day 4-5: `05-defi-projects/amm_simulator`
- Day 6-7: `05-defi-projects/token_contract`

## Essential Commands

### Building and Running
```bash
cargo build        # Compile (debug mode)
cargo run          # Build and run
cargo build --release  # Optimized build
cargo run --release    # Optimized run
```

### Development Tools
```bash
cargo check        # Quick error check (faster than build)
cargo clippy       # Linter with suggestions
cargo fmt          # Auto-format code
cargo test         # Run tests
cargo doc --open   # Generate and open documentation
```

### Common Patterns

#### Creating New Project
```bash
cargo new my_project
cd my_project
cargo run
```

#### Adding Dependencies
Edit `Cargo.toml`:
```toml
[dependencies]
serde = "1.0"
tokio = { version = "1.0", features = ["full"] }
```

Then run:
```bash
cargo build  # Downloads and compiles dependencies
```

## Learning Tips for Math/Quant Background

### Think in Types
```rust
// Instead of thinking: "x is a number"
// Think: "x has type i32, which forms a ring under + and *"

let x: i32 = 5;
let y: f64 = 3.14;
```

### Ownership ≈ Linear Logic
```rust
// Each value has exactly one owner (linear types)
let s1 = String::from("hello");
let s2 = s1;  // s1 MOVED to s2 (not copied!)
// s1 is now invalid

// Borrowing creates references (non-linear)
let s3 = String::from("world");
let r1 = &s3;  // Borrow (can have many)
let r2 = &s3;  // Another borrow (OK!)
```

### Traits ≈ Type Classes
```rust
// Like Haskell's type classes
trait Numeric {
    fn add(self, other: Self) -> Self;
}

// ∀T. Numeric(T) ⇒ ...
fn sum<T: Numeric>(a: T, b: T) -> T {
    a.add(b)
}
```

### Option/Result ≈ Monads
```rust
// Option<T> ≈ Maybe T
// Result<T,E> ≈ Either E T

// map is fmap (Functor)
Some(5).map(|x| x * 2)  // Some(10)

// and_then is >>= (Monad bind)
Some(5).and_then(|x| Some(x * 2))  // Some(10)

// ? operator is like do-notation
fn example() -> Result<i32, String> {
    let x = may_fail()?;  // Early return on Err
    let y = may_fail2()?;
    Ok(x + y)
}
```

## Common Beginner Mistakes

### 1. Fighting the Borrow Checker
```rust
// ❌ Won't compile
let mut vec = vec![1, 2, 3];
let first = &vec[0];  // Immutable borrow
vec.push(4);  // ❌ Can't mutate while borrowed
println!("{}", first);

// ✅ Solution: Limit borrow scope
let mut vec = vec![1, 2, 3];
{
    let first = &vec[0];
    println!("{}", first);
}  // Borrow ends here
vec.push(4);  // ✅ Now OK
```

### 2. String vs &str
```rust
// String = owned, heap-allocated
// &str = borrowed string slice

let s1: String = String::from("hello");
let s2: &str = "world";  // String literal
let s3: &str = &s1;  // Borrow from String
```

### 3. Expecting Python-like Behavior
```rust
// In Python: Everything is a reference
// In Rust: Must be explicit

// Python
# x = [1, 2, 3]
# y = x  # Both point to same list

// Rust
let x = vec![1, 2, 3];
let y = x;  // MOVED, x no longer valid!

// Want same behavior? Use reference or clone
let x = vec![1, 2, 3];
let y = &x;  // y borrows x
let z = x.clone();  // z is a deep copy
```

## When You Get Stuck

### 1. Read the Compiler Error
Rust has the best error messages of any language. Example:
```
error[E0382]: borrow of moved value: `s1`
  --> src/main.rs:4:20
   |
2  |     let s1 = String::from("hello");
   |         -- move occurs because `s1` has type `String`
3  |     let s2 = s1;
   |              -- value moved here
4  |     println!("{}", s1);
   |                    ^^ value borrowed here after move
```

The compiler tells you:
- What went wrong
- Where it happened
- Why it's a problem
- Often suggests a fix

### 2. Use `cargo check`
Much faster than `cargo build`, catches most errors.

### 3. Search the Error Code
```bash
rustc --explain E0382
```

### 4. Check the Documentation
```bash
# Open docs for std library
rustdoc --open

# In your project
cargo doc --open
```

## Next Steps After Each Section

### After 01-basics:
Build a simple calculator that:
- Takes two numbers
- Performs operations (+, -, *, /)
- Handles division by zero with Result

### After 02-intermediate:
Build a time series analyzer that:
- Reads price data
- Calculates returns
- Computes moving averages
- Finds max drawdown

### After 03-advanced:
Build a concurrent market data fetcher that:
- Fetches prices from multiple sources
- Uses async/await
- Handles errors gracefully
- Aggregates results

### After 04-blockchain-foundations:
Build a simple cryptocurrency that:
- Maintains a blockchain
- Validates transactions
- Implements basic consensus
- Prevents double-spending

### After 05-defi-projects:
Build your own DeFi protocol! Ideas:
- Lending protocol
- Staking mechanism
- Order book DEX
- Options pricing engine

## Resources Cheat Sheet

- **Stuck on syntax?** → [Rust by Example](https://doc.rust-lang.org/rust-by-example/)
- **Compiler error?** → Read it carefully, use `rustc --explain`
- **Need a library?** → [crates.io](https://crates.io/)
- **API docs?** → [docs.rs](https://docs.rs/)
- **Concept unclear?** → [The Rust Book](https://doc.rust-lang.org/book/)

## Test Your Understanding

After each section, can you answer:

1. **After ownership:**
   - What are the three rules of ownership?
   - When should you use &T vs &mut T vs T?
   - What is the difference between Copy and Clone?

2. **After traits:**
   - How do traits differ from interfaces?
   - What are associated types?
   - What is a trait bound?

3. **After iterators:**
   - What makes iterators zero-cost?
   - Difference between iter(), into_iter(), iter_mut()?
   - What is the difference between map and flat_map?

4. **After blockchain:**
   - Why is changing a block computationally expensive?
   - What is the probability of finding a valid PoW hash?
   - How does the chain structure prevent tampering?

---

**Remember:** Learning Rust is like learning math - it's rigorous, but once you understand it, everything makes perfect sense. The compiler is your proof checker!

Happy coding! 🦀
