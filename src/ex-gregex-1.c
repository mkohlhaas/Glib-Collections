#include <glib.h>
#include <stdio.h>
#include <string.h>

// https://developer-old.gnome.org/glib/stable/glib-regex-syntax.html

int main(void) {
  const char *regPattern = "^(?<Name>[a-zA-Z0-9_\\-\\.]+)@(?<SLD>[a-zA-Z0-9_]+).(?<TLD>[a-zA-Z]{2,5})$";
  printf("Regex pattern: %s\n", regPattern);
  GRegex *reg = g_regex_new(regPattern, G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT, NULL);
  if (!reg) {
    fprintf(stderr, "Couldn't create regular expression!\n");
  }
  printf("Escaped regex pattern: %s\n", g_regex_escape_string(regPattern, strlen(regPattern)));
  printf("Number of backreferences: %d\n", g_regex_get_max_backref(reg));
  printf("Number of captures: %d\n", g_regex_get_capture_count(reg));
  printf("Contains CR/LF: %s\n", g_regex_get_has_cr_or_lf(reg) ? "true" : "false");
  printf("Number of 'Name' subexpression: %d\n", g_regex_get_string_number(reg, "Name"));
  printf("Number of 'Second Level Domain' subexpression: %d\n", g_regex_get_string_number(reg, "SLD"));
  printf("Number of 'Top Level Domain' subexpression: %d\n", g_regex_get_string_number(reg, "TLD"));

  // simple matches
  const char *emailAddress1 = "Michael@example.com";
  printf("%s matches: %s\n", emailAddress1,
         g_regex_match_simple(regPattern, emailAddress1, G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT) ? "true" : "false");

  const char *emailAddress2 = "Michael.Kohlhaas@example.com";
  printf("%s matches: %s\n", emailAddress2,
         g_regex_match_simple(regPattern, emailAddress2, G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT) ? "true" : "false");

  const char *emailAddress3 = "Michael-Kohlhaas@example.com";
  printf("%s matches: %s\n", emailAddress3,
         g_regex_match_simple(regPattern, emailAddress3, G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT) ? "true" : "false");

  const char *emailAddress4 = "Michael_Kohlhaas@example.com";
  printf("%s matches: %s\n", emailAddress4,
         g_regex_match_simple(regPattern, emailAddress4, G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT) ? "true" : "false");

  const char *emailAddress5 = "Michael,Kohlhaas@example.com";
  printf("%s matches: %s\n", emailAddress5,
         g_regex_match_simple(regPattern, emailAddress5, G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT) ? "true" : "false");

  // matching
  printf("=============== Matching ====================\n");
  GMatchInfo *matchInfo;
  g_regex_match(reg, emailAddress2, G_REGEX_MATCH_ANCHORED, &matchInfo);
  while (g_match_info_matches(matchInfo)) {
    gchar *emailAddress = g_match_info_fetch(matchInfo, 0);
    gchar *name = g_match_info_fetch(matchInfo, 1);
    gchar *sld = g_match_info_fetch(matchInfo, 2);
    gchar *tld = g_match_info_fetch(matchInfo, 3);
    g_print("Email Address: %s\nName: %s\nSLD: %s\nTLD: %s\n", emailAddress, name, sld, tld);
    g_free(emailAddress);
    g_free(name);
    g_free(sld);
    g_free(tld);
    g_match_info_next(matchInfo, NULL);
  }
  g_match_info_free(matchInfo);
  g_regex_unref(reg);

  // simple splits
  printf("============= Simple Splits =================\n");
  gchar **parts = g_regex_split_simple(", *", "first, second,  third,  fourth", G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT);
  gchar **partsCpy = parts;
  while (*parts) {
    printf("%s\n", *parts++);
  }
  g_strfreev(partsCpy);

  printf("---------------------------------------------\n");
  parts = g_regex_split_simple("/", "4/5/6", G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT);
  partsCpy = parts;
  while (*parts) {
    printf("%s\n", *parts++);
  }
  g_strfreev(partsCpy);

  printf("---------------------------------------------\n");
  parts = g_regex_split_simple("/", "4//6", G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT);
  partsCpy = parts;
  while (*parts) {
    printf("%s\n", *parts++);
  }
  g_strfreev(partsCpy);

  // splits
  printf("================ Splits =====================\n");
  reg = g_regex_new(", *", G_REGEX_DEFAULT, G_REGEX_MATCH_DEFAULT, NULL);
  parts = g_regex_split(reg, "first, second,  third,  fourth", G_REGEX_MATCH_DEFAULT);
  partsCpy = parts;
  while (*parts) {
    printf("%s\n", *parts++);
  }
  g_strfreev(partsCpy);
}
