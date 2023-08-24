# Simple Banking System 

This project is part of my CS&131 Computer Programming 1 in C++ course to graduate with an AAS in Computer Science with Honors. 
To complete the Honors Contract that I created with my professor at Everett Community College, Eihab El Radie; 
I will create three projects. 
I plan to iterate each project forward, expanding the application as the course progresses.

## Project 1: Login

Project 1 is primarily a Profile Creation and Login feature. 
There is no data structure because we have yet to delve into file manipulation. 
Upon application execution, the user is prompted to log in, create a profile, or exit the program. 
All three options are implemented. 
However, upon login, the features virtually end. 

In my next iteration, I will utilize file manipulation to allow the user to save their profile in a file. 
Once their profile is created, they can log in, even after exiting the program. 
After logging in, I plan to give the user an array of options, 
such as viewing (fake) checking accounts and changing personal information like their password.

### ! NOTE !

The original Project 1 repository became corrupted while 
I was experimenting with and trying to self-teach Git. 
All code and commit history are saved, 
but the repository will not work as intended (to my knowledge).
The original repository URL is: <br>
https://github.com/TaylorBisset/CS131-BankingLogin-HonorsProject1

## Project 2: File Manipulation

For my second iteration of this project, I decided to use <filesystem> and <fstream> to utilize files to store data (locally). 
This is my first attempt at any data storage. I created a new directory in the project called "profiles" 
that holds .txt files associated with user profiles. 
For example, taylor.txt's content holds `username: taylor` and `password: qwer1324!@#$` 
and will be where banking account information will be stored.

In the final iteration of this project (for CS131), I plan to use vectors, arrays, and pointers for data management.
The user can create checking and savings accounts within their profile files. 

## Project 3: Vectors, Structures, and Pointers

In my final iteration of this project, I used vectors, pointers, and structures to help facilitate the banking portion. 
This included creating a class Account, which I then had vectors to create and manage account numbers and balances.
Manipulating the files gave me great difficulty, especially when overwriting the files' new balances. 
I spent several hours debugging and rewriting code to make these accounts work as intended. 

### Final Thoughts

I am delighted with the final results of my project; 
Recreating this project with my current knowledge would make it operate much more smoothly.

This project provided me with great insight as the course progressed. I had much fun and experienced incredible frustration. 
