#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

int v;
float input[3][10]; 
float output[3][10];
float transl[3][3];
float scale[3][3];
float rotate[3][3];
float reflect[3][3];
float shear[3][3];

void getdata()
{
	 float x,y;
	 printf("Enter no of vertices: ");
	 scanf("%d",&v);
		
	 for (int j=0;j<v;j++)
	 {
	  printf("Enter coordinates: ");
	  scanf("%f%f",&x,&y);
	  input[0][j]=x;
	  input[1][j]=y;
	  input[2][j]=1;
	  
	  }
	
}

void translation()
{
		 float tx,ty;
		 printf("Enter vales of tx,ty: ");
		 scanf("%f%f",&tx,&ty);
			
		 for (int i=0;i<3;i++)
		 {
			  for (int j=0;j<3;j++)
			  {
			   if (i==j)
			    transl[i][j]=1;
			   else
			    transl[i][j]=0;
			  }
		  
		 }
		 transl[0][2]=tx;
		 transl[1][2]=ty; 
}
void scaling()
{
	 float sx,sy;
	 printf("Enter vales sx,sy: ");
	 scanf("%f%f",&sx,&sy);
	 float xf,yf;
	 printf("Enter vales for fixed point xf,yf: ");
	 scanf("%f%f",&xf,&yf);
		
	 for (int i=0;i<3;i++)
	 {
	  for (int j=0;j<3;j++)
	  {
	    scale[i][j]=0;
	  }
 	}
	 scale[0][0]=sx;
	 scale[1][1]=sy;
	 scale[2][2]=1;
	 scale[0][2]=xf*(1-sx);
	 scale[1][2]=yf*(1-sy);
}
	
	
void rotation()
{
	 float deg;
	 float rad;
	 float xr;
	 float yr;
	    printf("Enter the angle in degrees: ");
	    scanf("%f",&deg);
	    rad= (M_PI*deg)/180;
	    printf("Enter coordinates for pivot point: ");
	    scanf("%f%f",&xr,&yr);
	    rotate[0][0]=cos(rad);
	    rotate[0][1]=(-sin(rad));
	    rotate[0][2]=xr*(1-cos(rad))+yr*(sin(rad));
	    rotate[1][0]=sin(rad);
	    rotate[1][1]= cos(rad);
	    rotate[1][2]=yr*(1-cos(rad))-xr*(sin(rad));
	    rotate[2][0]=0;
	    rotate[2][1]=0;
	    rotate[2][2]=1;
    
}

void reflection()
{
		 int ref;
		 printf("Enter relection along which line :\n1.Along x-axis\n2.Along y-axis\n3.Along an axis that is perpendicular to x-y plane and passing through origin\n4.Along x=y\n5.Along x=-y");
		 scanf("%d",&ref);
		 for (int i=0;i<3;i++)
		 {
		  for (int j=0;j<3;j++)
		  {
		   reflect[i][j]=0;
		   
		  }
		 }
			
		 if (ref==1)
		 {
			
	  reflect[0][0]=1;
	  reflect[1][1]=-1;
	  reflect[2][2]=1;
	 }
	 else if (ref==2)
	 { 
	  reflect[0][0]=-1;
	  reflect[1][1]=1;
	  reflect[2][2]=1;
	 }
	 else if(ref==3)
	 {
	  reflect[0][0]=-1;
	  reflect[1][1]=-1;
	  reflect[2][2]=1;
	 }
	 else if(ref==4)
	 {
		  reflect[0][1]=1;
		  reflect[1][0]=1;
		  reflect[2][2]=1;
		 }
		 else if(ref==5)
		 {
		  reflect[0][1]=-1;
		  reflect[1][0]=-1;
		  reflect[2][2]=1;
		 }
		   
	
	
}

