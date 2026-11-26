//COMP 1410 Assignment #1: Malina Klassen
#include <stdio.h>
#include <math.h>

//Reading number of components from user
int numComponents(){
    int num;
    do{
        printf("\nNumber of Components: ");
        scanf("%d", &num);
        if(num<=0){
            printf("Invalid input. Positive integers only.\n");
        }
    }while(num<=0);

    return num;
}

//Reading info of components from user
void getCompContents(int components, char *gradeName[components][100], int *weight, int *max){
    for(int i=0; i<components; i++){ 
        printf("Component %d:\n", i+1);
        printf("   Name: ");
        scanf("%s", gradeName[i]);
    do{
        printf("   Weight: ");
        scanf("%d", &weight[i]);
        if(weight[i]<0){
            printf("Invalid input. Positive integers only.\n");
        }
    }while(weight[i]<0);
    do{
        printf("   Max Allocated Points:");
        scanf("%d", &max[i]);
        if(max[i]<0){
            printf("Invalid input. Positive integers only.\n");
        }
    }while(max[i]<0);
    }
    return;
}

//Validate the component inputs
void validateCompContents(int components, char *gradeName[components][100], int *weight, int *max){
    int validate = 0;
    do{
        int weightCheck = 0;
        getCompContents(components, gradeName, weight, max); 
        for(int i=0; i<components; i++){
            weightCheck += weight[i];
        }
        if(weightCheck==100){
            validate = 1;
        } else {
            printf("Please ensure the total component weights add up to 100.\n");
        }
    }while(validate !=1);

}

//Reading number of students
int getStudentNum(int opt){
    int studentNum = 1;
    if(opt==2){
        do{
            printf("Number of Students: ");
            scanf("%d", &studentNum);
                    
            if(studentNum<0){
                printf("Invalid Input. Please input a positive integer.\n");
            }
        }while(studentNum<0);
    }
    return studentNum;
}

//Reading the student grades 
void getGrade(int student, int components, char *gradeName[components][100], int *maxPoints, int studentNum, int grades[studentNum][components]){
    for(int j=0; j<components; j++){
        do{
            printf("Score for \"%s\": ", gradeName[j]);
            scanf("%d", &grades[student][j]);

            if((grades[student][j]>maxPoints[j])||(grades[student][j]<0)){
                printf("Invalid Input. Score must be less than max and greater than 0.\n");   
            }
        }while((grades[student][j]>maxPoints[j])||(grades[student][j]<0));//will only end if the input is valid  
    }
}

//Calculating final weighted grade
void finalGradeCalc(int student, int components, int *weight, int *maxPoints, int studentNum, int grades[studentNum][components], int finalCalc[studentNum]){
    float gradeFloat = 0;
    for(int k=0; k<components; k++){
        gradeFloat += (((float)grades[student][k])/(float)maxPoints[k])*((float)weight[k]/100);
    }
    gradeFloat *= 100;
    finalCalc[student] = round(gradeFloat);
}

//Converting number grade to a letter
void letterGrade(int finalCalc){
    if (finalCalc>=90){
        printf("A+");
    } else if (finalCalc>=85){
        printf("A");
    }else if (finalCalc>=80){
        printf("A-");
    }else if(finalCalc>=75){
        printf("B+");
    }else if (finalCalc>=70){
        printf("B");
    } else if (finalCalc>=65){
        printf("C+");
    }else if (finalCalc>=60){
        printf("C");
    } else if (finalCalc>=50){
        printf("D");
    } else {
        printf("F");
    }
}

//Reading and printing grades
void printStudentGrades(int components, char *gradeName[components][100], int *weight, int *maxPoints, int studentNum, int grades[studentNum][components], int finalCalc[studentNum]){
    for(int i=0; i<studentNum; i++){
        if(1<studentNum){
            printf("-- Student %d --\n", i+1);
        } else {
            printf("-- Summary of Score --\n");
        }
    
        getGrade(i, components, gradeName, maxPoints, studentNum, grades); //Reading the grade values in separate function

        finalGradeCalc(i, components, weight, maxPoints, studentNum, grades, finalCalc);
        printf("Weighted Final Grade: %d%%", finalCalc[i]);
        printf("\nLetter Grade: ");
        letterGrade(finalCalc[i]);
        printf("\n");
    }
}

