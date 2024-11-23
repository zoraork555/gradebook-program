// Ashton Johnson 11797181
// This program supplements the functions that are run throught the interface.c file
// addStudent puts a new student linked list at the head of the list of students
// addGrade adds a new grade at the head of a student's list of grades
// count counts the number of students
// removeGrade removes one grade node from the linked list of grades
// removeStudent removes all grades from a students list and then removes the student from the student list
// printStudent prints a student and all of their grades
// print prints all students with all of their grades respectively
// addGradeOrdered adds a grade in a linked list of a student based on chapter, section, and type sequentially
// addStudentOrdered adds a student to the linked student list alphabetically first based on last name then first name

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gradebook.h"


/////////////////////////////////////////////////////////////////////////////////////////////
// add a student to the list of students
//	   1. Make sure a student by that name does not exist (print an error message and do nothing if it exists)
//	   2. Add a new student with that name (add-at-front)

Student* addStudent(Student *headStudentList, char last[], char first[])
{
  Student *new = malloc(sizeof(Student)); //allocate pointer
  new->lastName = malloc(sizeof(char) * strlen(last)+1); //allocate first name
  strcpy(new->lastName, last);
  new->firstName = malloc(sizeof(char) * strlen(first)+1); //allocate last name
  strcpy(new->firstName, first);
  new->headGradeList = malloc(sizeof(Grade));
  new->headGradeList = NULL;
  new->next = headStudentList;
  if (headStudentList==NULL) return new;
  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    if (strcmp(pointer->lastName, last)==0 && strcmp(pointer->firstName, first)==0) {
      printf("ERROR: Student already exists.\n");
      return headStudentList;
    }
  }
	return new;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// add a grade to the specified student
//   1. Make sure a student by that name exists (so you can add grade to it)
//   2. If the specifed grade already exists, update the grade's value to the new value
//   3. Otherwise, add the grade to the end of the student's grade list (add-at-end)

