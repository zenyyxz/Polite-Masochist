# Polite Masochist 🧙‍♂️

So, Sophie actually dared me to do this. She knew I needed a massive distraction today—April 11th is just one of those dates that needs to be buried under a mountain of total nonsense. 

I don't know why I went through with it, but I had this weird itch to see if I could make a prime number sieve in INTERCAL that was actually, 100% independent. No cheating with `syslib.i`, no pre-calculated Python loops, no shortcuts. Just one big, messy file that calculates every single prime from absolute zero while it runs.

It's absolute madness. INTERCAL doesn't even have an addition operator. I had to literally rip the bitwise adder logic out of the compiler's guts and glue it into the source just to make a counter work. 

---

## 🚀 1,000 Primes? Nah, We Went for 65,000.

The original dare was for the first 1,000 primes. But once I got the arithmetic logic unit (ALU) working, I realized I could just let it rip. Instead of stopping at 1,000, this program calculates **every single prime number a 16-bit machine can handle** (all the way up to 65,535). 

It takes about 17 seconds to speed-run the entire universe of 16-bit primes. If you see something like `LXVCDLXXIX` at the end, don't panic—that’s just INTERCAL for **65,479**. We didn't just win the dare; we over-engineered it into oblivion.

---

## 🤓 The Nerd Wiki (Built From Scratch)

Since I used the `-E` flag to ban all external libraries, I had to manually build the "brain" of the program inside the source file. Here’s what’s actually happening:

### 1. The 16-bit Ripple-Carry Adder
INTERCAL only has two real operators: **Mingle** (`$`) and **Select** (`~`). To add numbers (like `x + 1`), I had to build a ripple-carry adder. I used Mingling and Selecting to simulate XOR, AND, and OR gates to handle carry-bits. It’s slow, it’s ugly, and it’s the only way to count.

### 2. Subtraction & Two's Complement
Since subtraction is just adding a negative, I had to implement Two's Complement. To get `-x`, you flip all the bits (Selecting against a mask of all ones) and add 1. This is how the division engine works.

### 3. The Division Engine (Modulo)
There is no `%` or `/` here. To check if a number is prime, the program uses **repeated subtraction**. It takes the candidate, subtracts the divisor over and over until it hits zero or goes negative. If it hits exactly zero, it’s not a prime.

### 4. Flow Control via `COME FROM`
Forget `if/else`. INTERCAL uses `COME FROM`. It makes the logic flow backward and inside-out. It’s the primary reason I spent the whole day staring at a terminal.

---

## How to run (if you're also looking for a distraction)

1. **Get the compiler:** You need `ick` (C-INTERCAL). On Arch, you can grab it from the AUR.
2. **Compile it clean:** Run `ick -E primes.i`. The `-E` is what makes this "standalone" by banning the system math libraries.
3. **Execute:** `./primes`
4. **Wait:** It’ll spit out `II`, `III`, `V`, `VII`... as weird Roman numerals. 

It worked. I'm definitely distracted. Thanks, Sophie.
