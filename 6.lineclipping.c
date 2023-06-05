#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

int x1,y1,x2,y2;
int x11,y11,x22,y22;
int flaga=0,flagp=0;
int xmin, ymin, xmax,ymax;
int outcode1[4]={0,0,0,0},outcode2[4]={0,0,0,0};

void outcode_gen(int outcode[4], int xa, int ya)
{
	if(ya>ymax)
	{
		outcode[0]=1;
	}
	if(ya<ymin)
	{
		outcode[1]=1;
	}
	if(xa>xmax)
	{
		outcode[2]=1;
	}
	if(xa<xmin)
	{
		outcode[3]=1;
	}
}

void delay()
{
for(int i=0; i<1223; i++)
{
	for(int j=0; j<1223; j++)
	{
	
	}
}
}

void line_status()
{
		for(int i=0; i<4; i++)
		{
			if(outcode1[i] || outcode2[i] !=0)
			{
			flaga=1;
			}
		}

		if(flaga==0)
		{
			printf("Line is completely accepted");
		}

		for(int i=0; i<4; i++)
		{
			if(outcode1[i] && outcode2[i] !=0)
			{
				flagp=1;
			}
		}

		if(flagp==0)
		{
			printf("Line is partially accepted");
		}
		else if(flagp==1)
		{
			printf("Line is completely rejected");
		}
}

void line_clip()
{
	line_status();
	if(flagp==0)
	{
		float m;
		m=(y2-y1)/(float)(x2-x1);

		x11=x1;
		y11=y1;

		x22=x2;
		y22=y2;

	if(outcode1[0]==1)
	{
		y11=ymax;
		x11=x1+(y11-y1)/m;
	}
	if(outcode1[1]==1)
	{
		y11=ymin;
		x11=x1+(y11-y1)/m;
	}
	if(outcode1[2]==1)
	{
		x11=xmax;
		y11=y1+ m*(x11-x1);
	}
	if(outcode1[3]==1)
		{
		x11=xmin;
		y11=y1+ m*(x11-x1);
	}
	/*else
	{
	x11=x1;
	y11=y1;
	}*/

	if(outcode2[0]==1)
	{
		y22=ymax;
		x22=x2+(y22-y2)/m;
	}
	if(outcode2[1]==1)
	{
		y22=ymin;
		x22=x2+(y22-y2)/m;
	}
	if(outcode2[2]==1)
	{
		x22=xmax;
		y22=y2+ m*(x22-x2);
	}
	if(outcode2[3]==1)
	{
		x22=xmin;
		y22=y2+ m*(x22-x2);
	}
	/*else
	{
	x22=x2;
	y22=y2;
	}*/
	printf("X22 and y22 %d\t%d", x22,y22);
	}
}

int Round(int a)
{
	return (int)(a+0.5);
}
void dda(int xa, int ya, int xb, int yb)
{
	int dx, dy, steps;

	dx=xb-xa;
	dy=yb-ya;

	if(abs(dx)>abs(dy))
	{
	steps=abs(dx);
	}
	else
	{
	steps=abs(dy);
	}

	float x, y, Xin, Yin;

	Xin=dx/(float)steps;
	Yin=dy/(float)steps;

	x=xa;
	y=ya;

	glVertex2d(Round(x),Round(y));

	for(int i=0; i<steps; i++)
	{
	x=x+Xin;
	y=y+Yin;

	glVertex2d(Round(x), Round(y));
	}
}


void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	dda(x1,y1,x2,y2);

	glColor3f(0.0,0.0,0.0);
	dda(xmin,ymin,xmax,ymin);
	dda(xmax,ymin,xmax,ymax);
	dda(xmax,ymax,xmin,ymax);
	dda(xmin,ymax,xmin,ymin);
	glEnd();
	glFlush();
	delay();
	glClear(GL_COLOR_BUFFER_BIT);
	//glPointSize(3);
	glBegin(GL_POINTS);
	glColor3f(0.0,1.0,0.0);
	dda(x11,y11,x22,y22);
	dda(xmin,ymin,xmax,ymin);
	dda(xmax,ymin,xmax,ymax);
	dda(xmax,ymax,xmin,ymax);
	dda(xmin,ymax,xmin,ymin);

	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{

	printf("Xmin, Ymin and Xmax,Ymax for window");
	scanf("%d%d",&xmin,&ymin);
	scanf("%d%d",&xmax,&ymax);


	printf("Enter Coordinates of  line: ");
	scanf("%d%d",&x1,&y1);
	scanf("%d%d",&x2,&y2);

	outcode_gen(outcode1,x1,y1);
	outcode_gen(outcode2,x2,y2);

	for(int i=0; i<4; i++)
	{
	printf("Outcode2%d\t",outcode2[i]);
	}
	printf("\n");
	for(int i=0; i<4; i++)
	{
	printf("Outcode1%d\t",outcode1[i]);
	}
	//line_status();

	line_clip();


	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);

	glutCreateWindow("Line clip");

	glClearColor(1.0,1.0,1.0,0);
	glColor3f(1.0,0.0,0.0);
	//glPointSize(3);
	gluOrtho2D(0,640,0,480);

	glutDisplayFunc(draw);

	glutMainLoop();

}
