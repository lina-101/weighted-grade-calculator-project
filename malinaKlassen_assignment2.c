//COMP 1410 Assignment #2: Malina Klassen
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

//Component Structure
typedef struct{
    char name[50];
    int weight;
    int maximum;
    int score;
    double earnedScore;
} CourseComponents;

//Student Structure
typedef struct{
    char fullName[50];
    CourseComponents *components;
    int numComponents;
    double finalGrade;
    char* letterGrade;
} Student;

//Student Node Structure
typedef struct StudentNode{
    Student* student;
    struct StudentNode* next;
}StudentNode;

//Get Float inputs, part of validation
float getNum(){
    char inputNum[50];
    scanf(" %[^\n]s", inputNum);

    for(int i=0; i!='\0'; i++){
        if(!((inputNum[i]<=9)&&(inputNum[i]>=0))){
            return 0;
        }
    }
    float workingNum = atof(inputNum);
    return workingNum;
}

//Validating the input from getNum()
bool validateNum(float num){
    if(num==0){
        printf("Please enter integers only.\n");
        return false;
    }

    if(num>0){
        return true;
    } else{
        printf("Please enter positive integer numbers.\n");
        return false;
    }
}

//Read menu option
int getOption(){
    int opt = getNum();
    bool valid = false;
    if (valid = validateNum(opt)==false){
        return 0;
    }
    return opt;
}

//Menu Printout
int menuPrint(){
    printf("\n\n======================================");
    printf("\n  Weighted Grade Calculation Program");        
    printf("\n======================================");
    
    bool valid = false;
    int opt = 0;
    do{
        printf("\n1. Single Student Grades\n2. Multiple Students Grades\n3. Sort Students by Grade\n4. Search for a Student\n5. Exit");
        printf("\nEnter your choice (1/2/3/4/5): ");
        opt = getOption();            
        
        if ((opt==1)||(opt==2)||(opt==3)||(opt==4)||(opt==5)){
            valid = true;
        }else {
            printf("\nInvalid Input. Please input 1, 2, 3, 4, or 5.\n");
        }
    }while(valid!=true); //Validating option input
    
    return opt;
}

//Reading component num from user
int getComponentNum(){
    bool valid = false;
    do{
        printf("Enter number of course componenets: ");
        int num = (int)getNum();
        if(valid = validateNum(num)==true) return num;
    }while(valid!=true);
}

//Checking valid weight sum, must add to 100
bool validWeight(int check){
    if(check==100){
        return true;
    } else {
        printf("Please ensure all weights add up to 100.\n");
        return false;
    }
}

//Get Component Information and make sure it's valid
void getCourseComponents(CourseComponents *c){
    bool valid = false;
    printf("  Name: ");
    scanf(" %[^\n]s", c->name);

    do{
        valid = false;
        printf("  Weight (as percentage): ");
        c->weight = (int)getNum();
        valid = validateNum(c->weight);
    }while(valid!=true);
    
    do{
        valid = false;
        printf("  Max Allocated Points: ");
        c->maximum = (int)getNum();
        valid = validateNum(c->maximum);
    }while(valid!=true);
}

//Read valid earned student grades
void getEarnedGrade(int opt, CourseComponents *c){
    bool valid;
    do{
        if(opt == 1){
            printf("  Earned Points: ");
        }
        if (opt==2){
            printf("Score for ""%s"": ", c->name);
        }
        c->earnedScore = (int)getNum();
        valid = validateNum(c->earnedScore);
        if(c->earnedScore>c->maximum){
            printf("Please ensure the earned grade is not more than the max amount.\n");
            valid = false;
        }
    }while(valid!=true);
}

//Calculate final weighted grade
int finalGradeCalc(Student s){
    float gradeFloat = 0;
    for(int k=0; k<s.numComponents; k++){
        CourseComponents *currentComp = &(s.components[k]);
        float sPercent = ((float)currentComp->earnedScore)/((float)currentComp->maximum);
        float sWeight = ((float)currentComp->weight)/100;
        gradeFloat += sPercent * sWeight;
    }
    gradeFloat *= 100;
    int finalGrade = round(gradeFloat);
    return finalGrade;
}

