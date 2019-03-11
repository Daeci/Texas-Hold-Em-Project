# Texas-Hold-Em-Project
Texas Hold 'Em Project for CS225

Coding style:
Every .cpp file except for Main.cpp should come with its own .h file

#include style
1) have the default C/C++ library headers first, then use the user-created .h files

namespaces:
1) do not use the std namespace as it is better practice to simply use std::

variable declaration:
1) declare variables right before they need to be used (saves a little bit of memory)
example:
cout << "Enter a letter: ";
char letter;
cin >> letter;

curly braces:
1) main should always have the curly brace underneath
example:
int main()
{

}

2) every function definition should have the curly brace underneath
example:
void function1()
{

}

3) every condition statement (if, elseif, else, for, while, do-while, switch) should have the curly brace on the same line
examples:
if {

}

while () {

}

switch () {

}

spacing:
1) add spaces in between each new function definition
example:
void function1()
{
 
}
--space--
void function2()
{

}
2) add a space after each for, do-while, while, and switch loop
example:
for () {

}
--space--
//continuing code
3) add a space after each if/if-else/else logic string is completed
example:
if (something) {

}
elseif (something {

}
else {

}
--space--
//continuing code

function declaration and definition:
1) any function that will be used in other functions in a file MUST have a declaration at the top of the file
2) any function created in Main.cpp to be used in Main.cpp MUST have a declaration before main (at the top of the file)
