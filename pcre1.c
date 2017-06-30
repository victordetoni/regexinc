#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pcre.h>

/* code copied from https://stackoverflow.com/questions/21649423/linux-c-libpcre-output-unique-results
/
/ compile: gcc pcre1.c -o pcre1 -lpcre
/
*/

int main() {
  pcre *myregexp;
  const char *error;
  int erroroffset;
  int offsetcount;
  int offsets[(0+1)*3]; // (max_capturing_groups+1)*3
  const char *result;
  char *subject = "dskjdskajdasdsakdjskjdsadsadsakdhk";
  myregexp = pcre_compile("([a-z]+)", PCRE_MULTILINE|PCRE_DOTALL|PCRE_NEWLINE_ANYCRLF, &error, &erroroffset, NULL);

  if (myregexp != NULL) {
    	offsetcount = pcre_exec(myregexp, NULL, subject, strlen(subject), 0, 0, offsets, (0+1)*3);

    printf("offsetcount=%d\n",offsetcount);

    while (offsetcount > 0) {

      if (pcre_get_substring(subject, offsets, offsetcount, 0, &result) >= 0) {
        printf("%s\n", result);
      }

      offsetcount = pcre_exec(myregexp, NULL, subject, strlen(subject), offsets[1], 0, offsets, (0+1)*3);
    }

  } else {
      printf("Syntax error in REGEX at erroroffset\n");
  }

}
