#include<stdio.h>
#include<GL/glut.h>
int xc,yc,r;

int Round(float a)
{
	return(int)(a+0.5);
}

void ddaline(int xa,int ya,int xb,int yb)
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
	float xinc,yinc;
	xinc=dx/(float)(steps);
	yinc=dy/(float)(steps);
	
	float x,y;
	x=xa;
	y=ya;
	
	int i;
	glVertex2d(Round(x),Round(y));
	for(i=0;i<steps;i++)
	{
		x=x+xinc;
		y=y+yinc;
		glVertex2d(Round(x),Round(y));
	}	
}
void brescircle(int xc,int yc,int r)
{
	int x,y,d;
	x=0;
	y=r;
	d=3-2*r;
	
	do
	{
		glVertex2d(y+xc,x+yc);
		glVertex2d(x+xc,y+yc);
		glVertex2d(x+xc,-y+yc);
		glVertex2d(y+xc,-x+yc);
		glVertex2d(-y+xc,-x+yc);
		glVertex2d(-x+xc,-y+yc);
		glVertex2d(-x+xc,y+yc);
		glVertex2d(-y+xc,x+yc);
		
		if(d<0)
		{
			x=x+1;
			d=d+4*x+6;
		}
		else
		{
			x=x+1;
			y=y-1;
			d=d+4*x-4*y+10;
		}
	}while(y>=x);
}
	
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	ddaline(320,0,320,480);
	 ddaline(0,240,640,240);
		 //ddaline(-320,0,320,0);
	// ddaline(0,-240,0,240);
	 
	 
	 // brescircle(xc,yc,r);
	  
	  glEnd();
	  glFlush();
}
void mouseclick(int button, int state, int x, int y)
{
	y=480-y;
	  glBegin(GL_POINTS);
	  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	  {
	    
	    xc = x;
	    yc =y;
	    brescircle(xc,yc,r);
	  }

	  
	  glEnd();
	  glFlush();
  
}
int main(int argc,char **argv)
{

	printf("Enter the radius of circle:");
	scanf("%d",&r);
	/*printf("Enter the first and second pixel::");
	scanf("%d%d",&xc,&yc);*/
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Brehnamcircle");

	glClearColor(1.0,1.0,1.0,0);
	glColor3f(1.0,0.0,0.0);
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(draw);
	glutMouseFunc(mouseclick);
	glutMainLoop();

	return 0;
}
