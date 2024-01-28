# Calculator

A calculator build using a text parser, which builds an abstract syntax tree, and simplifies it.

## Description

This project is a simple calculator in the terminal, which receives a normal mathematical expression, and calculates the answer using a parse tree. 

## Installing
#### Linux
Build the project using the MakeFile:
```
make
```

The included makefile will build the project into a binary file.

### Executing program
The binary file is located in the */bin* folder, and can be executed with the following code snippet:
```
./calc
```
Or:
```
make run
```

#### Windows
Build the project using the MakeFile:
```
make win
```

The included makefile will build the project into an *.exe* file.

### Executing program
The *.exe* file is located in the */bin* folder, and can be executed by double clicking or from the terminal with:
```
.\calc
```
Or:
```
make win_run
```

## Authors

Niels Versteeg (s3322637)

## TODO
* <del> Add sin, cos and tan
* Tree check function
* Stress test
* <del> Auto separate input
* Add other calculator functions