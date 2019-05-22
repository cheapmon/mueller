# mueller
a simple brainfuck compiler

**Compile:** `clang++ src/mueller.cpp -o mueller`

**Run:** `./mueller [file]` 

---
**How do you compile brainfuck** you ask?
Well, let me tell you.

First, you transpile it to C, using this table from [Wikipedia](https://en.wikipedia.org/wiki/Brainfuck):
| brainfuck command | C equivalent                                                |
|-------------------|-------------------------------------------------------------|
| (Program Start)   | `char array[INFINITELY_LARGE_SIZE] = {0}; char *ptr=array;` |
| `>`               | `++ptr;`                                                    |
| `<`               | `--ptr;`                                                    |
| `+`               | `++*ptr;`                                                   |
| `-`               | `--*ptr;`                                                   |
| `.`               | `putchar(*ptr);`                                            |
| `,`               | `*ptr=getchar();`                                           |
| `[`               | `while (*ptr) {`                                            |
| `]`               | `}`                                                         |
Then you compile the transpiled C file using `clang -O3` magic.

Yeah, that's it.

---

**Why the name?** Because of Brainfucks' creator [Urban Müller](https://esolangs.org/wiki/Urban_M%C3%BCller).

**Is this a joke?** Yes.