//Convert number grade to letter
void letterGrade(Student *s){
    if (s->finalGrade>=90){
        s->letterGrade = (char*)"A+";
    } else if (s->finalGrade>=85){
        s->letterGrade = (char*)"A";
    }else if (s->finalGrade>=80){
        s->letterGrade = (char*)"A-";
    }else if(s->finalGrade>=75){
        s->letterGrade = (char*)"B+";
    }else if (s->finalGrade>=70){
        s->letterGrade = (char*)"B";
    } else if (s->finalGrade>=65){
        s->letterGrade = (char*)"C+";
    }else if (s->finalGrade>=60){
        s->letterGrade = (char*)"C";
    } else if (s->finalGrade>=50){
        s->letterGrade = (char*)"D";
    } else {
        s->letterGrade = (char*)"F";
    };
}

//Add a student to the linked list
void addStudentToList(StudentNode** head, Student* s){
    StudentNode* newS = (StudentNode*)malloc(sizeof(StudentNode));
    newS->student = s;
    newS->next = NULL;

    if (*head == NULL){
        *head = newS;
        return;
    }

    StudentNode* temp = *head;
    while(temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = newS;
}

//Sorting list of students by final grade
StudentNode* sortStudents(StudentNode** head){
    StudentNode* current;
    StudentNode* index;
    StudentNode temp;
    for(current = *head; current != NULL; current = current->next){
        for(index = current->next; index!=NULL; index = index->next){
            if(current->student->finalGrade < index->student->finalGrade){
                temp.student = current->student;
                current->student = index->student;
                index->student = temp.student;
            }
        }
    }
}

//Find the highest final grade
float findMaxGrade(StudentNode** headMax, StudentNode* head){
    StudentNode* temp = head;
    float maxGrade = 0;

    while(temp!=NULL){
        if(maxGrade<temp->student->finalGrade){
            maxGrade = temp->student->finalGrade;
        }
        temp = temp->next;
    }
    temp = head;
    while(temp!=NULL){
        if(maxGrade==temp->student->finalGrade){
            addStudentToList(headMax, temp->student);
        }
        temp = temp->next;
    }
    return maxGrade;
}

//Find the average
float findAvg(StudentNode* head){
    StudentNode* temp = head; 
    float sum = 0;
    float avg;
    int i=0;
    while(temp!=NULL){
        sum += temp->student->finalGrade;
        temp = temp->next;
        i++;
    }
    avg = sum/i;
    return avg;
}

//Find the median grade
float findMedian(StudentNode** head){
    StudentNode* temp = *head;
    int i = 0, j = 0; 
    while(temp!=NULL){
        temp = temp->next;
        i++;
    }

    float median;
    StudentNode* index = *head;
    if(i%2==0){
        while(j!=(i/2)-1 && index->next!=NULL){
            index = index->next;
            j++;
        }
        median = (index->student->finalGrade + index->next->student->finalGrade)/2;
    } else if (i%2==1){
        while(j!=i/2 && index->next!=NULL){
            index = index->next;
            j++;
        }
        median = index->student->finalGrade;
    }
    return median;
}

//Printing the Class Summary for option #2
void printClassSummary(StudentNode* head){
    StudentNode* temp = head; 
    printf("--Class Summary--");
    while(temp!=NULL){
        printf("\n%s - %.2f%% (%s)", temp->student->fullName, temp->student->finalGrade, temp->student->letterGrade);
        temp = temp->next;
    }
    StudentNode* studentMaxGrade = NULL;
    float max = findMaxGrade(&studentMaxGrade, head);
    float avg = findAvg(head);

    printf("\n\nMaximum: %.2f%% (Students:", max);
    StudentNode* temp2 = studentMaxGrade;
    while(temp2!=0){
        printf(" %s,", temp2->student->fullName);
        temp2 = temp2->next;
    }
    printf(")\nAverage: %.2f%%", avg);

    StudentNode* sorted = sortStudents(&head);
    StudentNode* current = sorted; 
    int i=0;
    while(current!=NULL){
        printf("\n%d. %s - %.2f (%s)", i, current->student->fullName, current->student->finalGrade, current->student->letterGrade);
        current = current->next;
        i++;
    }

    sortStudents(&head); //Sorting students so median can be found
    float median = findMedian(&head);
    printf("\nMedian: %.2f%%", median);
}

//Print Student List
void printStudents(StudentNode** head){
    if (*head==NULL) return;

    StudentNode* temp = *head;
    int i = 1;
    while(temp!=NULL){
        printf("\n%d. %s - %.2f%% (%s)", i++, temp->student->fullName, temp->student->finalGrade, temp->student->letterGrade);
        temp = temp->next;
    }
}

void freeMemory(StudentNode** head){
    if(head == NULL || *head==NULL) return;
    StudentNode* temp = *head;
    while(temp!=NULL){
        if (temp->student != NULL) {
            free(temp->student);
            temp->student = NULL;
        }
        //temp->student = NULL;
        StudentNode* current = temp;
        temp = temp->next;
        free(current);
    }
    *head = NULL;
}

void singleStudentOpt(int opt, StudentNode** head){
    Student s;
    printf("\nEnter student's full name: ");
    scanf(" %[^\n]s", s.fullName);

    s.numComponents = getComponentNum();
    s.components = malloc(s.numComponents*sizeof(CourseComponents));

    if(s.components==NULL){
        printf("Memory Failed to Allocate");
        return;
    } 

    bool valid = false;
    int weightcheck = 0;
    do{
        weightcheck = 0;
        for(int i=0; i<s.numComponents; i++){
            printf("\nComponent %d\n", i+1);
            getCourseComponents(&(s.components[i]));
            getEarnedGrade(opt, &(s.components[i]));
            weightcheck += s.components[i].weight;
        }
        valid = validWeight(weightcheck);

    }while(valid!=true);
    
    s.finalGrade = finalGradeCalc(s);
    letterGrade(&s);

    printf("\n---Summar of Scores---");
    printf("\nfinal grade: %.2f%%", s.finalGrade);
    printf("\nLetter Grade: %s", s.letterGrade);

    free(s.components);
    s.components = NULL;
}

void multiStudentOpt(int opt, StudentNode** head, Student* newStudent){
    Student sMore;
    sMore.components = NULL;
    sMore.numComponents = getComponentNum();
    sMore.components = malloc(sMore.numComponents*sizeof(CourseComponents));
    
    if(sMore.components==NULL){
        printf("Memory Failed to Allocate");
        return;
    } 

    bool valid = false;
    int weightcheck = 0;
    do{
        for(int i=0; i<sMore.numComponents; i++){
            printf("\nComponent %d\n", i+1);
            getCourseComponents(&(sMore.components[i]));
            weightcheck += sMore.components[i].weight;
        }
        valid = validWeight(weightcheck);
        if(valid==false){
            weightcheck = 0;
        }
    }while(valid!=true);

    do{
        newStudent = (Student*)malloc(sizeof(Student));
        *newStudent = sMore;
        if(newStudent==NULL){
            printf("Memory Failed to Allocate");
            break;
        } 
        
        printf("\nEnter student's full name (or type DONE to stop): ");
        scanf(" %[^\n]s", newStudent->fullName);
        
        if(strcmp(newStudent->fullName, "DONE") == 0){
            free(newStudent);
            break;
        }

        for(int j=0; j<newStudent->numComponents; j++){
            getEarnedGrade(opt, &(newStudent->components[j]));
        }

        newStudent->finalGrade = finalGradeCalc(*newStudent);
        letterGrade(newStudent);
        addStudentToList(head, newStudent);

    }while(newStudent != NULL && strcmp(newStudent->fullName, "DONE")!=0);
    printClassSummary(*head);
    free(sMore.components);
    sMore.components = NULL;
}

//Search for a specific student by name
void searchStudents(StudentNode** head, char* name){
    if(*head==NULL) return;
    StudentNode* temp = *head;

    while(temp!=NULL){
        if(strcmp(name, temp->student->fullName)==0){
            printf("\nResult: %s - %.2f%% (%s)", temp->student->fullName, temp->student->finalGrade, temp->student->letterGrade);
            return;
        }
        temp = temp->next;
    }
    printf("Student not found.");
}

int main(){
    int opt;
    StudentNode *head = NULL;
    Student* newStudent = NULL;

    do{
        int opt = menuPrint();

        if(opt==5){
            break;
        }

        //option #1: Single Student
        if(opt==1){
            singleStudentOpt(opt, &head);
        }

        //Option #2: Multiple Students
        if(opt==2){
            multiStudentOpt(opt, &head, newStudent);
        }
        //Option #3: sort students by final grade
        if(opt==3){
            printf("\n=====================================");
            printf("\nSorting Students by Final Grade. . .");
            printf("\n=====================================");
            printf("\nClass Ranking: ");
            StudentNode* sorted = sortStudents(&head);
            printStudents(&head);
        }
        //Option#4: searching for a student by name
        if(opt==4){
            char name[50];
            printf("\nEnter student name to search: ");
            scanf(" %[^\n]s", name);

            searchStudents(&head, name);
        }
    }while(opt!=5);
    printf("--- Good bye! ---");
    freeMemory(&head);
}