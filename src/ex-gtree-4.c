#include <glib.h>
#include <stdio.h>

gboolean iter_all(gpointer key, gpointer value, gpointer data) {
  printf("%s, %s\n", (char *)key, (char *)value);
  return FALSE;
}

gboolean iter_some(gpointer key, gpointer value, gpointer data) {
  printf("%s, %s\n", (char *)key, (char *)value);
  return g_ascii_strcasecmp(key, "b") == 0;
}
int main(void) {
  GTree *t = g_tree_new((GCompareFunc)g_ascii_strcasecmp);
  g_tree_insert(t, "d", "Detroit");
  g_tree_insert(t, "a", "Atlanta");
  g_tree_insert(t, "c", "Chicago");
  g_tree_insert(t, "b", "Boston");
  printf("Iterating all nodes\n");
  g_tree_foreach(t, (GTraverseFunc)iter_all, NULL);
  printf("Iterating some of the nodes\n");
  g_tree_foreach(t, (GTraverseFunc)iter_some, NULL);
  g_tree_destroy(t);
}
