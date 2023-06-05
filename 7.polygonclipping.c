#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <GL/glut.h>

int v, xmin, ymin, xmax, ymax;
int lv=0, rv=0, tv=0,bv=0;
int input[2][15];
int left[2][15];
int right[2][15];
int bottom[2][20];
int top[2][20];

int xa,ya,xb,yb;


void getdata(int input[2][15])
{
	for(int i=0; i<v; i++)
	{
		printf("x value: ");
		scanf("%d", &input[0][i]);
		
		printf("y value: ");
		scanf("%d", &input[1][i]);
	}
}


void left_clip(int xa, int ya, int xb, int yb)
{
	float m;
	int x,y;
	m=(yb-ya)/(float)(xb-xa);
	
	if(xa<xmin && xb>xmin)
	{
		x=xmin;
		y=ya+m*(x-xa);
		
		left[0][lv]=x;
		left[1][lv]=y;//intersection
		lv++;
		
		left[0][lv]=xb;
		left[1][lv]=yb;//second vertex
		lv++;
	}
	
	if(xa>xmin && xb>xmin)
	{
		
		left[0][lv]=xb;
		left[1][lv]=yb;//second vertex
		lv++;
	}
	
	if(xa>xmin && xb<xmin)
	{
		x=xmin;
		y=ya+m*(x-xa);
		
		left[0][lv]=x;
		left[1][lv]=y;//intersection
		lv++;
	}
	
	
}

void right_clip(int xa, int ya, int xb, int yb)
{
	float m;
	int x,y;
	m=(yb-ya)/(float)(xb-xa);
	
	if(xa<xmax && xb>xmax)
	{
		x=xmax;
		y=ya+m*(x-xa);
		
		right[0][rv]=x;
		right[1][rv]=y;//intersection
		rv++;
	
	}
	
	if(xa>xmax && xb<xmax)
	{
		
		x=xmax;
		y=ya+m*(x-xa);
		
		right[0][rv]=x;
		right[1][rv]=y;
		rv++;
		
		right[0][rv]=xb;
		right[1][rv]=yb;
		rv++;
		
	}
	
	if(xa<xmax && xb<xmax)
	{
		right[0][rv]=xb;
		right[1][rv]=yb;
		rv++;
	}
	
}

void bottom_clip(int xa, int ya, int xb, int yb)
{
	float m;
	int x,y;
	m=(yb-ya)/(float)(xb-xa);
	
	if(ya<ymin && yb>ymin)
	{
		y=ymin;
		x=xa+(y-ya)/m;
		
		bottom[0][bv]=x;
		bottom[1][bv]=y;
		bv++;
		
		
		bottom[0][bv]=xb;
		bottom[1][bv]=yb;
		bv++;
		
	}
	
	if(ya>ymin && yb>ymin)
	{
		
		bottom[0][bv]=xb;
		bottom[1][bv]=yb;
		bv++;
	}
	
	if(ya>ymin && yb<ymin)
	{
		y=ymin;
		x=xa+(y-ya)/m;
		
		bottom[0][bv]=x;
		bottom[1][bv]=y;
		bv++;
	}
	
	
}

void top_clip(int xa, int ya, int xb, int yb)
{
	float m;
	int x,y;
	m=(yb-ya)/(float)(xb-xa);
	
	if(ya<ymax && yb>ymax)
	{
		y=ymax;
		x=xa+(y-ya)/m;
		
		top[0][tv]=x;
		top[1][tv]=y;
		tv++;

		/*
		top[0][tv]=xa;
		top[1][tv]=ya;
		tv++;
		*/
	}
	
	if(ya<ymax && yb<ymax)
	{
		
		top[0][tv]=xb;
		top[1][tv]=yb;
		tv++;
	}
	
	if(ya>ymax && yb<ymax)
	{
		y=ymax;
		x=xa+(y-ya)/m;
		
		top[0][tv]=x;
		top[1][tv]=y;
		tv++;
		
		top[0][tv]=xb;
		top[1][tv]=yb;
		tv++;
	}
	
}


