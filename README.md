# Calculator_CPP
Implementation of SmartCalc on C++


*Dijkstra's algorithm* is used to translate expressions into *reverse Polish notation* to implement the calculator. 

- The program is developed in C++ language of C++17 standard
- The full coverage of expression calculation modules with unit-tests using the GTest library prepared
- The program is built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests. 
- The program is implemented using the MVC pattern, and also:
   - there is no business logic code in the view code
   - there is no interface code in the controller and the model
   - controllers is thin
- Both integers and real numbers with a dot can be input into the program. The input of numbers in exponential notation provided
- The calculation is done after you complete entering the calculating expression and press the `=` symbol.
- Calculating arbitrary bracketed arithmetic expressions in infix notation
- Calculate arbitrary bracketed arithmetic expressions in infix notation with substitution of the value of the variable _x_ as a number
- Plotting a graph of a function given by an expression in infix notation with the variable _x_ (with coordinate axes, mark of the used scale and an adaptive grid)
- Domain and codomain of a function are limited to at least numbers from -1000000 to 1000000
- Users are able to enter up to 255 characters
- Bracketed arithmetic expressions in infix notation supports the following arithmetic operations and mathematical functions:
   - **Arithmetic operators**:
     | Operator name | Infix notation <br /> (Classic) | Prefix notation <br /> (Polish notation) |  Postfix notation <br /> (Reverse Polish notation) |
      | --------- | ------ | ------ | ------ |
      | Brackets | (a + b) | (+ a b) | a b + |
      | Addition | a + b | + a b | a b + |
      | Subtraction | a - b | - a b | a b - |
      | Multiplication | a * b | * a b | a b * |
      | Division | a / b | / a b | a b \ |
      | Power | a ^ b | ^ a b | a b ^ |
      | Modulus | a mod b | mod a b | a b mod |
      | Unary plus | +a | +a | a+ |
      | Unary minus | -a | -a | a- |
      >Note that the multiplication operator contains the obligatory sign `*`. Processing an expression with the omitted `*` sign is optional and is left to the developer's decision
   - **Functions**:
      | Function description | Function |
      | ------ | ------ |
      | Computes cosine | cos(x) |
      | Computes sine | sin(x) |
      | Computes tangent | tan(x) |
      | Computes arc cosine | acos(x) |
      | Computes arc sine | asin(x) |
      | Computes arc tangent | atan(x) |
      | Computes square root | sqrt(x) |
      | Computes natural logarithm | ln(x) |
      | Computes common logarithm | log(x) |

## Part 2. Credit calculator

A special mode "credit calculator" provided:
- Input: total credit amount, term, interest rate, type (annuity, differentiated)
- Output: monthly payment, overpayment on credit, total payment

## Part 3. Deposit calculator

A special mode "deposit profitability calculator" provided:
- Input: deposit amount, deposit term, interest rate, tax rate, periodicity of payments, capitalization of interest, replenishments list, partial withdrawals list
- Output: accrued interest, tax amount, deposit amount by the end of the term
