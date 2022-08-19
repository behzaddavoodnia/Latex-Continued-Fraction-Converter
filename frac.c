#include <stdio.h>
#include <stdlib.h>

void latex_repr(int n, int depth, int val)
{
  if (depth == n)
    printf("%d", val);
  else {
    printf("%d+\\frac{", val);
    latex_repr(n, depth + 1, 2 * val);
    printf("}{");
    latex_repr(n, depth + 1, 2 * val + 1);
    printf("}");
  }
}

int main(int argc, char **argv)
{
  int n;
  char *tex_file;
  if (argc > 1)
    n = strtol(argv[1], NULL, 10);
  else {
    fprintf(stderr, "Enter the n: ");
    scanf("%d", &n);
          }
  if (n > 10) {
    fprintf(stderr, "n is too high: %d\n", n);
    return EXIT_FAILURE;
                  }
  printf("\\documentclass{article}\n\\begin{document}\n\\begin{equation}\n");
  latex_repr(n, 1, 1);
  printf("\n\\end{equation}\n\\end{document}\n");
  return EXIT_SUCCESS;
}