
#include <stdio.h>
#include <stdlib.h>

static int buffer_size = 30000;

void execute_atom(int *current_ptr, char *buffer, char command);
void repeat(char *str, char *buffer, int *ptr);

char *delete_spaces(char *str)
{
  int i = 0;
  int j = 0;
  char *output;
  while(str[i] != '\0')
    {
      i++;
    }
  output = malloc(i);
  if(output != NULL)
    {
      i = 0;
      j = 0;
      while(str[i] != '\0')
	{
	  if(str[i] != ' ')
	    {
	      output[j] = str[i];
	      j++;
	    }
	  i++;
	}
      output[j] = '\0';
      return (output);
    }
  return NULL;
}

void repeat(char *str, char *buffer, int *ptr)
{
  int i = 0;
  
  while(buffer[*ptr] != 0)
    {
      i = 0;
      while(str[i] != '\0')
	{
	  execute_atom(ptr, buffer, str[i]);
	  i++;
	}
    }
}

void parse(char *str)
{
  int i = 0;
  int pointer = 0;
  char buff[buffer_size];
  
  while(pointer < buffer_size)
    {
      buff[pointer] = 0;
      pointer++;
    }
  pointer = 0;
  while(str[i] != '\0')
    {
      if(str[i] == '[')
	{
	  int j = i;
	  while(str[j] != ']')
	    j++;
	  j -=i;
	  char temp[j]; //I know about dynamic arrays and
	                //about many difference string func, but it isn't for us
	  j = i;
	  while(str[j] != ']')
	    {
	      temp[j - i] = str[j];
	      j++;
	    }
	  i = j;
	  repeat(temp, buff, &pointer);
	}
      execute_atom(&pointer, buff, str[i]);
      i++;
    }
}

void execute_atom(int *current_ptr, char *buffer, char command)
{
  switch(command)
    {
    case '>':
      *current_ptr = *current_ptr + 1;
      break;
    case '<':
      *current_ptr = *current_ptr - 1;
      break;
    case '+':
      buffer[*current_ptr]++;
      break;
    case '-':
      buffer[*current_ptr]--;
      break;
    case '.':
      putchar(buffer[*current_ptr]);
      break;
    case ',':
      buffer[*current_ptr] = getchar();
      break;
    }
}

int symb_counter(FILE *fd)
{
  int i;

  i = 0;
  while (getc(fd) != EOF)
    {
      fseek(fd, i, 0);
      i++;
    }
  return (i);
}

int main(int argc, char **argv)
{
  if(argc == 2)
    {
      FILE *d = fopen(argv[1], "r");
      if(d != NULL)
	{
	  unsigned int size = symb_counter(d);
	  char *pr = malloc(size);
	  if(pr)
	    {
	      fseek(d, 0, SEEK_SET);
	      fread(pr, 1, size, d);
	    }
	  pr = delete_spaces(pr);
	  parse(pr);
	}
    }
  return (0);
}
