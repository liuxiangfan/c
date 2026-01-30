#include <stdbool.h>   /* C99 only */
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

/* external variables */
char contents[STACK_SIZE];
int top = 0;


void stack_overflow(void)
{
  printf("Stack overflow\n");
  exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
  printf("Stack underflow\n");
  exit(EXIT_FAILURE);
}


void make_empty(void)
{
  top = 0;
}

bool is_empty(void)
{
  return top == 0;
}

bool is_full(void)
{
  return top == STACK_SIZE;
}

void push(char ch)
{
  if (is_full())
    stack_overflow();
  else
    contents[top++] = ch;
}

char pop(void)
{
  if (is_empty())
    stack_underflow();
  else
    return contents[--top];

  return '\0'; /* prevents compiler warning due to stack_underflow() call */
}


int main(void)
{
    bool flag=true;
    char line[100];
    printf("Enter parentheses and/or braces:");
    if (fgets(line, sizeof(line), stdin) == NULL)
        return 0;
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    make_empty();
	for(int i=0;line[i]!='\0';i++)
    {
        char ch=line[i];
        if(ch=='('||ch=='{')
        {
            push(ch);
        }
        else if(ch==')'||ch=='}')
        {
            if(is_empty())
            {
                flag=false;
                break;
            }
            char match=pop();
            if((match=='('&&ch==')')||(match=='('&&ch==')'))
            {
                flag=true;
            }
            else
            {
                flag=false;
                break;
            }
        }         
    }
    if(flag)
        printf("Parentheses/braces are NOT nested properly\n");
    else
        printf("Parentheses/braces are nested properly\n"); 
    return 0;
}
