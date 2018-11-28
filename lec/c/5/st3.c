#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct __person
{
	int age;
	char name[28];
} person;

typedef struct __score
{
	int math;
	int english;
	int physics;
} score;

typedef struct __school
{
	person *p;
	score s;
	char name[24];
} school;

school *init_struct(void)
{
	school *tmp = (school *)malloc(sizeof(school));

	tmp->p = (person *)malloc(sizeof(person));

	tmp->p->age = 22;
	strcpy(tmp->p->name, "Jesica");

	tmp->s.math = 70;
	tmp->s.english = 80;
	tmp->s.physics = 20;

	strcpy(tmp->name, "Test Univ");

	return tmp;
}

void print_struct(school *s)
{
	printf("School Name = %s\n", s->name);
	printf("Student Name = %s\n", s->p->name);
	printf("Age = %d\n", s->p->age);

	printf("Student Score\n");
	printf("Math - %d, English - %d, Physics - %d\n",
			s->s.math, s->s.english, s->s.physics);
}

int main(void)
{
	school *s = NULL;

	s = init_struct();
	print_struct(s);

	free(s->p);
	free(s);

	return 0;
}