void addGrade(Student *headStudentList, char last[], char first[], char gradeName[], double value) {
  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    if (strcmp(pointer->lastName, last)==0 && strcmp(pointer->firstName, first)==0) {
      if (pointer->headGradeList==NULL) { //empty list
        Grade *pGrade = malloc(sizeof(Grade));
        strcpy(pGrade->name, gradeName);
        pGrade->value = value;
        pGrade->next = NULL;
        pointer->headGradeList = pGrade;
        return;
      }
      for (Grade *ptr=pointer->headGradeList; ptr!=NULL; ptr=ptr->next) {
        if (strcmp(ptr->name, gradeName)==0) {
          ptr->value = value;
          return;
        }
        if (ptr->next==NULL) {
          Grade *pGrade = malloc(sizeof(Grade));
          strcpy(pGrade->name, gradeName);
          pGrade->value = value;
          pGrade->next = NULL;
          ptr->next = pGrade;
          return;
        }
      }
      /*else { // otherwise
        Grade *pGrade = malloc(sizeof(Grade));
        strcpy(pGrade->name, gradeName);
        pGrade->value = value;
        pGrade->next = pointer->headGradeList;
        pointer->headGradeList = pGrade;
        return;
      }*/
    }
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////
// return the number of students in the list
// Iterate through the student list to count the number of students, return that count

int count(Student *headStudentList) {
  int count=0;
  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    count++;
  }
	return count;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// print all the grades for a given student
//	1. Make sure a student with that name exists
//	2. Print the name of that student
//	3. Print all the "grade name: grade value" pairs for that student

void printStudent(Student *headStudentList, char last[], char first[]) {
  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    if (strcmp(pointer->lastName, last)==0 && strcmp(pointer->firstName, first)==0) {
      printf("Student Name: %s, %s\n", pointer->lastName, pointer->firstName);
      if (pointer->headGradeList==NULL) {
        printf("\tThe student has no grades.\n");
      }
      else for (Grade *ptr=pointer->headGradeList; ptr!=NULL; ptr=ptr->next) {
        printf("\t%s  :  %f\n", ptr->name, ptr->value);
      }
      return;
    }
  }
  printf("ERROR: Student does not exist.\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////
// print all the students
// If the student list is empty, print a message to indicate it.
// Otherwise, for each student
//	   a. Print the name of that student
//	   b. Print all the "grade name: grade value" pairs for that student

void print(Student *headStudentList)
{
  if (headStudentList==NULL) printf("ERROR: There are no students.\n");
  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    printf("Student Name: %s, %s\n", pointer->lastName, pointer->firstName);
    if (pointer->headGradeList==NULL) {
      printf("\tThis student has no grades.\n");
    }
    else for (Grade *ptr=pointer->headGradeList; ptr!=NULL; ptr=ptr->next) {
      printf("\t%s  :  %f\n", ptr->name, ptr->value);
    }
    printf("\n");
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////
// add a student (in alphabetical order)
//	1. Make sure a student by that name does not exist
//	2. Add a student with that name (add-in-order)

Student *addStudentOrdered(Student *headStudentList, char last[], char first[])
{
  //create student location and info
  Student *new = malloc(sizeof(Student)); //allocate pointer
  new->lastName = malloc(sizeof(char) * strlen(last)+1); //allocate first name
  strcpy(new->lastName, last);
  new->firstName = malloc(sizeof(char) * strlen(first)+1); //allocate last name
  strcpy(new->firstName, first);
  new->headGradeList = malloc(sizeof(Grade));
  new->headGradeList = NULL;

  if (headStudentList==NULL) { //empty list
    new->next=NULL;
    return new;
  }

  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) { //make sure student doesn't exist
    if (strcmp(pointer->lastName, last)==0 && strcmp(pointer->firstName, first)==0) {
      printf("ERROR: Student already exists.\n");
      return headStudentList;
    }
  }

  if (headStudentList->next==NULL) { // only one
    int angy=0;
    for (int i=0; i<strlen(new->lastName); ++i) {
      if (strcmp(new->lastName, headStudentList->lastName)==0) {
        angy=1;
        break;
      }
      if ((new->lastName[i])<(headStudentList->lastName[i])) {
        new->next=headStudentList;
        return new;
      }
      if ((new->lastName[i])>(headStudentList->lastName[i])) {
        new->next=NULL;
        headStudentList->next=new;
        return headStudentList;
      }
      if ((new->lastName[i])==(headStudentList->lastName[i]) && (new->lastName[i+1]=='\0')) {
        new->next=headStudentList;
        return new;
      }
    }
    if (angy==1) {
      for (int i=0; i<strlen(new->firstName); ++i) {
        if ((new->firstName[i])<(headStudentList->firstName[i])) {
          new->next=headStudentList;
          return new;
        }
        if ((new->firstName[i])>(headStudentList->firstName[i])) {
          new->next=headStudentList->next;
          headStudentList->next=new;
          return headStudentList;
        }
        if ((new->firstName[i])==(headStudentList->firstName[i]) && (new->firstName[i+1]=='\0')) {
          new->next=headStudentList;
          return new;
        }
      }
    }
  }

  int beo=0;
  for (int i=0; i<strlen(new->lastName); ++i) { //first node
    if (strcmp(new->lastName, headStudentList->lastName)==0) {
      beo=1;
      break;
    }
    if ((new->lastName[i])<(headStudentList->lastName[i])) {
      new->next=headStudentList;
      return new;
    }
    else break;
    /*if ((new->lastName[i])>(headStudentList->lastName[i])) {
      printf("first1\n");
      new->next=headStudentList->next;
      headStudentList->next=new;
      return headStudentList;
    }*/
    if ((new->lastName[i])==(headStudentList->lastName[i]) && (new->lastName[i+1]=='\0')) {
      new->next=headStudentList;
      return new;
    }
  }
  if (beo==1) {
    for (int i=0; i<strlen(new->firstName); ++i) {
      if ((new->firstName[i])<(headStudentList->firstName[i])) {
        new->next=headStudentList;
        return new;
      }
      else break;
      /*if ((new->firstName[i])>(headStudentList->firstName[i])) {
        printf("first-1\n");
        new->next=headStudentList->next;
        headStudentList->next=new;
        return headStudentList;
      }*/
      if ((new->firstName[i])==(headStudentList->firstName[i]) && (new->firstName[i+1]=='\0')) {
        new->next=headStudentList;
        return new;
      }
    }
  }

  /*beo=0;
  for (int i=0; i<strlen(new->lastName); ++i) { //first node
    if (strcmp(new->lastName, headStudentList->next->lastName)==0) {
      beo=1;
      break;
    }
    if ((new->lastName[i])<(headStudentList->next->lastName[i])) {
      printf("second0\n");
      new->next=headStudentList;
      return new;
    }
    if ((new->lastName[i])>(headStudentList->lastName[i])) {
      printf("first1\n");
      new->next=headStudentList->next;
      headStudentList->next=new;
      return headStudentList;
    }
    else if ((new->lastName[i])==(headStudentList->next->lastName[i]) && (new->lastName[i+1]=='\0')) {
      printf("second2\n");
      new->next=headStudentList;
      return new;
    }
    else break;
  }
  if (beo==1) {
    for (int i=0; i<strlen(new->firstName); ++i) {
      if ((new->firstName[i])<(headStudentList->next->firstName[i])) {
        printf("second-0\n");
        new->next=headStudentList;
        return new;
      }
      if ((new->firstName[i])>(headStudentList->firstName[i])) {
        printf("first-1\n");
        new->next=headStudentList->next;
        headStudentList->next=new;
        return headStudentList;
      }
      else if ((new->firstName[i])==(headStudentList->next->firstName[i]) && (new->firstName[i+1]=='\0')) {
        printf("second-2\n");
        new->next=headStudentList;
        return new;
      }
      else break;
    }
  }*/

  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    //end case
    if (pointer->next->next==NULL) {
      int bahkslama=0;
      for (int i=0; i<strlen(new->lastName); ++i) {
        //printf("%c %c\n", new->lastName[i], pointer->next->lastName[i]);
        if (strcmp(new->lastName, pointer->next->lastName)==0) {
          bahkslama=1;
          break;
        }
        /*if ((new->lastName[i])<(pointer->next->lastName[i])) { //
          printf("-middle0 %d\n", i);
          new->next=pointer->next;
          pointer->next=new;
          return headStudentList;
        }
        if ((new->lastName[i])==(pointer->next->lastName[i]) && (new->lastName[i+1]=='\0')) {
          printf("-middle1 %d\n", i);
          new->next=pointer->next;
          pointer->next=new;
          return headStudentList;
        }*/
        if ((new->lastName[i])<(pointer->next->lastName[i])) {
          new->next=pointer->next;
          pointer->next=new;
          return headStudentList;
        }
        if ((new->firstName[i])>(pointer->next->firstName[i])) {
          new->next=NULL;
          pointer->next->next=new;
          return headStudentList;
        }
        if ((new->lastName[i])==(pointer->next->lastName[i]) && (new->lastName[i+1]=='\0')) {
          new->next=pointer->next;
          pointer->next=new;
          return headStudentList;
        }
      }
      if (bahkslama==1) {
        for (int i=0; i<strlen(new->firstName); ++i) {
          /*if ((new->firstName[i])<(pointer->next->firstName[i])) {
            printf("-middle-0 %d\n", i);
            new->next=pointer->next;
            pointer->next=new;
            return headStudentList;
          }
          if ((new->firstName[i])==(pointer->next->firstName[i]) && (new->firstName[i+1]=='\0')) {
            printf("-middle-1 %d\n", i);
            new->next=pointer->next;
            pointer->next=new;
            return headStudentList;
          }*/
          if ((new->firstName[i])<(pointer->next->firstName[i])) {
            new->next=pointer->next;
            pointer->next=new;
            return headStudentList;
          }
          if ((new->firstName[i])>(pointer->next->firstName[i])) {
            new->next=NULL;
            pointer->next->next=new;
            return headStudentList;
          }
          if ((new->firstName[i])==(pointer->next->firstName[i]) && (new->firstName[i+1]=='\0')) {
            new->next=pointer->next;
            pointer->next=new;
            return headStudentList;
          }
        }
      }
    }
    else {
      //middle case
      int aeoria=0;
      for (int i=-1; i<strlen(new->lastName); ++i) {
        //printf("%s %s\n", new->lastName, pointer->next->lastName);
        if (strcmp(new->lastName, pointer->next->next->lastName)==0) { //compare last names
          aeoria=1;
          break;
        }
        if ((new->lastName[i])<(pointer->next->next->lastName[i])) {
          new->next=pointer->next->next;
          pointer->next->next=new;
          return headStudentList;
        }
        if ((new->lastName[i])==(pointer->next->next->lastName[i]) && (new->lastName[i+1]=='\0')) {
          new->next=pointer->next->next;
          pointer->next->next=new;
          return headStudentList;
        }
      }
      if (aeoria==1) {
        for (int i=0; i<strlen(new->firstName); ++i) {
          if ((new->firstName[i])<(pointer->next->next->firstName[i])) {
            new->next=pointer->next->next;
            pointer->next->next=new;
            return headStudentList;
          }
          if ((new->firstName[i])==(pointer->next->next->firstName[i]) && (new->firstName[i+1]=='\0')) {
            new->next=pointer->next->next;
            pointer->next->next=new;
            return headStudentList;
          }
          /*if ((new->firstName[i])>(pointer->next->next->firstName[i])) {
            new->next=pointer->next->next;
            pointer->next->next=new;
            return headStudentList;
          }*/
        }
      }
    }
  }
  return headStudentList;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a grade to the specified student in order
//	1. Make sure a student by that name exists (so you can add a grade to the student)
//	2. If the grade already exists, update the value
//	3. Otherwise, add the grade to the student (add-in-order)

void addGradeOrdered(Student *headStudentList, char last[], char first[], char gradeName[], double value)
{
  char ntype;
  int nchap, nsec, chap=0, sec=0;
  sscanf(gradeName, "%c%d.%d", &ntype, &nchap, &nsec);
  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    if (strcmp(pointer->lastName, last)==0 && strcmp(pointer->firstName, first)==0) {
      for (Grade *ptr=pointer->headGradeList; ptr!=NULL; ptr=ptr->next) { //make sure grade doesn't exist
        if (strcmp(ptr->name, gradeName)==0) { //if it does, update it
          ptr->value = value;
          return;
        }
      }
      if (pointer->headGradeList==NULL) { //empty list
        Grade *pGrade = malloc(sizeof(Grade));
        strcpy(pGrade->name, gradeName);
        pGrade->value = value;
        pGrade->next = NULL;
        pointer->headGradeList = pGrade;
        return;
      }
      if (pointer->headGradeList->next==NULL) { //only one
        char ctype;
        int cchap, csec;
        sscanf(pointer->headGradeList->name, "%c%d.%d", &ctype, &cchap, &csec);
        if (cchap==nchap) chap=1;
        if (csec==nsec) sec=1;
        if (chap==0) {
          if (nchap<cchap) {
            Grade *pGrade = malloc(sizeof(Grade));
            strcpy(pGrade->name, gradeName);
            pGrade->value = value;
            pGrade->next = pointer->headGradeList;
            pointer->headGradeList = pGrade;
            return;
          }
          else {
            Grade *pGrade = malloc(sizeof(Grade));
            strcpy(pGrade->name, gradeName);
            pGrade->value = value;
            pGrade->next = NULL;
            pointer->headGradeList->next = pGrade;
            return;
          }
        }
        else if (sec==0) {
          if (nsec<csec) {
            Grade *pGrade = malloc(sizeof(Grade));
            strcpy(pGrade->name, gradeName);
            pGrade->value = value;
            pGrade->next = pointer->headGradeList;
            pointer->headGradeList = pGrade;
            return;
          }
          else {
            Grade *pGrade = malloc(sizeof(Grade));
            strcpy(pGrade->name, gradeName);
            pGrade->value = value;
            pGrade->next = NULL;
            pointer->headGradeList->next = pGrade;
            return;
          }
        }
        else {
          Grade *pGrade = malloc(sizeof(Grade));
          strcpy(pGrade->name, gradeName);
          pGrade->value = value;
          switch (ctype) {
            case 'P':
            switch (ntype) {
              case 'P':
                break;
              case 'C':
                pGrade->next = NULL;
                pointer->headGradeList->next = pGrade;
                return;
              case 'L':
                pGrade->next = NULL;
                pointer->headGradeList->next = pGrade;
                return;
              default:
                break;
            }
            case 'C':
            switch (ntype) {
              case 'P':
                pGrade->next = pointer->headGradeList;
                pointer->headGradeList = pGrade;
                return;
              case 'C':
                break;
              case 'L':
                pGrade->next = NULL;
                pointer->headGradeList->next = pGrade;
                return;
              default:
                break;
            }
            case 'L':
            switch (ntype) {
              case 'P':
                pGrade->next = pointer->headGradeList;
                pointer->headGradeList = pGrade;
                return;
              case 'C':
                pGrade->next = pointer->headGradeList;
                pointer->headGradeList = pGrade;
                return;
              case 'L':
                break;
              default:
                break;
            }
            default:
              break;
          }
        }
      }
      if (chap==0 && pointer->headGradeList->next==NULL) {
        char ctype; //new smallest
        int cchap, csec;
        sscanf(pointer->headGradeList->name, "%c%d.%d", &ctype, &cchap, &csec);
        if (cchap==nchap) chap=1;
        if (csec==nsec) sec=1;
        if (chap==0) {
          if (nchap<cchap) { //before
            Grade *pGrade = malloc(sizeof(Grade));
            strcpy(pGrade->name, gradeName);
            pGrade->value = value;
            pGrade->next = pointer->headGradeList;
            pointer->headGradeList = pGrade;
            return;
          }
        }
        else if (sec==0) {
          if (nsec<csec) {
            Grade *pGrade = malloc(sizeof(Grade));
            strcpy(pGrade->name, gradeName);
            pGrade->value = value;
            pGrade->next = pointer->headGradeList;
            pointer->headGradeList = pGrade;
            return;
          }
        }
        else {
          Grade *pGrade = malloc(sizeof(Grade));
          strcpy(pGrade->name, gradeName);
          pGrade->value = value;
          switch (ctype) {
            case 'P':
            switch (ntype) {
              case 'P':
                break;
              case 'C':
                //pGrade->next=pointer->headGradeList
                break;
              case 'L':
                break;
              default:
                break;
            }
            case 'C':
            switch (ntype) {
              case 'P':
                pGrade->next = pointer->headGradeList;
                pointer->headGradeList = pGrade;
                return;
              case 'C':
                break;
              case 'L':
                break;
              default:
                break;
            }
            case 'L':
            switch (ntype) {
              case 'P':
                pGrade->next = pointer->headGradeList;
                pointer->headGradeList = pGrade;
                return;
              case 'C':
                pGrade->next = pointer->headGradeList;
                pointer->headGradeList = pGrade;
                return;
              case 'L':
                break;
              default:
                break;
            }
            default:
              break;
          }
        }
      }
      for (Grade *ptr=pointer->headGradeList; ptr!=NULL; ptr=ptr->next) { //otherwise
        chap=0, sec=0;
        if (ptr->next->next==NULL) { //end
          char ctype;
          int cchap, csec;
          sscanf(ptr->next->name, "%c%d.%d", &ctype, &cchap, &csec);
          if (cchap==nchap) chap=1;
          if (csec==nsec) sec=1;
          if (chap==0) {
            if (nchap<cchap) { //before
              Grade *pGrade = malloc(sizeof(Grade));
              strcpy(pGrade->name, gradeName);
              pGrade->value = value;
              pGrade->next = ptr->next;
              ptr->next = pGrade;
              return;
            }
            else {
              Grade *pGrade = malloc(sizeof(Grade));
              strcpy(pGrade->name, gradeName);
              pGrade->value = value;
              pGrade->next = NULL;
              ptr->next->next = pGrade;
              return;
            }
          }
          else if (sec==0) {
            if (nsec<csec) {
              Grade *pGrade = malloc(sizeof(Grade));
              strcpy(pGrade->name, gradeName);
              pGrade->value = value;
              pGrade->next = ptr->next;
              ptr->next = pGrade;
              return;
            }
            else {
              Grade *pGrade = malloc(sizeof(Grade));
              strcpy(pGrade->name, gradeName);
              pGrade->value = value;
              pGrade->next = NULL;
              ptr->next->next = pGrade;
              return;
            }
          }
          else {
            Grade *pGrade = malloc(sizeof(Grade));
            strcpy(pGrade->name, gradeName);
            pGrade->value = value;
            switch (ctype) {
              case 'P':
              switch (ntype) {
                case 'P':
                  break;
                case 'C':
                  pGrade->next = NULL;
                  ptr->next->next = pGrade;
                  return;
                case 'L':
                  pGrade->next = NULL;
                  ptr->next->next = pGrade;
                  return;
                default:
                  break;
              }
              case 'C':
              switch (ntype) {
                case 'P':
                  pGrade->next = ptr->next;
                  ptr->next = pGrade;
                  return;
                case 'C':
                  break;
                case 'L':
                  pGrade->next = NULL;
                  ptr->next->next = pGrade;
                  return;
                default:
                  break;
              }
              case 'L':
              switch (ntype) {
                case 'P':
                  pGrade->next = ptr->next;
                  ptr->next = pGrade;
                  return;
                case 'C':
                  pGrade->next = ptr->next;
                  ptr->next = pGrade;
                  return;
                case 'L':
                  break;
                default:
                  break;
              }
              default:
                break;
            }
          }
        }
        else {
          char ctype;
          int cchap, csec;
          sscanf(ptr->next->name, "%c%d.%d", &ctype, &cchap, &csec);
          if (cchap==nchap) chap=1;
          if (csec==nsec) sec=1;
          if (chap==0) {
            if (nchap<cchap) { //before
              Grade *pGrade = malloc(sizeof(Grade));
              strcpy(pGrade->name, gradeName);
              pGrade->value = value;
              pGrade->next = ptr->next;
              ptr->next = pGrade;
              return;
            }
          }
          else if (sec==0) {
            if (nsec<csec) {
              Grade *pGrade = malloc(sizeof(Grade));
              strcpy(pGrade->name, gradeName);
              pGrade->value = value;
              pGrade->next = ptr->next;
              ptr->next = pGrade;
              return;
            }
          }
          else {
            Grade *pGrade = malloc(sizeof(Grade));
            strcpy(pGrade->name, gradeName);
            pGrade->value = value;
            switch (ctype) {
              case 'P':
              switch (ntype) {
                case 'P':
                  break;
                case 'C':
                  pGrade->next = ptr->next->next;
                  ptr->next->next = pGrade;
                  return;
                case 'L':
                  pGrade->next = ptr->next->next;
                  ptr->next->next = pGrade;
                  return;
                default:
                  break;
              }
              case 'C':
              switch (ntype) {
                case 'P':
                  pGrade->next = ptr->next;
                  ptr->next = pGrade;
                  return;
                case 'C':
                  break;
                case 'L':
                  pGrade->next = ptr->next->next;
                  ptr->next->next = pGrade;
                  return;
                default:
                  break;
              }
              case 'L':
              switch (ntype) {
                case 'P':
                  pGrade->next = ptr->next;
                  ptr->next = pGrade;
                  return;
                case 'C':
                  pGrade->next = ptr->next;
                  ptr->next = pGrade;
                  return;
                case 'L':
                  break;
                default:
                  break;
              }
              default:
                break;
            }
          }
        }
      }
    }
  }
  printf("ERROR: Student does not exist.\n");
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// remove a grade from a student
//	1. Make sure a student with that name exists
//	2. Make sure the grade exists in that student
//	3. Remove the grade from that student

void removeGrade(Student *headStudentList, char last[], char first[], char gradeName[]) {
  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    if (strcmp(pointer->lastName, last)==0 && strcmp(pointer->firstName, first)==0) {
      for (Grade *ptr=pointer->headGradeList; ptr!=NULL; ptr=ptr->next) {
        if (strcmp(pointer->headGradeList->name, gradeName)==0) { //head
          Grade *pDel=ptr;
          pointer->headGradeList=pointer->headGradeList->next;
          free(pDel);
          return;
        }
        else if (ptr->next==NULL) break;
        else if (strcmp(ptr->next->name, gradeName)==0) { //rest of list
          Grade *pDel=ptr->next;
          ptr->next = ptr->next->next;
          free(pDel);
          return;
        }
      }
      printf("ERROR: That grade does not exist.\n");
      return;
    }
  }
  printf("ERROR: That student does not exist.\n");
  return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// remove a student
//	1. Make sure a student with that name exists
//	2. Remove that student and all the grades of that student

Student *removeStudent(Student *headStudentList, char last[], char first[]) {
  if (strcmp(headStudentList->lastName, last)==0 && strcmp(headStudentList->firstName, first)==0) {
    if (headStudentList->next==NULL) {
      for (Grade *ptr=headStudentList->headGradeList; ptr!=NULL; ptr=headStudentList->headGradeList) { //delete grades
        removeGrade(headStudentList, last, first, ptr->name);
      }
      headStudentList=NULL;
    }
    else {
      for (Grade *ptr=headStudentList->headGradeList; ptr!=NULL; ptr=headStudentList->headGradeList) { //delete grades
        removeGrade(headStudentList, last, first, ptr->name);
      }
      headStudentList=headStudentList->next;
    }
    return headStudentList;
  }
  for (Student *pointer=headStudentList; pointer!=NULL; pointer=pointer->next) {
    if (strcmp(pointer->next->lastName, last)==0 && strcmp(pointer->next->firstName, first)==0) {
      if (pointer->next==NULL) {
        for (Grade *ptr=pointer->headGradeList; ptr!=NULL; ptr=pointer->headGradeList) { //delete grades
          removeGrade(headStudentList, last, first, ptr->name);
        }
        pointer->next = NULL; // delete student
        return headStudentList;
      }
      else {
        for (Grade *ptr=pointer->headGradeList; ptr!=NULL; ptr=pointer->headGradeList) { //delete grades
          removeGrade(headStudentList, last, first, ptr->name);
        }
        pointer->next = pointer->next->next; // delete student
        return headStudentList;
      }
    }
  }
  printf("ERROR: Student does not exist.\n");
  return headStudentList;
}
