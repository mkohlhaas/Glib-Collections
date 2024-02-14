#include <glib.h>
#include <stdio.h>

int main(void) {
  GList *list = NULL;
  list = g_list_append(list, "Hello World!");
  printf("The first item is '%s'\n", (char *)g_list_first(list)->data);
}
