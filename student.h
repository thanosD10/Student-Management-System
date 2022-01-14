#ifndef STUDENT_H
#define STUDENT_H

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

//CREATES A NEW LIST.
list create_list();

//CHECKS IF FILE EXIST. EXIST = 1 / DO NOT EXIST = 0.
int file_exists(char*);

//LOADS DATA FROM FILE.
list load(char*);

//PRINTS MENU WITH OPTIONS TO USER.
void printMenu();

//ADDS A NEW STUDENT TO SYSTEM.
int addStudent(student, list);

//SEARCHES THE SYSTEM FOR A REGISTERED STUDENT.
//IF STUDENT EXISTS RETURS THE STUDENT DATA ELSE RETURNS 0.
student findStudent(int, list);

//DELETES FROM THE SYSTEM A REGISTERED STUDENT.
int deleteStudent(student, list);

//PRINTS TO THE USER A REGISTERED TO THE SYSTEM STUDENT.
void print(student);

//CHANGES DATA FOR A REGISTERED TO THE SYSTEM STUDENT.
int updateStudent(student, list);

//SAME FUNCTION AS 'deleteStudent' BUT WITHOUT MESSEGES.
//USED SPECIFICALLY FOR THE FUNCTION 'listIDclassification'.
int classificationDeleteStudent(student, list);

//SORTS REGISTERED TO THE SYSTEM STUDENTS BY ID (IN ASCENDING ORDER).
list listIDclassification(list);

//PRINTS ALL THE STUDENTS WHO ARE REGISTERED IN THE SYSTEM.
void printstudents(list);

//SAVES ALL THE DATA TO FILE.
void save(char*, list);

//DESTROYS A LIST.
void list_destroy(list);

#endif