#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HOW_MANY_BOOK_HAS 1
#define BOOK_NAME_SIZE 30
#define QUEUE_PERSON_NAME_SIZE 50
#define QUEUE_SIZE 100

struct sBookQueue
{
  char name[QUEUE_PERSON_NAME_SIZE];
};

struct sBook
{
  char name[BOOK_NAME_SIZE];
  bool disponibility;
  struct sBookQueue *queue;
  int rear;
  int front;
};

void scanBookList(struct sBook *bookList);
void printBookList(struct sBook *bookList);
void printMenu();
void requestBook(struct sBook *bookList, int requestIndex);
void giveBackBook(struct sBook *bookList, int bookIndex);

int main(void)
{
  struct sBook *bookList = calloc(HOW_MANY_BOOK_HAS, sizeof(struct sBook));

  int userInputOptionMenu = 1;

  scanBookList(bookList);

  do{
    int index = 0;

    printMenu();
    scanf("%d", &userInputOptionMenu);

    switch(userInputOptionMenu){
      case 1:
        printBookList(bookList);
        break;
      case 2:
        printf("Qual o ID do livro que você deseja requisitar?");
        scanf("%d", &index);

        requestBook(bookList, index);
        break;

      case 3:
        printf("Qual o ID do livro que você deseja requisitar?");
        scanf("%d", &index);

        giveBackBook(bookList, index);
        break;
      case 0:
        exit(0);
        break;
      default:
        printf("Opção inválida");
        break;
    }
  }while(userInputOptionMenu != 0);

  return 0;
}

void scanBookList(struct sBook *bookList)
{
  printf("Registro de livros\n\n");

  for(int i = 0; i < HOW_MANY_BOOK_HAS; i++)
  {
    int disponibility = 0;

    printf("Nome do livro: ");
    scanf("%s", bookList[i].name);

    bookList[i].disponibility = true;

    bookList[i].rear  = -1;
    bookList[i].front = -1;

    struct sBookQueue *bookQueue = calloc(QUEUE_SIZE, sizeof(struct sBookQueue));

    bookList[i].queue = bookQueue;
  }
}

void printBookList(struct sBook *bookList)
{
  for(int i = 0; i < HOW_MANY_BOOK_HAS; i++)
  {
    printf("\nID do livro:     %d\n", i + 1);
    printf("Nome do livro:   %s\n", bookList[i].name);
    printf("Disponibilidade: %d\n", bookList[i].disponibility);
    
    for(int j = 0; j < QUEUE_SIZE; j++)
    {
      if(strlen(bookList[i].queue[j].name) != 0)
        printf("Fila de espera:  %s\n", bookList[i].queue[j].name);
    }
  }
}

void printMenu()
{
  printf("\n1 - Listar livros\n2 - Requisitar livro\n3 - Devolver livro\n0 - Finalizar programa\n->");
}

void giveBackBook(struct sBook *bookList, int bookIndex)
{
  bookIndex = bookIndex - 1;
  printf("\nID do livro:     %d\n", bookIndex + 1);
  printf("Nome do livro:   %s\n", bookList[bookIndex].name);
  printf("Disponibilidade: %d\n", bookList[bookIndex].disponibility);

  if(bookList[bookIndex].disponibility == 1)
  {
    printf("O livro não havia sido emprestado");
    return;
  }

  if(strlen(bookList[bookIndex].queue[bookList[bookIndex].front].name) == 0)
  {
    printf("Não há fila de espera");
    bookList[bookIndex].disponibility = true;
    return;
  }

  if(bookList[bookIndex].front == QUEUE_SIZE){
    bookList[bookIndex].front = 0;
    bookList[bookIndex].rear  = -1;
  }

  printf("Livro [%s] devolvido, próximo a receber o livro emprestado: [%s]", bookList[bookIndex].name, bookList[bookIndex].queue[bookList[bookIndex].front].name);

  bookList[bookIndex].front = bookList[bookIndex].front + 1;
}

void requestBook(struct sBook *bookList, int requestIndex)
{
  requestIndex = requestIndex - 1;
  printf("\nID do livro:     %d\n", requestIndex + 1);
  printf("Nome do livro:   %s\n", bookList[requestIndex].name);
  printf("Disponibilidade: %d\n", bookList[requestIndex].disponibility);

  for(int i = 0; i < QUEUE_SIZE; i++)
  {
    if(strlen(bookList[requestIndex].queue[i].name) != 0)
      printf("Fila de espera:  %s\n", bookList[requestIndex].queue[i].name);
  }

  if(bookList[requestIndex].disponibility == 1)
  {
    printf("Livro [%s] de ID [%d] foi retirado", bookList[requestIndex].name, requestIndex);
    bookList[requestIndex].disponibility = false;
  }else{
    char lastInBookQueue[QUEUE_PERSON_NAME_SIZE];

    printf("Insira o nome para a lista de espera: ");
    scanf("%s", lastInBookQueue);

    for(int i = 0; i < QUEUE_SIZE; i++)
    {
      if(strlen(bookList[requestIndex].queue[i].name) == 0){
        if(bookList[requestIndex].front == -1)
          bookList[requestIndex].front = 0;

        bookList[requestIndex].rear = bookList[requestIndex].rear + 1;

        strcpy(bookList[requestIndex].queue[bookList[requestIndex].rear].name, lastInBookQueue);
        printf("[%s] está na posição da fila [%d] para o livro [%s]", lastInBookQueue, i + 1, bookList[requestIndex].name);
        return;
      }
    }
  }
}