//Finding the maximum
float findMaxGrade(int studentNum, int finalCalc[studentNum]){
    float max;
    for(int i=0; i<studentNum; i++){
        if(max<finalCalc[i]){
            max = finalCalc[i];
        }
    }
    return max;
}

//Recursive Function: finding the average
float findGradeAvg(int i, int sum, int components, int studentNum, int finalCalc[studentNum]){
    if (i==studentNum){
        float avg = (float)sum/studentNum;
        return avg;
    }
    sum += finalCalc[i];
    findGradeAvg(i+1, sum, components, studentNum, finalCalc);

}

//Finding the Median
float findMedian(int components, int studentNum, int finalCalc[studentNum]){
    int sortedFinal[studentNum]; //Creating a copy of finalCalc to sort
    for (int k=0; k<studentNum; k++){
        sortedFinal[k] = finalCalc[k];
    }
    //Sorting copy of finalCalc 
    for(int i=0; i<studentNum; i++){
        for (int j=0; j<studentNum; j++){
            if(sortedFinal[i]<sortedFinal[j]){
                int temp = sortedFinal[i];
                sortedFinal[i] = sortedFinal[j];
                sortedFinal[j] = temp;
            }
        }
    }
    //Finding the median
    float median;
    if (studentNum%2==0){
        median = (float)(sortedFinal[(studentNum/2)-1]+sortedFinal[(studentNum/2)])/2;
    } else {
        median = sortedFinal[(int)round((studentNum/2.00))-1];
    }
    
    return median;
}

//Printing the class summary (for opt 2)
void classSummary(int components, char *gradeName[components][100], int *weight, int *maxPoints, int studentNum, int finalCalc[studentNum]){
    float maximum = findMaxGrade(studentNum, finalCalc);
    float average = findGradeAvg(0, 0, components, studentNum, finalCalc);
    float median = findMedian(components, studentNum, finalCalc);

    printf("-- Class Summary --\n");
    printf("Maximum: %.2f\n", maximum);
    printf("Average: %.2f\n", average);
    printf("Median: %.2f\n", median);
}

int main(){
    int opt;
    
    //Menu printout 
    do{
        printf("\n======================================");
        printf("\nWeighted Grades Calculation Program");        
        printf("\n======================================");
        
        int valid = 0;
        do{
            printf("\n1. Single Student\n2. Multiple Students\n3. Exit");
            printf("\nEnter your choice (1/2/3): ");
            scanf("%d", &opt);
            
            if ((opt==1)||(opt==2)||(opt==3)){
                valid = 1;
            }else {
                printf("\nInvalid Input. Please input 1, 2, or 3.");
            }
        }while(valid!=1); //Validating option input

        if(opt==3){
            break;
        }

    //Read number of components and declare variables
        int components = numComponents();
        char *gradeName[components][100];
        int weight[components], maxPoints[components];

        //Read contents of components
        validateCompContents(components, gradeName, weight, maxPoints);

    //Number of students
        int studentNum = getStudentNum(opt); 

    //Read students grades
        int grades[studentNum][components];
        int finalCalc[studentNum]; //Calculate weighted grade

    //Grades printing
        printStudentGrades(components, gradeName, weight, maxPoints, studentNum, grades, finalCalc);

        if (opt==2){
            //Call class summary function (only used for multiple students)  
            classSummary(components, gradeName, weight, maxPoints, studentNum, finalCalc);         
        }

    }while(opt!=3);

    if (opt==3){
        printf("\n--- HAVE A GOOD DAY! ---\n");        
        printf("=========================");

    }
}