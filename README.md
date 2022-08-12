# A recursive continued fraction Latex converter
* This function models the problem as a binary tree which tries to solve left and right branches 
### Inputs:
* Number of levels of continued fraction
* Current depth of binary tree
* Integer value of numerator and denominator 
### Return: 
* A Latex formatted strings of continued fraction  
### ----------------------------------------------------------------------------

### Compilling

_Below is an example of how you can compile the source code using gcc._

1. Compile with gcc:
   ```sh
   gcc frac.c -o frac.out
   ```
2. Execute the output binary:
   ```sh
    ./frac.out <Number>
   ```
3. Stream the output to a tex file:
   ```sh
   ./frac.out <Number> > my_tex.tex
   ```
4. Install tex on the Ubuntu using:
   ```sh
   sudo apt update
   sudo apt install texlive-full -y
   ```
5. Produce pdf file from tex file using:
   ```sh
   pdflatex my_tex.tex
   ```