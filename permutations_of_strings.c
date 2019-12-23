#include "c_headers.h"

void swap(char **s, int p1, int p2)
{
  char *tmp = s[p1];
  s[p1] = s[p2];
  s[p2] = tmp;
}

int lt(char * lhs, char * rhs)
{
  int l_sz, r_sz;
  l_sz = strlen(lhs);
  r_sz = strlen(rhs);

  int i;
  for (i = 0; i < l_sz && i < r_sz; ++i) {
      if(lhs[i] == rhs[i]) continue;
      if(lhs[i] < rhs[i]) return 1;
      else return 0;
  }
  return l_sz < r_sz;
}
int find_next_largest_val(char **s, int n, int k, int i)
{
  int l;
  for (l = i; i < n; ++i)
    if(lt(s[k],s[i]))
      l = i;

  return l;
}
void reverse(char **s, int from, int to)
{
  if(from < to) {
    swap(s,from, to);
    reverse(s, from + 1, to - 1);
  }
}
int next_permutation(int n, char **s)
{
  int i, k, l, had_next_perm = 0;
  for (i = n-1; i > 0; --i) {
    if(lt(s[i-1],s[i]) && !had_next_perm) {
        k = i-1;
        l = find_next_largest_val(s,n,k,k+1);
        swap(s,k,l);
        reverse(s,k+1,n-1);
        had_next_perm = 1;
    }
  }
  return had_next_perm;
}

int main()
{
  char **s;
  int n;
  scanf("%d", &n);
  s = calloc(n, sizeof(char*));
  for (int i = 0; i < n; i++)
  {
    s[i] = calloc(11, sizeof(char));
    scanf("%s", s[i]);
  }
  do
  {
    for (int i = 0; i < n; i++)
      printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
  } while (next_permutation(n, s));
  for (int i = 0; i < n; i++)
    free(s[i]);
  free(s);
  return 0;
}
