#include <GL/glut.h> 
#include <stdlib.h> 
#include<math.h>
#include<stdio.h>

int x1,y0,x0,y1;

void swap(int* x0, int* y0,int* x1, int * y1,int* dx,int* dy)
{
	int temp = *x0;
	*x0=*x1;
	*x1=temp;
	(*dx)*=(-1);
	(*dy)*=(-1);
	temp = *y0;
	*y0=*y1;
	*y1=temp;
}

void slopeMore_above(int x0,int y0,int y1,int dy,int dx)
{
	int d= dy-2*dx;
	int incN = -2*dx;
	int incNE = 2*(dy-dx);
	int y =y0;
	int x=x0;
	glVertex2i (x,y);
	
	while(y<y1)
	{
		if(d<=0)
		{
			d+=incNE;
			x++;
		}
		else
		{
			d+=incN;
		}
		y++;
		glVertex2i (x,y);
	}
}
	
void slopeMore_below(int x0,int y0,int y1,int dy,int dx)
{
	int d = 2*dx - dy;
	int incSE = 2*dx + 2*dy;
	int decS = 2*(dx);
	int x = x0;
	int y = y0;
	glVertex2i (x,y);
	while(y>y1)
	{
		if (d>0)
		{
			x++;
			d+=incSE;
		}
		else
		{
			d+=decS;
		}
		y--;
		glVertex2i (x,y);
	}
}	
	
void slopeLess_below(int x0,int y0,int x1,int dy,int dx)	
{
	int d = 2*dy + dx;
	int incE = 2*dy;
	int decSE = 2*(dy+dx);
	int x=x0;
	int y=y0;
	glVertex2i (x,y);
	while(x<=x1)
	{
		if(d>0)
			d+=incE;
		else
		{
			d+=decSE;
			y--;
		}	
		x++;
		glVertex2i (x,y);
	}
}
	
void slopeLess_above(int x0,int y0,int x1,int dy,int dx)
{
	int d = 2*dy - dx;
	int incNE = 2*(dy-dx);
	int incE = 2*dy;
	int y=y0;
	int x=x0;
	glVertex2i (x,y);
	while(x<=x1)
	{
		if(d<=0)
			d+=incE;
		else
		{
			d+=incNE;
			y++;
		}	
		x++;
		glVertex2i (x,y);
	}
}	
	
void vertical_above(int x0,int y0,int y1)
{
	int y=y0;
	int x=x0;
	while(y<y1)
	{
		glVertex2i (x,y);
		y++;
	}
}	

void vertical_below(int x0,int y0,int y1)
{
	int y=y0;
	int x=x0;
	while(y>y1)
	{
		glVertex2i (x,y);
		y--;
	}
}	
	
void display(void)
{   
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glColor3f(1, 0, 0); 	
	glPointSize(3);
    	glBegin(GL_POINTS);
    	
		int dy = y1-y0;
		int dx=x1-x0;
		int flag=0;
		if(dx==0)
		{
			if(y1>y0)
				vertical_above(x0,y0,y1);
			else
				vertical_below(x0,y0,y1);
			flag=1;	
		}
		if(flag==0)
		{
			float m = dy/dx;
			if(abs(m)<=1)
			{
				if(x1<x0)
					swap(&x0,&y0,&x1,&y1,&dx,&dy);
				if(y1>y0)
					slopeLess_above(x0,y0,x1,dy,dx);
				else
					slopeLess_below(x0,y0,x1,dy,dx);
			}	
			else
			{
				if(x1<x0)
					swap(&x0,&y0,&x1,&y1,&dx,&dy);
				if(y1>y0)
					slopeMore_above(x0,y0,y1,dy,dx);
				else
					slopeMore_below(x0,y0,y1,dy,dx);		
			}
		}
	glEnd();
	glFlush();	
}


int main(int argc,char** argv)
{
	printf("Please input the Starting and Ending points for the line\nEnter only integer points for proper visualization!\n");
	printf("Enter initial coordinates!\n");
	scanf("%d%d",&x0,&y0);
	printf("Enter final coordinates!\n");
	scanf("%d%d",&x1,&y1); 
	glutInit(&argc,argv);
    	glutInitDisplayMode(GLUT_SINGLE);
   	glutInitWindowSize(640, 480);
    	glutCreateWindow("Line Drawing");
    	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
 	glutDisplayFunc(display);
//	glutIdleFunc(idle);
   	glutMainLoop();
}
