# CSC212 Final Project: Sparse Matrices with Linked Lists
*Created by Rick Herchuk, Lisandro Nunez, Demetri Petrou, Justin Watkins   

## Overview

This is our repository for our CSC212 Data Structures & Algorithms final project. This is an implementation of Sparse Matrices with Linked Lists. 
A Sparse Matrix, also known as a Sparse Array, is a matrix that mostly consists of zeroes. In our implementation, the nonzero elements of the Sparse Matrix are "linked" together using a linked list data structure, using pointers from nonzero value to nonzero value. Using a linked list allows for only having to store the nonzero elements and their coordinates in memory, instead of storing a large contiguous block of memory with all of the zeroes.

![Alt Text](https://matteding.github.io/images/coo.gif)

GIF Credit: https://matteding.github.io/2019/04/25/sparse-matrices/

## Prerequisites

### Linux (apt package manager)

1. **Install g++ and SFML library**

` sudo apt update `

` sudo apt install g++ && libsfml-dev`

### MacOS (coming soon)

### Windows (coming soon)

## How to Compile and Run

### Linux (Debian-based)
0. Open terminal
1. Clone this repository
`git clone https://github.com/fherchuk/CSC212-Final-Project.git`
2. cd to this cloned repo's directory
`cd CSC212-Final-Project.git`
3. Type `make`
4. Type `./matrix_app` to run

### MacOS (coming soon)

### Windows (coming soon)