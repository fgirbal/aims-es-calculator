# AIMS Embedded Systems Assignment
#### Author: Francisco Girbal Eiras

From a computer science perspective, an interpreter is a program that executes instructions given to it, without the need for this program to be given in machine code (i.e. before it is compiled). Examples of interpreters abound, from macro languages like Excel to the Python interpreter. At a simpler level, a calculator that takes in a string and returns the result of the operations described in it is an arithmetic interpreter of that string. 
There are many use cases for the use of such an interpreter in a low-power embedded system. An example can be a card reader machine that a merchant takes to the market: it's convenient this machine can do an arbitrary calculations (e.g. a tally of the items, including discounts on particular items), while at the same time being able to accept card transactions. This machine should be as low-power as possible to avoid the need to constantly recharge it.

In this project, we implemented a calculator interpreter in C++ with the explicit goal of efficient computation of the expressions given.

### Compiling and running

Clone this Github repo, and to compile the parser calculator, run (requires `g++`):

```
cd src
make
```

Which should produce a `string_calculator` executable. Then to run it simply execute:

```
./string_calculator
```

At which point you should see the following:

```
-------------- Welcome to the parser calculator! --------------
|                                                             |
| Enter an expression using the operators +, -, *, /, ^, (, ) |
|                                                             |
|  - The default engine uses an infix to postfix conversion   |
|      (enter 'p' to go back to it)                           |
|  - Enter 's' for parsing using a syntax tree                |
|  - Enter 'h' for a detailed comparison of both parsers      |
|  - Enter 'e' to exit                                        |
|                                                             |
---------------------------------------------------------------
[p] >> 
```

And from there you can simply query for a given expression, using either the postfix (`p`) or syntax tree (`s`) implementations. See `report.pdf` for a brief overview of each method, and a comparison between the two.

## <span></span>

###### Last edit: 29 Nov 2020 by Francisco Eiras