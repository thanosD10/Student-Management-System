#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRING 50

typedef struct node* student;
struct node{
    char name[MAXSTRING];
    int id;
    struct node* previous;
    struct node* next;
};

typedef struct listS* list;
struct listS {
    struct node* head;
    struct node* tail;
    int size;
};

//CREATES A NEW LIST
list create_list() {
    list newList=(list) malloc(sizeof(struct listS));
    if(newList == NULL) {
        printf("ERROR: NOT ENOUGH MEMORY! ABORTING...");
        abort();
    }
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;

    return newList;
}

int file_exists(char* filename){
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

//LOAD DATA FROM FILE
list load(char* filename) {
    list studentsList = create_list();

    if(file_exists(filename) == 1) {
        FILE* fp = fopen(filename, "r");
        if(fp == NULL) {
            printf("ERROR: FILE COULD NOT BE OPENED FOR DATA LOADING!\n");
            abort();
        }

        fseek(fp, 0, SEEK_END);
        long fileSize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        (int)fileSize;
        if(fileSize != 0) {
            int i = 0;
            while(feof(fp) == 0) {
                student newNode = (student)malloc(sizeof(struct node));
                fscanf(fp, "%s %d\n", newNode->name, &newNode->id);
                newNode->next = NULL;
                if(studentsList->size == 0) {
                    newNode->previous = NULL;
                    studentsList->head = newNode;
                    studentsList->tail = newNode;
                    studentsList->size ++;
                } else {
                    student previousLast = studentsList->tail;
                    newNode->previous = previousLast;
                    previousLast->next = newNode;
                    studentsList->tail = newNode;
                    studentsList->size ++;
                }
                //DELETE
            }
        }
        fclose(fp);
    } else {
        FILE* fp = fopen(filename, "w");
        if(fp == NULL) {
            printf("ERROR: FILE COULD NOT BE OPENED!\n");
            abort();
        }
        fclose(fp);
    }
    return studentsList;
}

//PRINTS MENU
void printMenu() {
    printf("\n--------------------------------------------\n");
    printf("|  MENU OPTIONS:                           |\n");
    printf("| 1. Add a new student                     |\n");
    printf("| 2. Delete a registered student           |\n");
    printf("| 3. Search for a registered student       |\n");
    printf("| 4. Change registered data for a student  |\n");
    printf("| 5. Print all registered students         |\n");
    printf("| 6. Quit                                  |\n");
    printf("--------------------------------------------\n");
    printf("Provide the number of action you want to proceed(1-6):\n");
}

int unique_id(list studentsList, int newid) {
    student curStudent = studentsList->head;

    while(curStudent != NULL) {
        if(newid == curStudent->id) {
            printf("\nERROR: ID ALREADY EXISTS! ");
            printf("Currently belongs to student: %s\n", curStudent->name);
            return 0;
        }
        curStudent = curStudent->next;
    }
    return 1;
}

//1
int addStudent(student addSt, list studentsList) {
    if(studentsList->size == 0) {
        studentsList->head = addSt;
        studentsList->tail = addSt;
        studentsList->size ++;
    } else {
        student previousLast = studentsList->tail;
        previousLast->next = addSt;
        addSt->previous = previousLast;
        studentsList->tail = addSt;
        studentsList->size ++;
    }
}

student findStudent(int searchid, list studentsList) {
    student curStudent = studentsList->head;

    while(curStudent != NULL) {
        if(curStudent->id == searchid) {
            return curStudent;
        }
        curStudent = curStudent->next;
    }
    printf("\nStudent with id: %d does not exist!\n", searchid);
    return 0;
}

//2
int deleteStudent(student deleteSt, list studentsList) {
    student curStudent = studentsList->head;

    if(studentsList->size == 1) {
        printf("\nDELETE STUDENT PROCESS ended successfully!\n");
        printf("Deleted student:\nname: %s   id: %d\n", curStudent->name, curStudent->id);
        free(studentsList);

        studentsList = create_list();
    } else if(studentsList!=NULL && curStudent->id==deleteSt->id) {
        studentsList->head = curStudent->next;

        printf("\nDELETE STUDENT PROCESS ended successfully!\n");
        printf("Deleted student:\nname: %s   id: %d\n", curStudent->name, curStudent->id);
        free(curStudent);
        studentsList->size--;
    } else {
        student prevStudent;
        while(studentsList!=NULL && curStudent->id!=deleteSt->id){
            prevStudent = curStudent;
            curStudent = curStudent->next;
        }
        prevStudent->next = curStudent->next;

        printf("\nDELETE STUDENT PROCESS ended successfully!\n");
        printf("Deleted student:\nname: %s   id: %d\n", curStudent->name, curStudent->id);
        free(curStudent);
        studentsList->size--;
    }
}

//3
void print(student printSt) {
    printf("id: %d   name: %s\n",printSt->id, printSt->name);
}

//4
int updateStudent(student changeDataSt, list studentsList) {
    printf("\n---------------------------------------------\n");
    printf("|  CHANGE REGISTERED STUDENT DATA OPTIONS:    |\n");
    printf("| 1. name                                     |\n");
    printf("| 2. id                                       |\n");
    printf("| 3. name & id                                |\n");
    printf("---------------------------------------------\n");
    printf("Provide the number of action you want to proceed(1, 2 or 3):\n");

    int changeDataAnswer;
    while(scanf("%d",&changeDataAnswer) != 1) {
        printf("\nINVALID NUMBER OF ACTION!\n");
        printf("Provide a valid NUMBER of action to proceed(1, 2 or 3):\n");
        
        getchar();
    }

    int wrongInput;
    if(changeDataAnswer<1 || changeDataAnswer>3) {
        printf("\nINVALID NUMBER OF ACTION!\n");
        printf("Provide a VALID number of action to proceed(1, 2 or 3):\n");
        wrongInput = 1;
    } else {
        wrongInput = 0;
    }

    while(wrongInput == 1) {
        while(scanf("%d",&changeDataAnswer) != 1) {
            printf("\nINVALID NUMBER OF ACTION!\n");
            printf("Provide a valid NUMBER of action to proceed(1, 2 or 3):\n");
        
            getchar();
        }

        if(changeDataAnswer<1 || changeDataAnswer>3) {
            printf("\nINVALID NUMBER OF ACTION!\n");
            printf("Provide a VALID number of action to proceed(1, 2 or 3):\n");
            wrongInput = 1;
        } else {
            wrongInput = 0;
        }
    }

    printf("\n");
    printf("Current registered data:\n");
    print(changeDataSt);
    printf("\n");

    if(changeDataAnswer == 1) {
        printf("Provide a new name:\n");
        char newName[MAXSTRING];
        scanf("%s", newName);

        char oldName[MAXSTRING];
        strcpy(oldName ,changeDataSt->name);
        strcpy(changeDataSt->name, newName);
        printf("ID: %d - name changed from %s to %s\n", changeDataSt->id, oldName, changeDataSt->name);

    } else if(changeDataAnswer == 2) {
        printf("Provide a new unique id:\n");
        int newID;
        while(scanf("%d", &newID) != 1) {
            printf("\nStudent's id must be a NUMBER!\n");
            printf("Provide a new unique id:\n");

            getchar();
        }

        int unique = unique_id(studentsList, newID);
        while(unique != 1) {
            printf("Provide a unique id:\n");

            while(scanf("%d", &newID) != 1) {
                printf("\nStudent's id must be a NUMBER!\n");
                printf("Provide a new unique id:\n");

                getchar();
            }

            unique = unique_id(studentsList, newID);
        }
        int oldID = changeDataSt->id;
        changeDataSt->id = newID;
        printf("NAME: %s - id changed from %d to %d\n", changeDataSt->name, oldID, changeDataSt->id);

    } else {
        printf("Provide a new name:\n");
        char newName[MAXSTRING];
        scanf("%s", newName);

        char oldName[MAXSTRING];
        strcpy(oldName ,changeDataSt->name);
        strcpy(changeDataSt->name, newName);
        printf("\nID: %d - name changed from %s to %s\n", changeDataSt->id, oldName, changeDataSt->name);

        printf("\nProvide a new unique id:\n");
        int newID;
        while(scanf("%d", &newID) != 1) {
            printf("\nStudent's id must be a NUMBER!\n");
            printf("Provide a new unique id:\n");

            getchar();
        }

        int unique = unique_id(studentsList, newID);
        while(unique != 1) {
            printf("Provide a unique id:\n");

            while(scanf("%d", &newID) != 1) {
                printf("\nStudent's id must be a NUMBER!\n");
                printf("Provide a new unique id:\n");

                getchar();
            }

            unique = unique_id(studentsList, newID);
        }
        int oldID = changeDataSt->id;
        changeDataSt->id = newID;
        printf("NAME: %s - id changed from %d to %d\n", changeDataSt->name, oldID, changeDataSt->id);
    }
}

int classificationDeleteStudent(student deleteSt, list studentsList) {
    student curStudent = studentsList->head;

    if(studentsList->size == 1) {
        free(studentsList);

        studentsList = create_list();
    } else if(studentsList!=NULL && curStudent->id==deleteSt->id) {
        studentsList->head = curStudent->next;

        free(curStudent);
        studentsList->size--;
    } else {
        student prevStudent;
        while(studentsList!=NULL && curStudent->id!=deleteSt->id){
            prevStudent = curStudent;
            curStudent = curStudent->next;
        }
        prevStudent->next = curStudent->next;

        free(curStudent);
        studentsList->size--;
    }
}

list listIDclassification(list studentsList) {
    list newStudentsList = (list)malloc(sizeof(struct listS));
    newStudentsList = create_list();

    while(studentsList->size > 0) {
        student curNode = studentsList->head;
        int maxID = -1;
        char* maxName;
        student deleteThisNode;
        while(curNode != NULL) {
            if(curNode->id > maxID) {
                maxID = curNode->id;
                strcpy(maxName, curNode->name);
                deleteThisNode = curNode;
            }
            curNode = curNode->next;
        }

        classificationDeleteStudent(deleteThisNode, studentsList);

        student maxIDnode = (student)malloc(sizeof(struct node));
        strcpy(maxIDnode->name, maxName);
        maxIDnode->id = maxID;
        maxIDnode->next = NULL;
        maxIDnode->previous = NULL;
        addStudent(maxIDnode, newStudentsList); 
    }
    free(studentsList);

    return newStudentsList;
}

//5
void printstudents(list studentsList) {
    student curStudent = studentsList->tail;

    printf("\n\n");
    printf("---------------------------------------------------------\n");
    while(curStudent != NULL) {
        print(curStudent);
        printf("---------------------------------------------------------\n");
        curStudent = curStudent->previous;
    }
    printf("\n\n");
}

void save(char *filename, list studentsList) {
    student curStudent = studentsList->head;

    FILE* fp = fopen(filename, "w");
    if(fp == NULL) {
        printf("ERROR: FILE COULD NOT BE OPENED FOR DATA SAVING!\n");
        abort();
    }

    while(curStudent != NULL) {
        fprintf (fp ,"%s %d\n" , curStudent->name, curStudent->id);
        //fwrite(curStudent->name, sizeof(curStudent->name), 1, fp);
        //fputc(curStudent->id, fp);
        curStudent = curStudent->next;
    }
    fclose(fp);
}

void list_destroy(list studentsList) {
    student curNode = studentsList->head;
    int i = 0;
    while(curNode != NULL) {
        i++;
    student tmpPointer = curNode->next;
    free(curNode);
    curNode = tmpPointer;
    }

    if(i != studentsList->size) {
        printf("ERROR: MEMORY LEAK DETECTED!!!! Freed %d elements from list with size %d\n", i, studentsList->size);
        abort();
    }

    free(studentsList);
}



int main(int argc, char** argv) {

    if(argc != 2) {
        printf("ERROR: USER INPUT!\n");
        return 0;
    }

    printf("\n********************************************************\n");
    printf("*         WELCOME TO STUDENTS MANAGMENT SYSTEM         *\n");
    printf("********************************************************\n\n");

    list studentsList = load(argv[1]);

    int menuAnswer;
    do {
        if(studentsList->size == 0) {
            printf("\n\n\nSYSTEM IS EMPTY!!!\n");
            printf("\n--------------------------------------\n");
            printf("|  MENU OPTIONS:                       |\n");
            printf("| 1. Add a new student                 |\n");
            printf("| 2. Quit                              |\n");
            printf("--------------------------------------\n");
            printf("Provide the number of action you want to proceed(1 or 2):\n");

            int emptyAnswer;
            while(scanf("%d",&emptyAnswer) != 1) {
                printf("\nINVALID NUMBER OF ACTION!\n");
                printf("Provide a valid NUMBER of action to proceed(1 or 2):\n");
            
                getchar();
            }
    
            int wrongInput;
            if(emptyAnswer<1 || emptyAnswer>2) {
                printf("\nINVALID NUMBER OF ACTION!\n");
                printf("Provide a VALID number of action to proceed(1 or 2):\n");
                wrongInput = 1;
            } else {
                wrongInput = 0;
            }
            
            while(wrongInput == 1) {
                while(scanf("%d",&emptyAnswer) != 1) {
                    printf("\nINVALID NUMBER OF ACTION!\n");
                    printf("Provide a valid NUMBER of action to proceed(1 or 2):\n");
                    
                    getchar();
                }

                if(emptyAnswer<1 || emptyAnswer>2) {
                    printf("\nINVALID NUMBER OF ACTION!\n");
                    printf("Provide a VALID number of action to proceed(1 or 2):\n");
                    wrongInput = 1;
                } else {
                    wrongInput = 0;
                }
            }

            if(emptyAnswer == 1) {
                menuAnswer = 1;
            } else {
                menuAnswer = 6;
            }

        } else {
            printMenu();
            while(scanf("%d",&menuAnswer) != 1) {   
                printf("\nINVALID NUMBER OF ACTION!\n");
                printf("Provide a valid NUMBER of action to proceed(1-6):\n");
                
                getchar();
            }

            int wrongInput;
            if(menuAnswer<1 || menuAnswer>6) {
                printf("\nINVALID NUMBER OF ACTION!\n");
                printf("Provide a VALID number of action to proceed(1-6):\n");
                wrongInput = 1;
            } else {
                wrongInput = 0;
            }

            while(wrongInput == 1) {
                while(scanf("%d",&menuAnswer) != 1) {
                    printf("\nINVALID NUMBER OF ACTION!\n");
                    printf("Provide a valid NUMBER of action to proceed(1-6):\n");
                
                    getchar();
                }

                if(menuAnswer<1 || menuAnswer>6) {
                    printf("\nINVALID NUMBER OF ACTION!\n");
                    printf("Provide a VALID number of action to proceed(1-6):\n");
                    wrongInput = 1;
                } else {
                    wrongInput = 0;
                }
            }
        }
        printf("\n\n");

        if(menuAnswer == 1) {
            printf("---| ADD STUDENT PROCESS |---\n\n");

            printf("Provide new student's name:\n");
            char addName[MAXSTRING];
            scanf("%s", addName);
            
            printf("\n");
            printf("Provide a unique id:\n");
            int addID;

            while(scanf("%d", &addID) != 1) {
                printf("\nStudent's id must be a NUMBER!\n");
                printf("Provide a new unique id:\n");

                getchar();
            }

            int unique = unique_id(studentsList, addID);
            while(unique != 1) {
                printf("Provide a unique id:\n");

                while(scanf("%d", &addID) != 1) {
                    printf("\nStudent's id must be a NUMBER!\n");
                    printf("Provide a new unique id:\n");

                    getchar();
                }

                unique = unique_id(studentsList, addID);
            }

            student addSt = (student)malloc(sizeof(struct node));
            strcpy(addSt->name, addName);
            addSt->id = addID;
            addSt->next = NULL;
            addSt->previous = NULL;
            addStudent(addSt, studentsList);

            printf("\nADD STUDENT PROCESS ended successfully!\n");
            printf(" ADDED STUDENT\n name: %s   id: %d\n", addSt->name, addSt->id);

        } else if(menuAnswer == 2) {
            printf("---| DELETE STUDENT PROCESS |---\n\n");

            studentsList = listIDclassification(studentsList);
            printf("\n\n - CURRENT STUDENTS LIST -");
            printstudents(studentsList);

            printf("\nProvide student's id:\n");
            int deleteID;
            while(scanf("%d", &deleteID) != 1) {
                printf("\nStudent's id must be a NUMBER!\n");
                printf("Provide student's id:\n");

                getchar();
            }

            student studentDelete = findStudent(deleteID, studentsList);
            if(studentDelete == 0) {
                printf("DELETE STUDENT PROCESS stopped...\n");
            } else {
                deleteStudent(studentDelete, studentsList);
            }

        } else if(menuAnswer == 3) {
            printf("---| SEARCH STUDENT PROCESS |---\n\n");

            printf("Provide student's id:\n");
            int searchID;

            while(scanf("%d", &searchID) != 1) {
                printf("\nStudent's id must be a NUMBER!\n");
                printf("Provide student's id:\n");

                getchar();
            }

            student studentSearch = findStudent(searchID, studentsList);
            if(studentSearch == 0) {
                printf("SEARCH STUDENT PROCESS stopped...\n");
            } else {
                printf("\nFound student:\n");
                print(studentSearch);
                printf("\nSEARCH STUDENT PROCESS ended successfully!\n");
            }

        } else if(menuAnswer == 4) {
            printf("---| CHANGE STUDENT REGISTERED DATA PROCESS |---\n\n");

            studentsList = listIDclassification(studentsList);
            printf("\n\n - CURRENT STUDENTS LIST -");
            printstudents(studentsList);

            printf("Provide student's id:\n");
            int changeDataID;
            while(scanf("%d", &changeDataID) != 1) {
                printf("\nStudent's id must be a NUMBER!\n");
                printf("Provide student's id:\n");

                getchar();
            }

            student studentChangeData = findStudent(changeDataID, studentsList);
            if(studentChangeData == 0) {
                printf("\nCHANGE STUDENT REGISTERED DATA PROCESS stopped...\n");
            } else {
                updateStudent(studentChangeData, studentsList);
                printf("\nCHANGE STUDENT REGISTERED DATA PROCESS ended successfully!\n");
            }

        } else if(menuAnswer == 5) {
            printf("---| PRINT STUDENTS PROCESS |---");

            studentsList = listIDclassification(studentsList);
            printstudents(studentsList);
            printf("PRINT STUDENTS PROCESS ended successfully!\n");
        }
    } while(menuAnswer != 6);

    studentsList = listIDclassification(studentsList);
    save(argv[1], studentsList);

    list_destroy(studentsList);

    printf("ALL NEW CHANGES HAS BEEN SAVED!\n\n");
    printf("CLOSING SYSTEM...\n");

    return 0;
}