#include "./c_headers.h"

void tokenizer(char *str, char delim)
{
  int i = 0, 
      beg_tok = 0, 
      tok_idx = 0, 
      len = strlen(str), 
      found_whitespace = 0;
  while(i < len) {
    // Conditions met at the beginning of each token
    if(!beg_tok && str[i] != delim) {
      beg_tok = 1;
      found_whitespace = 0;
      tok_idx = i;
    } else if(str[i] == delim) {
      if(beg_tok) {
        printf("%.*s\n",i - tok_idx, &str[tok_idx]);
        beg_tok = 0;
      }
      while(i < len && str[i] == delim) i++;
      found_whitespace = 1;
      tok_idx = i;
    }
    if(!found_whitespace) i++;
  }

  // Handles case where final token doesn't end with whitespace
  if(tok_idx < i) {
    printf("%.*s\n",i - tok_idx, &str[tok_idx]);
  }

}

int main(int argc, char **argv)
{
  char delim = ' ';
  if(argc > 1) delim = *argv[1];
  tokenizer("Hello ma friends.", delim);
  tokenizer("Hello World!", delim);
  tokenizer("Goodbye World!", delim);

  return 0;
}
