#include <stdio.h>
#include <string.h>
struct Student
{
char name[30];
int rollno;
float cgpa;
};

void heapify_function(struct Student array[], int n, int i);
int main()
{
int num;
printf("\nEnter the number of students: \n");
scanf("%d", &num);
struct Student students[num];
for (int i=0; i<num; i++)
{
printf("\nEnter Name of Student %d: ",i+1);
scanf("%s", students[i].name);
printf("Enter Roll Number: ");
scanf("%d", &students[i].rollno);
printf("Enter CGPA: ");
scanf("%f", &students[i].cgpa);
}
//Sorting
for (int i=num/2-1; i>=0; i--)
heapify_function(students, num, i);
for (int i=num-1; i>0; i--)
{

struct Student temp=students[0];
students[0]=students[i];
students[i]=temp;
heapify_function(students, i, 0);
}
printf("\nSorted records based on Roll Number:\n\n");
for(int i=0; i<num; i++)
printf("\nName: %s, Roll Number: %d, CGPA: %.2f\n", students[i].name, students[i].rollno,
students[i].cgpa);
return 0;
}
void heapify_function(struct Student array[], int n, int i)
{
int largest=i;
int leftchild=2*i+1;
int rightchild=2*i+2;
if(leftchild<n&&array[leftchild].rollno>array[largest].rollno)
largest=leftchild;
if(rightchild<n&&array[rightchild].rollno>array[largest].rollno)
largest=rightchild;
if(largest!=i)
{
struct Student temp=array[i];
array[i]=array[largest];
array[largest]=temp;
heapify_function(array, n, largest);
}
}