void shearing()
{
	 int ch;
	 float shx,shy;
	 for (int i=0;i<3;i++)
	 {
	  for (int j=0;j<3;j++)
	  {
	   shear[i][j]=0;
	   if(i==j)
	   {
	    shear[i][j]=1;
	   }
	  }
	 }
		
	 printf("Enter which shearing:\n1.X-direction\n2.Y-direction");
	 scanf("%d",&ch);
		
	 if(ch==1)
	 {
	  printf("Enter shearing force in x-direction: ");
	  scanf("%f",&shx);
	  shear[0][1]=shx;
	 }
	 if(ch==2)
	 {
	  printf("Enter shearing force in y-direction: ");
	  scanf("%f",&shy);
	  shear[1][0]=shy;
	 }
		
}


void multiply(float in[3][10],float out[3][10], float t [3][3])
{ 
 float outp;
 for (int c = 0; c < 3; c++) 
 {
        for (int d = 0; d < v; d++) 
        {
         out[c][d]=0;
         outp=0;
          for (int k = 0; k < 3; k++) 
          {
              outp = outp + (t[c][k] * in[k][d]);
          }
          out[c][d]=outp;
          outp=0;
          
  }
 }
	
}

int Round(float a)
{
  return (int)(a + 0.5);
}

void ddaline (int xa, int ya, int xb, int yb) 
{
  int dx,dy,steps;
  dx =xb-xa;
  dy =yb-ya;
  if (abs(dx)> abs(dy)){
    steps = abs(dx);
  }
  else {
    steps =abs (dy);
  }
  float xinc, yinc;
  xinc =dx/(float)(steps);
  yinc=dy/(float)(steps);
  
  float x= xa;
  float y= ya;
  
  glVertex2d(Round(x),Round(y));
  
  for (int k=0;k<steps;k++)
  {
    x=x+xinc;
    y=y+yinc;
    glVertex2d(Round(x),Round(y));
  }
  
}

void Draw()
{

 glClear(GL_COLOR_BUFFER_BIT);
 glBegin(GL_POINTS);
 int i;
 glColor3f(1.0,1.0,1.0);
 ddaline(0,240,640,240);
 ddaline(320,480,320,0);
 glColor3f(1.0,0.0,0.0);
 for (i=0;i<v-1;i++)
 {
  ddaline(320+(input[0][i]),240+(input[1][i]),320+(input[0][i+1]),240+(input[1][i+1]));
 }
 ddaline(320+(input[0][i]),240+(input[1][i]),320+(input[0][0]),240+(input[1][0]));
 glColor3f(0.0,0.0,1.0);
 for (i=0;i<v-1;i++)
 {
  ddaline(320+(output[0][i]),240+(output[1][i]),320+(output[0][i+1]),240+(output[1][i+1]));
 }
 ddaline(320+(output[0][i]),240+(output[1][i]),320+(output[0][0]),240+(output[1][0]));
	
 glEnd();
 glFlush();
}


int main (int argc , char **argv)
{
 int choice;
 int m;
 getdata();
	
 printf("Enter which operation is to be performed: \n1.Translation\n2.Scaling\n3.Rotation\n4.Reflection\n5.Shear\n");
 scanf("%d",&choice);
 if (choice==1)
 {
  translation();
  multiply(input,output,transl);
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("2dTransformation");
  glClearColor(0.0,0.0,0.0,0);  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(Draw);
    glutMainLoop();     
 }
 else if (choice==2)
 {
  scaling();
  multiply(input,output,scale);
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("2dTransformation");
  glClearColor(0.0,0.0,0.0,0);  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(Draw);
    glutMainLoop();     
 }
 else if (choice==3)
 {
  rotation();
  multiply(input,output,rotate);
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("2dTransformation");
  glClearColor(0.0,0.0,0.0,0);  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(Draw);
    glutMainLoop();    
   } 
 else if (choice==4)
 {
  reflection();
  multiply(input,output,reflect);
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("2dTransformation");
  glClearColor(0.0,0.0,0.0,0);  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(Draw);
    glutMainLoop();     
 }
 else if (choice==5)
 {
  shearing();
  multiply(input,output,shear);
  glutInit(&argc, argv);  
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("2dTransformation");
  glClearColor(0.0,0.0,0.0,0);  
  gluOrtho2D(0,640,0,480);
  glutDisplayFunc(Draw);
    glutMainLoop();     
 }
 else
 {
  printf("Enter valid number!!");
 }
}
	

