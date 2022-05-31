#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pile
{
  char character;
  struct Pile *next;
};

struct Pile* stack(struct Pile *pile, char value);
struct Pile* unstack(struct Pile **pile);
void swap(char phraseArray[]);

int main(void)
{
  char phraseToSwap[50] = {"ESTE EXERCICIO E MUITO FACIL."};

  swap(phraseToSwap);
}

struct Pile* stack(struct Pile *pile, char value)
{
  struct Pile *newPile = calloc(1, sizeof(struct Pile));
  
  if(newPile == NULL)
  {
    printf("Falha ao alocar memoria");
    exit(1);
  }

  newPile->character = value;
  newPile->next      = pile;

  return newPile;
}

struct Pile* unstack(struct Pile **pile)
{
  struct Pile *remove = NULL;

  if(*pile == NULL)
  {
    printf("Pilha vazia");
    
    return remove;
  }

  remove = *pile;
  *pile  = remove->next;

  return remove;
}

void swap(char phraseArray[])
{
  struct Pile *remove = NULL;
  struct Pile *pile   = NULL;

  int arrayLength = strlen(phraseArray);
  int index       = 0;

  if(phraseArray[arrayLength - 1] != '.') return;

  while(phraseArray[index] != '\0')
  {
    if(phraseArray[index] != ' ') pile = stack(pile, phraseArray[index]);
    else
    {
      while(pile)
      {
        remove = unstack(&pile);
        printf("%c", remove->character);

        free(remove);
      }

      printf(" ");
    }

    index++;
  }

  while(pile)
  {
    remove = unstack(&pile);

    if(remove->character == '.')
    {
      free(remove);
      continue;
    }

    printf("%c", remove->character);

    if(remove->next == NULL)
    {
      pile = stack(pile, phraseArray[arrayLength - 1]);

      remove = unstack(&pile);

      printf("%c", remove->character);
    }

    free(remove);
  }

  printf("\n");
}

