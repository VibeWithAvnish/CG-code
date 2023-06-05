#include<stdio.h>
#include<GL/glut.h>
int xa,ya,xb,yb;
int choice;
int Round(float a)
{
	return(float)(a+0.5);
}
void ddaline(int xa,int ya,int xb,int yb,int choice)
{
	int dx,dy,steps;
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
	float xincre,yincre;
	
	xincre=dx/(float)(steps);
	yincre=dy/(float)(steps);
	
	float x=xa;
	float y=ya;
	glVertex2d(Round(x),Round(y));
	
	glBegin(GL_POINTS);
	int i;
	for(i=0;i<steps;i++)
	{
		switch(choice)
		{
			case 1:  //simple line
				x=x+xincre;
				y=y+yincre;
				glVertex2d(Round(x),Round(y));
				break;
			case 2:  //dashed line
				if(i%6!=0)
				{
					glVertex2d(Round(x),Round(y));
				}
				x=x+xincre;
				y=y+yincre;
				break;
			case 3: //dot line
				if(i%2==0)
				{
					glVertex2d(Round(x),Round(y));
				}
				x=x+xincre;
				y=y+yincre;
				break;
			case 4: //solid line
				glPointSize(7.0);
				x=x+xincre;
				y=y+yincre;
				glVertex2d(Round(x),Round(y));
				break;	
		}
	}
	glEnd();
	glFlush();
}
void mouse(int button,int state,int x,int y)
{
	y=480-y;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		xa=x;
		ya=y;
	}
	if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
	{
		xb=x;
		yb=y;
		glColor3f(0.0,0.0,1.0);
		ddaline(xa,ya,xb,yb,choice);
	}
}
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
	
	ddaline(0,240,640,240,1);
	ddaline(320,0,320,480,1);
	
	/*glColor3f(0.0,0.0,1.0);
	ddaline(xa,ya,xb,yb,choice);*/
	glEnd();
	//glFlush();
}
void draw1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0);
	glBegin(GL_POINTS);
	ddaline(0,240,640,240,1);
	ddaline(320,0,320,480,1);
	glPointSize(3.0);
	glBegin(GL_POINTS);
	
	
	glEnd();
	//glFlush();
}
int main(int argc,char**argv)
{
	/*printf("enter the starting point:");
	scanf("%d%d",&xa,&ya);
	printf("enter the ending point:");
	scanf("%d%d",&xb,&yb);*/
	
	printf("\n1:simple line \t 2:dashed line \t  3:dot line \t  4:solid line");
	scanf("%d",&choice);
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("dda");
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	gluOrtho2D(0,640,0,480);
	//glutDisplayFunc(draw);
	if(choice==4)
	{
		glutDisplayFunc(draw1);
	}
	else
	{
		glutDisplayFunc(draw);
	}
	glutMouseFunc(mouse);
	glutMainLoop();
	
	return 0;
}


