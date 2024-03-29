#include <glib.h>
#include <stdio.h>

gint finder(gpointer a, gpointer b) { return strcmp(a, b); }

int main(void) {
  GQueue *q = g_queue_new();
  g_queue_push_tail(q, "Alice");
  g_queue_push_tail(q, "Bob");
  g_queue_push_tail(q, "Fred");
  g_queue_push_tail(q, "Jim");
  GList *fred_link = g_queue_find(q, "Fred");
  printf("The fred node indeed contains %s\n", (char *)fred_link->data);
  GList *joe_link = g_queue_find(q, "Joe");
  printf("Finding 'Joe' yields a %s link\n", joe_link ? "good" : "null");
  GList *bob = g_queue_find_custom(q, "Bob", (GCompareFunc)finder);
  printf("Custom finder found %s\n", (char *)bob->data);
  bob = g_queue_find_custom(q, "Bob", (GCompareFunc)g_ascii_strcasecmp);
  printf("g_ascii_strcasecmp also found %s\n", (char *)bob->data);
  g_queue_free(q);
}
