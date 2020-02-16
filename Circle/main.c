#include <GL/glut.h> 
#include <stdlib.h>
#include<stdio.h> 
	
int radius,xcentre,ycentre;	
	
void plotCirclePoints(int x,int y)
{
	glVertex2i (x+xcentre,y+ycentre);
	glVertex2i (x*(-1)+xcentre,y+ycentre);
	glVertex2i (x+xcentre,y*(-1)+ycentre);
	glVertex2i ((-1)*x+xcentre,y*(-1)+ycentre);
	glVertex2i (y+xcentre,x+ycentre);
	glVertex2i (y*(-1)+xcentre,x+ycentre);
	glVertex2i (y+xcentre,(-1)*x+ycentre);
	glVertex2i ((-1)*y+xcentre,(-1)*x+ycentre);
}	
	
void display(void)
{
        
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    	glColor3f(1,0, 0); 	
	glPointSize(3);
    	glBegin(GL_POINTS);
	int x=0,y=radius;
	int d =1-radius;
	int deltaE= 3;
	int deltaSE = 2*(-1)*radius + 5;
	plotCirclePoints(x,y);
	while(y>x)
	{
		if(d<0)
		{
			d+=deltaE;
			deltaE+=2;
			deltaSE+=2;
		}
		else
		{
			d+=deltaSE;
			deltaSE+=4;
			deltaE+=2;
			y--;
		}
		plotCirclePoints(x,y);
		x++;
	}
	glEnd();

	glFlush();	
}


int main(int argc,char** argv)
{
	printf("Enter the coordinates of the centre\n");
	scanf("%d%d",&xcentre,&ycentre);
	printf("Please enter radius\nIt should be an integer between 0 and 150\n");
	scanf("%d",&radius);
	
	glutInit(&argc,argv);
    	glutInitDisplayMode(GLUT_SINGLE);
   	glutInitWindowSize(640,480); 
    	glutCreateWindow("Circle Drawing");
    	glClearColor(0,1,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
 	glutDisplayFunc(display);
   	glutMainLoop();
}
