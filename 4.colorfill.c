#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>

int v ,poly[2][10];
float bound[3][10];
float boundary[3],fill[3],bc[3];
int xin=0,yin=0;
int q;

int roundoff(float val)
{
	return val+0.5;
}
void ddaline(int xa,int ya,int xb,int yb){
	int dx=xb-xa;
	int dy=yb-ya;
	int steps;
	if(abs(dx)>abs(dy)){
		steps=abs(dx);
	}
	else{
		steps=abs(dy);
	}
	float xin=dx/(float)(steps);
	float yin=dy/(float)(steps);
	float x=xa;
	float y=ya;
	glBegin(GL_POINTS);
	glVertex2d(roundoff(x),roundoff(y));
	for(int i=0;i<steps;i++){
		x=x+xin;
		y=y+yin;
		glVertex2d(roundoff(x),roundoff(y));
	}
	
}

void floodfill(int x,int y,float bc[3],float fil[3])
{
		float col[3];
		glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,col);
		
		if((col[0]==bc[0] && col[1]==bc[1] && col[2]==bc[2])&&(col[0]!=fill[0] || col[1]!=fill[1] || col[2]!=fill[2]))
		{
			glColor3f(fill[0],fill[1],fill[2]);
			glBegin(GL_POINTS);
			glVertex2d(x,y);
			glEnd();
			glFlush();
		
			floodfill(x+2,y,bc,fill);
			floodfill(x-2,y,bc,fill);
			floodfill(x,y+2,bc,fill);
			floodfill(x,y-2,bc,fill);
		}
}

void boundaryfill(int x,int y,float boundary[3],float fill[3])
{
	float color[3];
	glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,color);
	
	if((color[0]!=boundary[0] || color[1]!=boundary[1] || color[2]!=boundary[2])&&(color[0]!=fill[0] || color[1]!=fill[1] || color[2]!=fill[2]))
	 //if((color[0]!=boundary[0] || color[1]!=boundary[1] || color[2]!=boundary[2])&&(color[0]!=fill[0] || color[1]!=fill[1] || color[2]!=fill[2]))
		{
			glColor3f(fill[0],fill[1],fill[2]);
			glBegin(GL_POINTS);
			glVertex2d(x,y);
			glEnd();
			glFlush();
			
			boundaryfill(x+2,y,boundary,fill);
			boundaryfill(x-2,y,boundary,fill);
			boundaryfill(x,y+2,boundary,fill);
			boundaryfill(x,y-2,boundary,fill);
		}
}

void myMouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
         
         xin = x;
         yin = 480-y;
         if(q==1){
         	boundaryfill(xin,yin,boundary,fill);
         }
         else if(q==2){
            floodfill(xin,yin,bc,fill);
         }
     }

}

void polygon(){
	
	
}
void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3);
	glBegin(GL_POINTS);
	int i;
	glColor3f(boundary[0],boundary[1],boundary[2]);
	for(i=0;i<v-1;i++){
		ddaline(poly[0][i],poly[1][i],poly[0][i+1],poly[1][i+1]);
	}
	ddaline(poly[0][0],poly[1][0],poly[0][i],poly[1][i]);
	glutMouseFunc(myMouse);
	glEnd();
	glFlush();
}


void draw1()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3);
	glBegin(GL_POINTS);
	int i;
	for(i=0;i<v-1;i++){
		glColor3f(bound[0][i],bound[1][i],bound[2][i]);
		ddaline(poly[0][i],poly[1][i],poly[0][i+1],poly[1][i+1]);
	}
	glColor3f(bound[0][i],bound[1][i],bound[2][i]);
	ddaline(poly[0][0],poly[1][0],poly[0][i],poly[1][i]);
	glutMouseFunc(myMouse);
	glEnd();
	glFlush();

}
int main(int argc,char **argv){
	printf("enter no.of vertex");
	scanf("%d",&v);
	int val;
	for(int i=0; i<v;i++){
		printf("enter x of vertex");
		scanf("%d",&val);
		poly[0][i]=val;
		printf("enter y of vertex");
		scanf("%d",&val);
		poly[1][i]=val;
	
	}
	
	printf("enter the background color: ");
	for(int i=0; i<3;i++)
	{
		scanf("%f",&bc[i]);	
	}
	printf("enter the boundary color: ");
	for(int i=0; i<3;i++)
	{
		scanf("%f",&boundary[i]);	
	}
	
	for(int i=0; i<v;i++){
	printf("Enter the color of the side in RGB format\n");
		scanf("%f",&bound[0][i]);
		scanf("%f",&bound[1][i]);
		scanf("%f",&bound[2][i]);
	}
	printf("enter the fill color: ");	
	for(int i=0; i<3;i++)
	{
		scanf("%f",&fill[i]);	
	}printf("enter what to do :: 1=boundaryfill 2=floodfill");
	scanf("%d",&q);
	
	/*printf("inside x co-ordinate::");
	scanf("%d",&xin);
	printf("inside y co-ordinate::");
	scanf("%d",&yin);*/
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("polygon");
	glClearColor(bc[0],bc[1],bc[2],0.0);
	glColor3f(0.0,0.0,0.0);
	gluOrtho2D(0,640,0,480);
	if(q==1)
	{
		glutDisplayFunc(draw);
	}
	else if(q==2)
	{
		glutDisplayFunc(draw1);
	}
	glutMainLoop();
	return 0;
	
}






















