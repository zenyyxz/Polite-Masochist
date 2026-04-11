# Polite Masochist 

Sophie actually dared me to do this. She knew I needed a massive distraction today—April 11th is just one of those dates that needs to be buried under a mountain of total nonsense. 

I have no idea why I went through with it, but I had this weird itch to see if I could make a prime number sieve in INTERCAL that was actually, 100% independent. No cheating with `syslib.i`, no pre-calculated Python loops, no shortcuts. Just one big, messy file that calculates every single prime from absolute zero while it runs.

It's absolute madness. INTERCAL doesn't even have an addition operator. I had to literally rip the bitwise adder logic out of the compiler's guts and glue it into the source just to make a counter work. 

---

##  The Flex List (What's under the hood)

I didn't just find some primes; I rebuilt the basics of computing in a language designed to be impossible. Here’s the raw list of what’s in this file:

- **Manual 16-bit ALU:** I built a ripple-carry adder from scratch using only bit-mingling and selecting. No `+`, just pure binary logic.
- **Custom Subtraction:** Implemented Two's Complement manually to handle negative numbers.
- **Division/Modulo Engine:** Since there's no `%` operator, I built a division engine using repeated bitwise subtraction.
- **Zero-Library Independence:** Compiled with `-E`. This thing doesn't use a single external library or the standard `syslib.i`. It’s a total loner.
- **Full 16-bit Sieve:** Instead of stopping at 1,000, it exhausts the entire 16-bit space (up to 65,535) in about 17 seconds.
- **C-Powered "Double-Pipe" Logger:** Since 65,000 primes will absolutely murder your terminal scrollback buffer, I built a C logger to save everything to `primes.txt` while you watch it happen.
- **The "Humanizer" (C++ Converter):** Because reading Roman numerals makes my eyes bleed, I added a C++ post-processor to turn the `primes.txt` into standard decimal numbers in `primes_in_decimal.txt`.

---

##  The Nerd Wiki (Everything Built From Scratch)

Since I used the `-E` flag to ban all external libraries, I had to manually build the "brain" of the program inside the source file. Here’s what’s actually happening under the hood:

### 1. The 16-bit Ripple-Carry Adder (The "ALU")
INTERCAL has two main operators: **Mingle** (`$`) and **Select** (`~`). That's it. To add two numbers (like `x + 1`), I had to build a ripple-carry adder.
- **Mingle:** Interleaves the bits of two numbers.
- **Select:** Picks bits out of a number based on a mask.
By Mingling a number with a mask and then Selecting specific bits, I can simulate XOR, AND, and OR gates. I used these to build the carry-out logic for each bit. It's slow, it's ugly, and it's the only way to count.

### 2. Subtraction & Two's Complement
Since subtraction is just adding a negative number, I had to implement Two's Complement. 
- To get `-x`, you flip all the bits and add 1.
- Flipping bits in INTERCAL is done by Selecting the number against a mask of all ones.
I used this to build the `x - y` logic, which is the foundation of the division engine.

### 3. The Division Engine (Modulo)
There is no `%` or `/` in this world. To check if a number is prime, I have to divide it by every prime I've found so far.
- I implemented this using **repeated subtraction**.
- The program takes the candidate, subtracts the divisor over and over until it hits zero or goes negative.
- If it hits exactly zero, the remainder is zero, and the number isn't prime.

### 4. Flow Control via `COME FROM`
Forget `if/else` or `while` loops. INTERCAL uses `COME FROM`.
- Instead of saying "if prime, go to line 5", I have to go to line 5 and say "COME FROM line 2 IF the prime-check passed".
- It makes the logic flow backward and inside-out. It’s the primary reason I spent four hours staring at a wall today.

### 5. The "Humanizer" Logic
The C++ converter is a bit of a relief after all that INTERCAL. It parses the Roman numerals but has to handle the overline (underscores) properly.
- INTERCAL outputs a line of underscores *above* any character that should be multiplied by 1000.
- `LXVCDLXXIX` for 65,479 actually appears in the text as `___` then the Roman string.
- The C++ tool counts those underscores and correctly splits the string into "thousands" and "ones" before doing the math.

---

##  How to Read the Output (Butchered Roman Numerals)

If you see something like `LXVCDLXXIX`, don't panic. It’s not broken; it’s just INTERCAL being itself. 

- **LXV** = 65 (The thousands part)
- **CD** = 400
- **LXXIX** = 79
- **Total** = 65,479 (Which is a prime!)

---

## How to run (if you're also looking for a distraction)

1. **Get the compiler:** You need `ick` (C-INTERCAL). 
2. **Compile the Sieve:** Run `ick -E primes.i`. This creates the `primes` binary.
3. **Compile the Tools:** 
   - `gcc logger.c -o logger`
   - `g++ roman_to_decimal.cpp -o roman_to_decimal`
4. **Execute:** `./logger`
5. **Watch the magic:** It’ll spit out Roman numerals on your screen, save them to `primes.txt`, and then *automatically* convert them all to decimal in `primes_in_decimal.txt`.

It worked. Thanks, Sophie :)
