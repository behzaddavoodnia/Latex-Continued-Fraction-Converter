import sys

def latex_frac(n, depth, val):
  if depth == n:
    return str(val);
  left = latex_frac(n, depth + 1, 2 * val);
  right = latex_frac(n, depth + 1, 2 * val + 1);
  return '%d+\\frac{%s}{%s}' % (val, left, right)

print('\\documentclass{article}\n\\begin{document}\n\\begin{equation}')
print(latex_frac(int(sys.argv[1]), 1, 1))
print('\\end{equation}\n\\end{document}')

