# CSC212 Final Project: Sparse Matrices with Linked Lists
### *Created by Rick Herchuk, Lisandro Nunez, Demetrios Petrou, Justin Watkins*   

## Overview

This is our repository for our CSC212 Data Structures & Algorithms final project. This is an implementation of Sparse Matrices with Linked Lists. 
A **Sparse Matrix**, also known as a **Sparse Array**, is a matrix that mostly consists of zeroes. 
In our implementation, the nonzero elements of the Sparse Matrix are "linked" together using a linked list data structure, using pointers from nonzero value to nonzero value.
Using a linked list allows for only having to store the nonzero elements and their coordinates in memory, instead of storing a large contiguous block of memory with all of the zeroes.

![Alt Text](https://matteding.github.io/images/coo.gif)

GIF Credit: https://matteding.github.io/2019/04/25/sparse-matrices/

## How to Compile and Run

### Linux (Ubuntu/Debian/Debian-based)
1. Install gcc, g++, make, SFML library, and git in terminal

    `sudo apt update && sudo apt install gcc g++ make libsfml-dev git`

2. Clone this repository in terminal

    `git clone https://github.com/fherchuk/CSC212-Final-Project.git`

3. Go into the project directory

    `cd CSC212-Final-Project/Sparse\ Matrix\ Final\ CSC212/`

4. Compile

    `make`

5. Run executable, then window with GUI will appear

    `./matrix_gui`

    ![GUI window](images/readme-gui-window.png)

### Visual Studio Community Testing
If you would like to test the functionality of the individual functions in the matrix classes via a main function, the repository can be cloned from Visual Studio, and the sln file will be available to open and use. The main.cpp file is mostly empty and can be used to test the classes. A Matrix or MatrixVector object can be created and the methods can be used with the help of the comments.