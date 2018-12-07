#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __Car Car;

struct __Car
{
	int speed;
	char color[32];

	int (*gs)(Car *);
	char *(*gc)(Car *);
	void (*ss)(Car *, int);
	void (*sc)(Car *, char *);
};

int getSpeed(Car *c)
{
	return c->speed;
}

char *getColor(Car *c)
{
	return c->color;
}

void setSpeed(Car *c, int s)
{
	c->speed = s;
}

void setColor(Car *c, char *color)
{
	strcpy(c->color, color);
}

int main(void)
{
	Car *c = (Car *)malloc(sizeof(Car));
	c->gs = getSpeed;
	c->gc = getColor;
	c->ss = setSpeed;
	c->sc = setColor;

	c->ss(c, 30);
	printf("speed = %d\n", c->gs(c));

	c->sc(c, "blue");
	printf("color = %s\n", c->gc(c));

	return 0;
}
