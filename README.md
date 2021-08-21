# CO222 Project1 Clock
CO222-2021 : Programming Methodology | Project 1

You have to develop a digital clock that prints the current time, and date on the linux
terminal. If a color is given as an argument to the program, the program should be able to
print a colored output. You will be given a sample program (prog) that would do the same
task. Your task is to replicate the functionality of the given program. Below figures show the
expected output from your program.
The output should print exactly at the same place and scale as the given program
(prog)

# Inputs:

Command-line arguments:

● If a colour is given as an argument to the program with the ‘-c’ flag, the program
should be able to print the clock using the given colour. If no argument is given, use
black and white as default.

![image](https://user-images.githubusercontent.com/73381996/130306703-2f5ba104-cb0d-493a-830b-713f7cc28da9.png)

![image](https://user-images.githubusercontent.com/73381996/130306705-ac47b02b-2d72-4bdf-b859-89ac56c0627e.png)


● These colors should be supported by the program - black, red, green, yellow, blue,
magenta, cyan

● If -h flag is given or the given arguments are invalid, you should print the usages of
your program (how the arguments should be given). See the sample binary given for
the expected behaviour.

# Problem breakdown
Instead of directly going to code the solution, you must break down the problem into smaller
subproblems, such as
1. How to get user inputs as arguments
2. How to get the current system time
3. How to get the current system time as a string
4. How to print a number
5. How to print multiple numbers at different positions
6. How to print the date
7. How to assign a color to printed characters
8. Error handling for the program
Instead of thinking about the problem as a whole, try and find the solutions for each one of
the above questions. That will help you to reach the final goal smoothly and accumulatively.

# Important

● Pay attention to boundary cases and handle the errors correctly.

● Refer ANSI escape codes which will be useful to complete this project.

● When you try to get the system time, there are many different ways you can
approach. Most of the examples you can find might be too complicated for you to
understand. But there is a very easy way to do it with asctime and localtime functions
from time.h library.

● Under no circumstance, you should copy somebody else’s code. Copying someone
else’s code or showing your source code to anyone else will earn you zero mark for
the whole project. You might need to be really careful because this has happened
many times in the past. Therefore, put some honest effort to earn the marks for
project 1.

● Basic functionality, functionality with colors, error handling, modularization (functions)
and good coding practices will be considered when marking.

# Deadline
The deadline for the submission is 29th of August 2021 23:55h. Late submissions are
accepted with 20% minus marks of what you earn for every day late. Submit your
answer (without compile error or warning) in a single file with the filename E18yyyproject1.c,
where yyy is your registration number.
Marks: You will get 10 marks for your final grade from the project

