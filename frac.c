#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*"If you define _GNU_SOURCE , you will get access to lots of nonstandard GNU/Linux extension functions and access to traditional functions (like vasprintf())
 which were omitted from the POSIX standard (often for good reason, such as being replaced with better alternatives,
 or being tied to particular legacy implementations)"*/
 
/*
* @function		my_vasprintf
* @discussion	Variable assign to string printf:
*				The vasprintf() function shall write formatted output to a dynamically allocated string,
*				and store the address of that string in the location referenced by str_pointer. It shall behave as asprintf(),
*				except that instead of being called with a variable number of arguments, it is called with an argument list as defined by <stdarg.h>
* @param		the address of string in the location referenced by str_pointer
* @param		fmt as formaatted string 
* @param		va_list ap as argument pointer list
* @return		Returns the number of bytes (chars on the buffer) printed 
*/

int my_vasprintf(char** str_pointer, const char* fmt, va_list ap) //fmt=format pointer list, va_list=argument pointer list. Edit and assign buffer to string 
{
  va_list ap1;
  int len;
  char* buffer;
  int res;

  va_copy(ap1, ap);
  len = vsnprintf(NULL, 0, fmt, ap1); //get lenght of ap1 list 

  if (len < 0)
    return len;

  va_end(ap1);
  buffer = (char*) malloc(len + 1); //allocate memory to buffer regarding lenght of ap1 list

  if (!buffer)
    return -1;

  res = vsnprintf(buffer, len + 1, fmt, ap); //res= number of chars on the buffer 

  if (res < 0)
    free(buffer);
  else
    *str_pointer = buffer; // Assign buffer to dereference of str_pointer

  return res;
}

/*
* @function		strdup_printf		
* @discussion	
* @param		... as va_list
* @param		const char* as a format list string 
* @return		If not error accures, this function returns str_pointer as formatted dupplicated string 
*/
char* strdup_printf(const char* fmt, ...)
{
  char* str_pointer;
  int error;
  va_list ap;

  va_start(ap, fmt);
  error = my_vasprintf(&str_pointer, fmt, ap);
  va_end(ap);

  return error < 0 ? NULL : str_pointer;
}

/*
* @function		latex_frac		
* @discussion	a recursive Latex continued fraction converter.
*				This function models the problem as a binary tree which tries to solve left and right branches 
* @param		int n as input levels of continued fraction
* @param		int depth as current depth of binary tree
* @param		int val as integer value of numerator and denominator 
* @return		This function returns a formatted string 
*/

char* latex_frac(int n, int depth, int val)
{
  if (depth == n)
    return strdup_printf("%d", val); // Base case condition
  char* left = latex_frac(n, depth + 1, 2 * val);
  char* right = latex_frac(n, depth + 1, 2 * val + 1);
  char* ret = strdup_printf("%d+\\frac{%s}{%s}", val, left, right);
  
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

