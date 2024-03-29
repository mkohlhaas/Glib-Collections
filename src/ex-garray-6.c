#include <glib.h>
#include <stdio.h>

void prt(GArray *a) {
  printf("Array holds: ");
  for (int i = 0; i < a->len; i++)
    printf("%d ", g_array_index(a, int, i));
  printf("\n");
}

int compare_ints(gpointer a, gpointer b) {
  int *x = (int *)a;
  int *y = (int *)b;
  return *x - *y;
}

int main(void) {
  GArray *a = g_array_new(FALSE, FALSE, sizeof(int));
  int x[6] = {2, 1, 6, 5, 4, 3};
  g_array_append_vals(a, &x, 6);
  prt(a);
  printf("Sorting\n");
  g_array_sort(a, (GCompareFunc)compare_ints);
  prt(a);
  g_array_free(a, FALSE);
}
