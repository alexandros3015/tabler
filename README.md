# Tabler

A cool that makes a cool little table based on like stuff. I made it because I was learning about this in math and was bored so I make this so yeah.

## controls
--noprint to not print the table, useful for if you only quickly want to plot something.
Enter either a or g (arithmetic or geometric). 
Arithmetic Structure: `f(n) = mn + b`
Geometric Stucture: `f(n) = b(m)^n`
Use `--remove` to remove the file `data.txt` after running the script. data.txt contains the file

## gnuplot

If you want to plot the graph, first you need to [install gnuplot](https://sourceforge.net/projects/gnuplot/files/gnuplot/) and go though the installation process. Make sure to add the program to path. 
After installing gnuplot, simply add `--plot` or `--p` as an argument to running the file (e.g. `.\main.exe --plot`).
If you don't wanna plot it just don't add the argument.

### Building
To build, clone the repository, and run this command in the cloned folder:
```
gcc -o main.exe main.c -lm
```
