#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME 50+1
#define ID 16+1
#define DATE 10+1
#define MAX_R 255+1


typedef struct employee {
    char *name;
    char id[ID];
    char date[DATE];
    int salary;
    struct employee *right;
    struct employee *left;
}Employee;

Employee *read_file(char *, Employee *);
void write(char *, char*, Employee *);
int main(int argc, char *argv[])
{
    if(argc!=4){
        printf(stderr, "Incorrect number of arguments.\n");
        exit(EXIT_FAILURE);
    }
    Employee *tmp1, *tmp2;
    Employee *head = NULL;
    head = read_file(argv[1], head);
    write(argv[2], argv[3], head);

    tmp1 = head;
    while (tmp1!=NULL) {
        free (tmp1->name);
        tmp2 = tmp1->right;
        free (tmp1);
        tmp1 = tmp2;
    }

    return;
}

Employee *read_file(char *fname, Employee *head){
    Employee *tmp;
    char name[NAME], id[ID];

    FILE *fp=fopen(fname, "r");
    if(fp==NULL){
        printf(stderr,"Cannot open the file.\n");
        return head;
    }

    /*while(fscanf(fp, "%s%s%s%d", name, tmp->id, tmp->date, &tmp->salary)!=EOF){
        tmp = (Employee*)malloc(sizeof(Employee));
        if (tmp == NULL){
            printf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        tmp->name = (char *) malloc ((strlen(name)+1)*sizeof(char));
        if (tmp->name == NULL){
            printf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        sprintf (tmp->name, "%s", name);
       // strcpy(tmp->id, id);
        tmp->right = head;
        tmp->left = NULL;
        if(head != NULL){
            head->left = tmp;
        }
        head = tmp;
        printf("%s %s %s %d\n", tmp->name, tmp->id, tmp->date, tmp->salary);
    }
    */char riga[MAX_R];
    while (fgets(riga, MAX_R, fp)!=NULL){
    tmp = (Employee *) malloc (sizeof (Employee));
    if (tmp==NULL){
      printf("Allocation Error.\n");
      exit (EXIT_FAILURE);
    }
    sscanf(riga, "%s %s %s %d", name, id, tmp->date, &tmp->salary);
    tmp->name=strdup(name);
     if (tmp->name == NULL){
            printf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
    strcpy(tmp->id, id);
    tmp->right = head;
    tmp->left = NULL;
    if (head!=NULL) {
      head->left = tmp;
    }
    head = tmp;
    //printf("%s %s %s %d\n", tmp->name, tmp->id, tmp->date, tmp->salary);
  }
    fclose(fp);
    return head;
}
void write(char *name, char *command, Employee *head){
  Employee *tmpPtr;
  int i;

  for (tmpPtr=head; tmpPtr!=NULL; tmpPtr=tmpPtr->right) {
    if (strcmp(tmpPtr->name, name) == 0 ) {
      break;
    }
  }

  if (tmpPtr==NULL) {
    return;
  }

  fprintf (stdout, "%s %s %s %d\n",
    tmpPtr->name, tmpPtr->id, tmpPtr->date, tmpPtr->salary);

  for (i=0; i<strlen(command); i++) {
    if (command[i] == '+') {
      if (tmpPtr->right!=NULL) {
        tmpPtr = tmpPtr->right;
      }
    } else {
      if (tmpPtr->left!=NULL) {
        tmpPtr = tmpPtr->left;
      }
    }
    fprintf (stdout, "%s %s %s %d\n",
      tmpPtr->name, tmpPtr->id, tmpPtr->date, tmpPtr->salary);
  }

  return;
}
