#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* latex_frac(int n, int depth, int val)
{
	char* ret = (char*) malloc (100000);
  if (depth == n){
		sprintf(ret,"%d", val); // Base case condition
	return ret;
  }
  char* left = latex_frac(n, depth + 1, 2 * val);
  char* right = latex_frac(n, depth + 1, 2 * val + 1);
  sprintf(ret,"%d+\\frac{%s}{%s}", val, left, right);
  
  free(left);
  free(right);
  
  return ret;
}

int main (int argc, char **argv)
{
  if (argc != 2)
    {
      fprintf(stderr, "Invalid invocation!\n\n");
      fprintf(stderr, "SYNPOSIS:\n");
      fprintf(stderr, "\t%s n\n", argv[0]);
      return EXIT_FAILURE;
    }

  //int n = strtoll(argv[1], NULL, 10);
  int n = atoi(argv[1]);
  char* s = latex_frac(n, 1, 1);

  FILE* file = fopen("sina_frac.tex", "w");
    if (file == NULL)
    {
       fprintf(stderr,"Could't Create a File!");
       return EXIT_FAILURE;
    }
    else{
     fputs(s,file);
     fclose(file);
    }
  printf("\\documentclass{article}\n\\begin{document}\n");
  printf("\\begin{equation}\n%s\n\\end{equation}\n", s);
  printf("\\end{document}\n");

  free(s); //No memory leak

  return EXIT_SUCCESS;
}

