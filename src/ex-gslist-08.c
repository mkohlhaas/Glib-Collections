#include <glib.h>
#include <stdio.h>

void print_iterator(gpointer item, gpointer prefix) {
  printf("%s %s\n", (char *)prefix, (char *)item);
}

void print_iterator_short(gpointer item) { printf("%s\n", (char *)item); }

int main(void) {
  GSList *list = g_slist_append(NULL, g_strdup("first"));
  list = g_slist_append(list, g_strdup("second"));
  list = g_slist_append(list, g_strdup("third"));
  printf("Iterating with a function:\n");
  g_slist_foreach(list, print_iterator, "‑‑>");
  printf("Iterating with a shorter function:\n");
  g_slist_foreach(list, (GFunc)print_iterator_short, NULL);
  printf("Now freeing each item\n");
  g_slist_foreach(list, (GFunc)g_free, NULL);
  g_slist_free(list);
}
