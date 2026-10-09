# Cot - Programming Languare (Work in progress)


## I am creating this project to make writing code easy without affecting speed.

**Roadmap:**

 1. Lexer ✔
 2. Parser ✔
 3. C++ Transpiler ✔
 4. Compiler via gcc ✔
 5. print ✔
 6. variables ✔
 7. math (+, -, *, /) ✘
 8. if, else, elif ✘
 9. while, for ✘
 10. libs (import)  ✘

**What has already been done:**

 - Lexer
 - Parser
 - C++ Transpiler
 - Compiler via gcc
 - Number, string, bool
 - print
 - variables
 
 **For example, here is the code that will work right now:**
 

    x = true
	y = 228
	z = "Hello, World!"
	print("x=" x "\ny=" y "\nz=" z)

**And the result will be:**
*x=true*
*y=228*
*z=Hello, World!*

**As you have already gathered, the .cot code follows this path:**

> .cot -> lexer -> parser -> C++ transpiler -> transpiled.cpp -> compiler via gcc -> programm.exe
