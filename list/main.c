#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* STRUCTS
*/
struct Date
{
  int day;
  int month;
};

struct Contact
{
  char name[30];
  char telephone[15];
  char cellphone[15];
  char email[40];
  struct Date birthDate;
};

struct Element
{
  struct Contact info;
  struct Element* next;
};

/*
* PROTOTYPES
*/
void printMenu();
struct Element* insertValue(struct Element* list);
struct Element* findSpecificValue(struct Element* list, char searchParam[30]);
void removeSpecificNode(struct Element* list, char searchParam[30]);
void updateSpecificNode(struct Element* list, char searchParam[30]);

/*
* MAIN
*/
int main(void)
{
  struct Element *contactList = NULL;
  int userInputOptionMenu     = 1;

  do{
    int index                   = 0;
    char userInputForSearch[30];

    printMenu();
    scanf("%d", &userInputOptionMenu);

    switch(userInputOptionMenu){
      case 1:
        contactList = insertValue(contactList);
        break;
      case 2:
        printf("Informe o nome do contato a ser buscado: ");
        scanf("%s", userInputForSearch);

        findSpecificValue(contactList, userInputForSearch);
        break;
      case 3:
        printf("Informe o nome do contato a ser buscado: ");
        scanf("%s", userInputForSearch);
        
        removeSpecificNode(contactList, userInputForSearch);
        break;
      case 4:
        printf("Informe o nome do contato a ser buscado: ");
        scanf("%s", userInputForSearch);

        updateSpecificNode(contactList, userInputForSearch);
        break;
      case 5:
        if(contactList == NULL) break;

        free(contactList);
        break;
      case 0:
        exit(0);
        break;
      default:
        printf("Opção inválida");
        break;
    }
  }while(userInputOptionMenu != 0);
}

/*
* FUNCTIONS
*/
void printMenu()
{
  printf("\n1 - Cadastrar contato\n2 - Buscar contato\n3 - Apagar contato\n4 - Atualizar contato\n5 - Zerar agenda\n0 - Finalizar programa\n->");
}

struct Element* insertValue(struct Element* list)
{
  struct Element *internalList = (struct Element *)calloc(1, sizeof(struct Element));
  if(internalList == NULL)
  {
    printf("Falha ao alocar memória");
    exit(1);
  }

  char contactName[30];
  char contactTelephone[15];
  char contactCellphone[15];
  char contactEmail[40];

  int birthDay  = 0;
  int birthMont = 0;

  printf("Insira o nome do contato: ");
  scanf("%s", contactName);

  if(findSpecificValue(list, contactName))
  {
    printf("Contato duplicado, operação não completada");
    return NULL;
  }

  printf("Insira o email do contato: ");
  scanf("%s", contactEmail);

  printf("Insira o telefone do contato: ");
  scanf("%s", contactTelephone);

  printf("Insira o celular do contato: ");
  scanf("%s", contactCellphone);

  printf("Insira o dia de nascimento do contato: ");
  scanf("%d", &birthDay);

  printf("Insira o mes de nascimento do contato: ");
  scanf("%d", &birthMont);

  strcpy(internalList->info.name,      contactName);
  strcpy(internalList->info.telephone, contactTelephone);
  strcpy(internalList->info.cellphone, contactCellphone);
  strcpy(internalList->info.email,     contactEmail);

  internalList->info.birthDate.day   = birthDay;
  internalList->info.birthDate.month = birthMont;

  internalList->next = list;

  return internalList;
}

struct Element* findSpecificValue(struct Element *list, char searchParam[30])
{
  struct Element *aux = NULL;
  if(list == NULL)
  {
    printf("Lista vazia");
    return 0;
  }

  aux = list;

  while(aux != NULL)
  {
    if(strcmp(aux->info.name, searchParam) == 0) 
    {
      printf("Nome:     %s\n", aux->info.name);
      printf("Email:    %s\n", aux->info.email);
      printf("Telefone: %s\n", aux->info.telephone);
      printf("Celular:  %s\n", aux->info.cellphone);

      printf("\nAniversario: %d/%d\n", aux->info.birthDate.day, aux->info.birthDate.month);

      return aux;
    }
    else                                         aux = aux->next;
  }

  printf("Contato não encontrado");
  return NULL;
}

void removeSpecificNode(struct Element* list, char searchParam[30])
{
  struct Element *aux = NULL;

  if(list == NULL)
  {
    printf("A lista está vazia.");
    return;
  }

  aux = findSpecificValue(list, searchParam);

  if(aux == NULL)
  {
    printf("O item informado não foi encontrado.");
    return;
  }

  printf("O contato %s foi deletado\n", aux->info.name);

  free(aux);
}

void updateSpecificNode(struct Element* list, char searchParam[30])
{
  struct Element *aux = NULL;

  if(list == NULL)
  {
    printf("A lista está vazia.");
    return;
  }

  aux = findSpecificValue(list, searchParam);

  if(aux == NULL)
  {
    printf("O item informado não foi encontrado.");
    return;
  }

  char oldContactName[30];
  strcpy(oldContactName, aux->info.name);

  char contactName[30];
  char contactTelephone[15];
  char contactCellphone[15];
  char contactEmail[40];

  int birthDay  = 0;
  int birthMont = 0;

  printf("Insira o nome do contato: ");
  scanf("%s", contactName);

  printf("Insira o email do contato: ");
  scanf("%s", contactEmail);

  printf("Insira o telefone do contato: ");
  scanf("%s", contactTelephone);

  printf("Insira o celular do contato: ");
  scanf("%s", contactCellphone);

  printf("Insira o dia de nascimento do contato: ");
  scanf("%d", &birthDay);

  printf("Insira o mes de nascimento do contato: ");
  scanf("%d", &birthMont);

  strcpy(aux->info.name,      contactName);
  strcpy(aux->info.telephone, contactTelephone);
  strcpy(aux->info.cellphone, contactCellphone);
  strcpy(aux->info.email,     contactEmail);

  aux->info.birthDate.day   = birthDay;
  aux->info.birthDate.month = birthMont;

  printf("O contato %s foi atualizado para %s\n", oldContactName, aux->info.name);

  aux = findSpecificValue(list, aux->info.name); 
}