int Round(float a)
{
	return(int)(a+0.5);
}

void ddaline(int xa,int ya,int xb,int yb)
{
	int dx,dy,steps;
	dx = xb-xa;
	dy = yb-ya;
	if(abs(dx)>abs(dy))
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}


	float xincrement , yincrement;
	xincrement = dx/(float)(steps);
	yincrement = dy/(float)(steps);
	float x = xa;
	float y = ya;

	glVertex2d(Round(x),Round(y));

	for(int k = 0; k<steps; k++)
	{
		x=x+xincrement;
		y=y+yincrement;
		glVertex2d(Round(x),Round(y));
	}
}


void Draw()
{
 	int z;
 	
 	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
 	ddaline(xmin,ymin,xmax,ymin);
	ddaline(xmax,ymin,xmax,ymax);
	ddaline(xmax,ymax,xmin,ymax);
	ddaline(xmin,ymax,xmin,ymin);
	
	glColor3f(1.0,0.0,0.0);
	
	for(z=0; z<(v-1); z++)
	{
		ddaline(input[0][z],input[1][z],input[0][z+1],input[1][z+1]);
	}
		ddaline(input[0][z],input[1][z],input[0][0],input[1][0]);
	
 	glEnd();
	glFlush();
	
 	sleep(2);
 	
 	int u;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
	glColor3f(0.0,1.0,0.0);
	
	for(u=0; u<tv-1; u++)
	{
		ddaline(top[0][u],top[1][u],top[0][u+1],top[1][u+1]);
	}
		ddaline(top[0][u],top[1][u],top[0][0],top[1][0]);
		
	glEnd();
	glFlush();
}



int main(int argc,char **argv)
{
		
	printf("Enter value of Xmin and ymin: ");
	scanf("%d%d", &xmin, &ymin);
	
	printf("Enter value of Xmax and ymax: ");
	scanf("%d%d", &xmax, &ymax);
	
	printf("Enter total no. of vertices");
	scanf("%d" ,&v);
	
	getdata(input);
	int j;   	   		
	for (j=0; j<v-1; j++)
	{
		left_clip(input[0][j], input[1][j], input[0][j+1], input[1][j+1]);
	}   	   		
	   left_clip(input[0][j], input[1][j], input[0][0], input[1][0]); 
	   
	//Started clipping  
	int k;
	    for (k=0; k<lv-1; k++)
	{
		right_clip(left[0][k], left[1][k], left[0][k+1], left[1][k+1]);
	}   	   		
	   right_clip(left[0][k], left[1][k], left[0][0], left[1][0]); 
	  
	 
	
	 
	int m;
	    for (m=0; m<rv-1; m++)
	{
		bottom_clip(right[0][m], right[1][m], right[0][m+1], right[1][m+1]);
	}   	   		
	   bottom_clip(right[0][m], right[1][m], right[0][0], right[1][0]); 
	   
	 
	int n;
	    for (n=0; n<(bv-1); n++)
	{
		top_clip(bottom[0][n], bottom[1][n], bottom[0][n+1], bottom[1][n+1]);
	}   	   		
	   top_clip(bottom[0][n], bottom[1][n], bottom[0][0], bottom[1][0]);  
	   
	   
	   
	  /* 
	    printf("Top::: \n");
	      for(int j=0; j<2; j++)
	{
		for(int i=0; i<tv; i++)
		{
			printf("\t%d",top[j][i]);
		}
		printf("\n");
	}
	*/		
		
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//SET THE INITIAL DISPLAY MODE
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("DDA Program");
	glClearColor(0.0,0.0,0.0,0);//set clear color to white
	glColor3f(1.0,1.0,1.0);//set fill color to black
	gluOrtho2D(0,640,0,480);
	glutDisplayFunc(Draw);//CALL TO DISPLAYING FUNCTION
	glutMainLoop();//keep displaying until the programm is close
  	
  	return 0;
  }
