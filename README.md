# C Lite Compiler

This is a simple compiler project made using C language. It is created to understand the basic working of a compiler, especially how code is analyzed and processed.

---

## About the Project

The C Lite Compiler is a basic implementation of a compiler for a simplified C-like language.
It mainly focuses on two important parts:

* **Lexical Analysis** → Breaking input code into tokens
* **Parsing** → Checking whether the code follows correct syntax

This project helps in understanding how a compiler works step by step.

---

## Features

* Identifies keywords, identifiers, operators, and constants
* Converts input code into tokens
* Performs basic syntax checking
* Simple and easy-to-understand implementation

---

## Project Structure

```
C_lite/
│── src/
│   ├── LA.c
│   ├── parser.c
│
│── README.md
│── LICENSE
│── .gitignore
```

---

## How to Run

### Step 1: Compile the files

```
gcc src/LA.c -o LA
gcc src/parser.c -o parser
```

### Step 2: Run the programs

```
./LA
./parser
```

---

## What I Learned

* Basics of compiler design
* How lexical analysis works
* How parsing checks syntax
* Improved my C programming skills

---

## Future Improvements

* Add symbol table
* Add semantic analysis
* Combine all phases into one program

---

## 👨‍💻 Author

Aditya Sahani
B.Tech CSE (AI/ML), IILM University

---

⭐ Feel free to explore and improve this project!
