#include <stdio.h>
#include <string.h>

int main (void){

typedef struct {

	char name[20];
	char favoriteClass[20];
	double gpa;
} Student;

Student harry;

strcpy(harry.name, "Harry");
strcpy(harry.favoriteClass, "Physics");
harry.gpa = 4.0;

printf("%s	%s	%1.2f", harry.name, harry.favoriteClass, harry.gpa);

return 0;
}
