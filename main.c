#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.c"

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
                printf("\n-------------------------------------------------------\n");
                printf("Found student:\n");
                print(studentSearch);
                printf("-------------------------------------------------------\n");
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
                if(updateStudent(studentChangeData, studentsList) == 0) {
                    printf("\nCHANGE STUDENT REGISTERED DATA PROCESS stopped...\n");
                } else {
                    printf("\nCHANGE STUDENT REGISTERED DATA PROCESS ended successfully!\n");
                }
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