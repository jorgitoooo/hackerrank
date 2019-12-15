#include "./c_headers.h"

int comparator(const void * a, const void * b)
{
    return (*(int*)a - *(int*)b);
}

int min_abs_diff(int arr_count, int* arr)
{
    qsort(arr, arr_count, sizeof(int), comparator);

    int min_diff = INT_MAX;
    for(int i = 1; i < arr_count; i++) {
        int curr_min = abs(arr[i] - arr[i-1]); 
        min_diff = curr_min < min_diff ? curr_min : min_diff; 
    }

    return min_diff;
}

int main(int argc, char **argv)
{
  const int size0 = 3;
  const int size1 = 10;
  const int size2 = 5;

  int arr0[3] = {3,-7,0};
  int arr1[10] = {-59,-36,-13,1,-53,-92,-2,-96,-54,75};
  int arr2[5] = {1,-3,71,68,17};

  assert(min_abs_diff(size0, arr0) == 3);
  assert(min_abs_diff(size1, arr1) == 1);
  assert(min_abs_diff(size2, arr2) == 3);

  printf("%d\n", min_abs_diff(size0, arr0));
  printf("%d\n", min_abs_diff(size1, arr1));
  printf("%d\n", min_abs_diff(size2, arr2));
  
  return 0;
}
