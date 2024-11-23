#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gradebook.h"

typedef
enum {
    ADD_STUDENT,
    ADD_GRADE,
    COUNT,
    PRINT_STUDENT,
    PRINT,
    ADD_STUDENT_ORDERED,
    ADD_GRADE_ORDERED,
    REMOVE_GRADE,
    REMOVE_STUDENT,
    HELP,
    QUIT,
    INVALID
}
Option
;

char *actions[11] = {
"addStudent",
"addGrade",
"count",
"printStudent",
"print",
"addStudentOrdered",
"addGradeOrdered",
"removeGrade",
"removeStudent",
"help",
"quit"
};

int getActionID(char action[])
{
	int i;
	for (i=0; i<11; i++) {
		if (strcmp(action, actions[i])==0) return i;
	}
	return i; // 11 for invalid action
}

int isValidGradeName(char gradeName[])
{
    char type;
    int chap, sec;
    sscanf(gradeName, "%c%d.%d", &type, &chap, &sec);

	if (type!='P' && type!='C' && type!='L') return 0;
    if (chap<=0 || sec<=0) return 0;

    char name2[100];
    sprintf(name2, "%c%d.%d", type, chap, sec);
    if (strcmp(gradeName, name2)!=0) return 0;

    return 1;
}

void printHelp(void) {
    printf("\nThe valid commands:\n\n");
    printf("\taddStudent lastname firstname\n");
    printf("\t*** Add a student (add-at-front)\n");
    printf("\taddGrade lastname firstname gradename value\n");
    printf("\t*** Add a grade to an existing student (add-at-end)\n");
    printf("\tcount\n");
    printf("\t*** Print the number of students\n");
    printf("\tprintStudent lastname firstname\n");
    printf("\t*** Print a student\n");
    printf("\tprint\n");
    printf("\t*** Print all students\n");
    printf("\taddStudentOrdered lastname firstname\n");
    printf("\t*** Add a student (in alphabetical order)\n");
    printf("\taddGradeOrdered lastname firstname gradename value\n");
    printf("\t*** Add a grade in order to an existing student\n");
    printf("\tremoveGrade lastname firstname gradename\n");
    printf("\t*** Remove a grade from a student\n");
    printf("\tremoveStudent lastname firstname\n");
    printf("\t*** Remove a student\n");
    printf("\thelp\n");
    printf("\t*** Display this list\n");
    printf("\tquit\n");
    printf("\t*** Exit the program\n");

    printf("\nNote: a valid grade name starts with a letter (P, C or L),\n");
	printf("followed by a chapter number, a dot, and a section number.\n\n");
}

int main(int argc, char* argv[])
{
	char action[100];
	char last[100], first[100];
	char gradeName[100];
	double value;
	char rest[300];

	Student *headStudentList=NULL;

	while (1) {
		printf("\nEnter a command: ");
        scanf("%s", action);
		int action_id=getActionID(action);
		if (action_id==QUIT) break;
		switch (action_id) {
			case ADD_STUDENT:
				scanf("%s%s", last, first);
				headStudentList = addStudent(headStudentList, last, first);
				break;
			case ADD_GRADE:
				scanf("%s%s", last, first);
				scanf("%s", gradeName);
				if (isValidGradeName(gradeName)) {
					scanf("%lf", &value);
					addGrade(headStudentList, last, first, gradeName, value);
				}
				else {
            		printf("\n%s: invalid grade name. Type help for help.\n", gradeName);
            		fgets(rest, 300, stdin); // skip the rest of line
				}
				break;
			case COUNT:
				printf("\nThere are %d students\n", count(headStudentList));
				break;
			case PRINT_STUDENT:
				scanf("%s%s", last, first);
				printStudent(headStudentList, last, first);
				break;
			case PRINT:
				print(headStudentList);
				break;
			case ADD_STUDENT_ORDERED:
				scanf("%s%s", last, first);
				headStudentList = addStudentOrdered(headStudentList, last, first);
				break;
			case ADD_GRADE_ORDERED:
				scanf("%s%s", last, first);
				scanf("%s", gradeName);
				if (isValidGradeName(gradeName)) {
					scanf("%lf", &value);
					addGradeOrdered(headStudentList, last, first, gradeName, value);
				}
				else {
            		printf("\n%s: invalid grade name. Type help for help.\n", gradeName);
            		fgets(rest, 300, stdin); // skip the rest of line
				}
				break;
			case REMOVE_GRADE:
				scanf("%s%s", last, first);
				scanf("%s", gradeName);
				if (isValidGradeName(gradeName)) {
					removeGrade(headStudentList, last, first, gradeName);
				}
				else {
            		printf("\n%s: invalid grade name. Type help for help.\n", gradeName);
            		fgets(rest, 300, stdin); // skip the rest of line
				}
				break;
			case REMOVE_STUDENT:
				scanf("%s%s", last, first);
				headStudentList = removeStudent(headStudentList, last, first);
				break;
			case HELP:
				printHelp();
				break;
			case INVALID:
            	printf("\n%s: invalid action. Type help for help.\n", action);
            	fgets(rest, 300, stdin); // skip the rest of line
				break;
		}

	}
	return 0;
}
