#include "../Common/BasicTypes.h"
#include "../Common/List.h"
#include "../Common/Memory.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const double MIN_MARKS = 40;
static const double MAX_MARKS = 100;

typedef struct {
    double mark;
    string PASS;
} range;

typedef struct {
    string name;
    range maths;
    range science;
    range social;
} Marks;

string checkPass(Boolean pass) {
    return pass ? "passed" : "failed";
}

Marks createMarks(const string name, double maths, double science, double social) {
    Marks new;
    new.name = strdup(name); // make a copy of the name
    new.maths.mark = maths;
    new.maths.PASS = checkPass(maths >= MIN_MARKS);
    new.science.mark = science;
    new.science.PASS = checkPass(science >= MIN_MARKS);
    new.social.mark = social;
    new.social.PASS = checkPass(social >= MIN_MARKS);
    return new;
}

void printMarks(List list) {
    char name[100];
    printf("Enter the student name: ");
    scanf_s("%99s", name, (unsigned)_countof(name));

    Boolean found = false;
    Marks stud;

    for (size_t i = 0; i < list->size; i++) {
        Marks *temp = (Marks *)valueAt(list, i);
        if (strcmp(temp->name, name) == 0) {
            stud = *temp;
            found = true;
            break;
        }
    }

    if (!found) {
        printf("Student not found\n");
        return;
    }

    printf("\nStudent name   : %s\n", stud.name);
    printf("Maths marks    : %.2lf\n", stud.maths.mark);
    printf("Maths result   : %s\n", stud.maths.PASS);
    printf("Science marks  : %.2lf\n", stud.science.mark);
    printf("Science result : %s\n", stud.science.PASS);
    printf("Social marks   : %.2lf\n", stud.social.mark);
    printf("Social result  : %s\n", stud.social.PASS);
}

void createStudents(List students) {
    char name[100];
    double maths, science, social;

    printf("Enter the student name: ");
    scanf_s("%99s", name, (unsigned)_countof(name));

    printf("Enter the student's maths mark: ");
    scanf_s("%lf", &maths);
    printf("Enter the student's science mark: ");
    scanf_s("%lf", &science);
    printf("Enter the student's social mark: ");
    scanf_s("%lf", &social);

    Marks *stud1 = newAlloc(sizeof(Marks));
    *stud1 = createMarks(name, maths, science, social);

    appendList(students, stud1);
    printf("Student added successfully!\n\n");
}

int main() {
    Boolean loop = true;
    List students = createList(sizeof(Marks));

    while (loop) {
        int option = 0;
        printf("\nSelect one of the options:\n");
        printf("1. Add student\n");
        printf("2. Print student marks\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf_s("%d", &option);

        switch (option) {
        case 1:
            createStudents(students);
            break;
        case 2:
            printMarks(students);
            break;
        case 3:
            loop = false;
            break;
        default:
            printf("Invalid option!\n");
        }
    }

    destruct();
    return 0;
}
