#include <iostream>
#include <cmath>
#include<ctime>
#include <sstream>
#include <string>
#include <GL/glut.h>
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
using namespace std;

class coin
{
	private:
		float x;
		float y;
		float vely;
		float velx;
		float rad;
		float red;
		float blue;
		float green;
                float accx;
		float accy;
		int flag;
	public:
                coin(float radius, float xCor,float yCor,float redG, float greenG,float blueG)
                {
			flag=1;
                        rad=radius;
                        x=xCor;
                        y=yCor;
                        velx=0;
                        vely=0;
                        accx=0.001f;
			accy=0.001f;
                        red=redG;
                        blue=blueG;
                        green=greenG;
                }
		int getFlag()
		{
			return this->flag;
		}
		float getRad()
		{
			return this->rad;
		}
		float getRed()
		{
			return this->red;
		}
		float getGreen()
                {
                        return this->green;
                }
	 	float getBlue()
                {
                        return this->blue;
                }

                float getVelx()
                {
                        return this->velx;
                }
                float getVely()
                {
                        return this->vely;
                }
                float getx()
                {
                        return this->x;
                }
                float gety()
                {
                        return this->y;
                }
                float getAccx()
		{
			return (this->accx)*cos(atan((this->vely)/(this->velx)));
		}
		float getAccy()
		{
			return (this->accy)*sin(atan((this->vely)/(this->velx)));
		}
                void changeVelxBy(float x,int flag)
                {
                        if(flag==1)//To increase velocity x
                                this->velx=this->velx+x;
                        else//To decrease velocity
                                this->velx=this->velx-x;
                }
                void changeVelyBy(float y,int flag)
                {
                        if(flag==1)//To increase velocity y
                                this->vely=this->vely+y;
                        else//To decrease velocity
                                this->vely=this->vely-y;
                }
                void setVelx(float x)
                {
                        this->velx=x;
                }
                void setVely(float y)
                {
                        this->vely=y;
                }
                void setx(float x)
                {
                        this->x=x;
                }
                void sety(float y)
                {
                        this->y=y;
                }
};

class box
{
	private:
		float len;
		float red;
		float green;
		float blue;
	public:
		box(float l, float r, float g, float b)
		{
			len=l;
			red=r;
			green=g;
			blue=b;
		}
		float getLen()
                {
                        return this->len;
                }
                float getRed()
                {
                        return this->red;
                }
                float getGreen()
                {
                        return this->green;
                }
                float getBlue()
                {
                        return this->blue;
                }
};

class hole
{
	private:
		float rad;
		float x;
		float y;
		int flag;
	public:
		hole(float xCor,float yCor)
		{
			x=xCor;
			y=yCor;
			rad=0.2f;
			flag=0;
		}
		float getRad()
		{
			return this->rad;
		}
		float getx()
		{
			return this->x;
		}
		float gety()
		{
			return this->y;	
		}
		int getFlag()
		{
			return this->flag;
		}
};

// Function Declarations
void drawScene();
void update(int value);
void handleCollision();
void drawBox(box box1);
void drawbox(box box1);
void drawCoin(coin coin1);
void drawHole(hole hole1);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void handleMouseActiveMotion(int x,int y);
void output(int x, int y, float r, float g, float b, string str);
void mousemove(int x);
void powerstriker(int x,int y);


coin null(0.0f,-10.0f,0.0f,0.0f,0.0f,0.0f);
coin coin1(0.125f,0.56f,0.0f,0.0f,0.0f,0.0f);
coin coin2(0.125f,0.4f,0.4f,1.0f,1.0f,1.0f);
coin coin3(0.125f,0.0f,0.56f,0.0f,0.0f,0.0f);
coin coin4(0.125f,0.0f,-0.56f,1.0f,1.0f,1.0f);
coin coin5(0.125f,-0.4f,-0.4f,0.0f,0.0f,0.0f);
coin coin6(0.125f,-0.56f,0.0f,1.0f,1.0f,1.0f);
coin coin7(0.125f,-0.4f,0.4f,0.0f,0.0f,0.0f);
coin coin8(0.125f,0.4f,-0.4f,1.0f,1.0f,1.0f);
coin coin9(0.125f,0.0f,0.0f,1.0f,0.0f,0.0f);

coin coins[9]={coin1,coin2,coin3,coin4,coin5,coin6,coin7,coin8,coin9};

coin striker(0.175f,0.0f,-2.0f,0.0f,0.0f,1.0f);

box outer(6.0f,0.35f, 0.14f, 0.08f);
box inner(5.5f,1.0f, 0.871f, 0.678f);

box inside(4.175f,0.0f,0.0f,1.0f);

hole hole1 = hole(2.5f,2.5f);
hole hole2 = hole(2.5f,-2.5f);
hole hole3 = hole(-2.5f,2.5f);
hole hole4 = hole(-2.5f,-2.5f);

hole holes[4]={hole1,hole2,hole3,hole4};

float angleOfMarker=0;
float velOfMarker=0.0f;
float lenStart=0.2f;
float started=0;
int score = 0;
int flag=1;
clock_t start=clock(),end;
int but;

int main(int argc, char **argv) {

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    int w = glutGet(GLUT_SCREEN_WIDTH);
    int h = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = w * 2 / 3;
    int windowHeight = h * 2 / 3;

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

    glutCreateWindow("Carrom Board - Nurendra Choudhary - 201325186");  // Setup the window
    initRendering();

    // Register callbacks
    glutDisplayFunc(drawScene);
    glutIdleFunc(drawScene);
    glutKeyboardFunc(handleKeypress1);
    glutSpecialFunc(handleKeypress2);
    glutMouseFunc(handleMouseclick);
    glutMotionFunc(handleMouseActiveMotion);
    glutReshapeFunc(handleResize);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}

// Function to draw objects on the screen
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    // Draw Box
    glTranslatef(0.0f, 0.0f, -8.0f);
    glColor3f(outer.getRed(), outer.getGreen(), outer.getBlue());
    drawBox(outer);
  

    glPushMatrix(); 
    glTranslatef(0.0f, 0.0f, 0.0f);
    glColor3f(inner.getRed(), inner.getGreen(), inner.getBlue());
    drawBox(inner);
     
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glColor3f(0.0f,1.0f,0.0f);
    drawbox(inside);
    glPopMatrix();    
    
    glPushMatrix();
    glTranslatef(0.0f,0.0f,0.0f);
    glColor3f(0.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLE_FAN);
        for(int i=0 ; i<360 ; i++) {
                glVertex2f((0.8) * cos(DEG2RAD(i)), (0.8) * sin(DEG2RAD(i)));
        }
        glEnd();
 
    glPopMatrix();
    // Draw Coins
    for(int i=0;i<9;i++)
    {
    	glPushMatrix();
    	glTranslatef(coins[i].getx(), coins[i].gety(), 0.0f);
    	glColor3f(coins[i].getRed(), coins[i].getGreen(), coins[i].getBlue());
    	drawCoin(coins[i]);
    	glPopMatrix();
    }
    
    //Draw Striker
    glPushMatrix();
    glTranslatef(striker.getx(), striker.gety(), 0.0f);
    glColor3f(striker.getRed(), striker.getGreen(), striker.getBlue());
    drawCoin(striker);
    glPopMatrix();
    
    if(started==0)
    {
    //Draw Striker marker
    glPushMatrix();
    glTranslatef(striker.getx(),striker.gety(),0.0f);
    glRotated(angleOfMarker,0.0f,0.0f,1.0f);
    glColor3f(0.1f, 0.5f, 0.5f);
    glBegin(GL_LINES);
    	glVertex3f(0.0f, 0.0f,0.0f);
    	glVertex3f(lenStart+(3*velOfMarker), lenStart+(3*velOfMarker),0.0f); 
    glEnd(); 
    glPopMatrix();
    }
    for(int i=0;i<4;i++)
    {
    	glPushMatrix();
    	glTranslatef(holes[i].getx(),holes[i].gety(), 0.0f);
    	glColor3f(0.0f, 0.0f, 0.0f);
    	drawHole(holes[i]);
    	glPopMatrix();
    }
    flag=1;
    for(int i=0;i<9;i++)
    {
	if(fabs(coins[i].getRad()) > 0.00001)
		flag=0;
    }
  //  cout<<flag<<endl; 
    if(flag==0)
    {
	    glPushMatrix();
	    end=clock();
	    double clk=double(((end-start)/CLOCKS_PER_SEC))*2.5;
	    int s = score - (int)clk; 
	    stringstream ss;
	    ss << s;
	    string str = ss.str();
	    string a="Score: ";
	    a.append(str);
	    string b="\nTimer:\n";
	    stringstream sd;
	    sd << clk;
	    string sf = sd.str();
	    b.append(sf);
	    b.append("s.");
	    output(4.0f,3.0f,1.0f,0.0f,3.0f,a);
	    output(2.0f,3.0f,1.0f,0.0f,3.0f,b);
	    glPopMatrix();
    }
    else
    {
	    glPushMatrix();
            stringstream ss;
	    ss << score;
            string str = ss.str();
            string a="Score: ";
            a.append(str);
//            cout<<"Game Over"<<endl;
            string b = "GAME OVER!!!";
            string c = "Press 'R' to start again";
            output(3.0f,3.0f,1.0f,0.0f,3.0f,a);
            output(3.0f,1.0f,1.0f,0.0f,0.0f,b);
            output(3.0f,-1.0f,1.0f,0.0f,3.0f,c);
            glPopMatrix();
    }
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}


void output(int x, int y, float r, float g, float b, string str)
{
	glColor3f(r,g,b);
	glRasterPos2f(x,y);
	int len;
	len = str.length();
	for(int k=0;k<len;k++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[k]);
	}
}
// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
	// Handle ball collisions with box
	for(int i=0;i<9;i++)
	{
		if(coins[i].getx()+coins[i].getRad()>inner.getLen()/2 || coins[i].getx()-coins[i].getRad()<-1*inner.getLen()/2)
			coins[i].setVelx(-(0.8)*coins[i].getVelx());
		if(coins[i].gety()+coins[i].getRad()>inner.getLen()/2 || coins[i].gety()-coins[i].getRad()<-1*inner.getLen()/2)
			coins[i].setVely(-(0.8)*coins[i].getVely());
	}
	if(striker.getx()+striker.getRad()>inner.getLen()/2 || striker.getx()-striker.getRad()<-1*inner.getLen()/2)
		striker.setVelx(-(0.8)*striker.getVelx());
	if(striker.gety()+striker.getRad()>inner.getLen()/2 || striker.gety()-striker.getRad()<-1*inner.getLen()/2 ) 
		striker.setVely(-(0.8)*striker.getVely());

	//Handle ball collisions with holes
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(sqrt(((coins[i].getx()-holes[j].getx())*(coins[i].getx()-holes[j].getx()))+((coins[i].gety()-holes[j].gety())*(coins[i].gety()-holes[j].gety()))) <= coins[i].getRad()+holes[j].getRad())
			{
				if(coins[i].getRed()==0.0f && coins[i].getGreen()==0.0f && coins[i].getBlue()==0.0f)
					score+=20;
				else if(coins[i].getRed()==1.0f && coins[i].getGreen()==1.0f && coins[i].getBlue()==1.0f)
					score+=30;
				else
					score+=50;
				coins[i]=null;
			}
		}
	}
	for(int j=0;j<4;j++)
	{
		if(sqrt(((striker.getx()-holes[j].getx())*(striker.getx()-holes[j].getx()))+((striker.gety()-holes[j].gety())*(striker.gety()-holes[j].gety()))) <= striker.getRad()+holes[j].getRad())
		{
			score-=5;
			striker.setVelx(0.0f);
			striker.setVely(0.0f);
			striker.setx(0.0f);
			striker.sety(-2.0f);
			lenStart=0.2f;
			started=0;
		}

	}

	//Handle coin-coin and striker-coin collision
	for(int i=0;i<9;i++)
	{
		if(sqrt(pow(coins[i].getx()-striker.getx(),2)+pow(coins[i].gety()-striker.gety(),2)) <= striker.getRad() + coins[i].getRad())
		{
			float angle=atan((coins[i].gety()-striker.gety())/(coins[i].getx()-striker.getx()));
			float si=sin(angle);
			float co=cos(angle);
			float bll1_velx=coins[i].getVelx();
			float bll1_vely=coins[i].getVely();
			float bll2_velx=striker.getVelx();
			float bll2_vely=striker.getVely();
			coins[i].setVelx((bll1_velx*si-bll1_vely*co)*si + (bll2_velx*co+bll2_vely*si )*co);
			striker.setVelx((bll2_velx*si-bll2_vely*co)*si + ( bll1_velx*co+bll1_vely*si)*co);
			coins[i].setVely(-1*(bll1_velx*si-bll1_vely*co)*co + (bll2_velx*co+bll2_vely*si )*si);
			striker.setVely((bll2_velx*si-bll2_vely*co)*co - ( bll1_velx*co+bll1_vely*si)*si); 
		}
	}
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(i!=j)
			{
				if(sqrt(pow(coins[i].getx()-coins[j].getx(),2)+pow(coins[i].gety()-coins[j].gety(),2))<=coins[j].getRad()+coins[i].getRad())
				{
					float angle=atan((coins[i].gety()-coins[j].gety())/(coins[i].getx()-coins[j].getx()));
					float si=sin(angle);
					float co=cos(angle);
					float bll1_velx=coins[i].getVelx();
					float bll1_vely=coins[i].getVely();
					float bll2_velx=coins[j].getVelx();
					float bll2_vely=coins[j].getVely();
					coins[i].setVelx((bll1_velx*si-bll1_vely*co)*si + (bll2_velx*co+bll2_vely*si )*co);
					coins[j].setVelx((bll2_velx*si-bll2_vely*co)*si + ( bll1_velx*co+bll1_vely*si)*co);
					coins[i].setVely(-1*(bll1_velx*si-bll1_vely*co)*co + (bll2_velx*co+bll2_vely*si )*si);
					coins[j].setVely((bll2_velx*si-bll2_vely*co)*co - ( bll1_velx*co+bll1_vely*si)*si);
				}

			}
		}
	}

	// Update velocities of coins and striker
	if(striker.getVelx()*(striker.getVelx()-striker.getAccx())>=0 && started==1)
	{
		if(striker.getVelx()>0)
			striker.setVelx(striker.getVelx()-striker.getAccx());
		else
			striker.setVelx(striker.getVelx()+striker.getAccx());
	}
	else
		striker.setVelx(0.0f);
	if(striker.getVely()*(striker.getVely()-striker.getAccy())>=0 && started==1)
	{
		if(striker.getVely()>0)
			striker.setVely(striker.getVely()-striker.getAccy());
		else
			striker.setVely(striker.getVely()+striker.getAccy());
	}
	else
		striker.setVely(0.0f);
	if(striker.getVelx()==0 && striker.getVely()==0 && started==1)
	{
		striker.setx(0.0f);
		striker.sety(-2.0f);
		lenStart=0.2f;
		started=0;
	}
	for(int i=0;i<9;i++)
	{
		if(coins[i].getVelx()*(coins[i].getVelx()-coins[i].getAccx())>=0 && started==1)
			coins[i].setVelx(coins[i].getVelx()-coins[i].getAccx());
		else
			coins[i].setVelx(0.0f);
		if(coins[i].getVely()*(coins[i].getVely()-coins[i].getAccy())>=0 && started==1)
			coins[i].setVely(coins[i].getVely()-coins[i].getAccy());
		else
			coins[i].setVely(0.0f);
	}
	// Update position of coins and striker 
	striker.setx(striker.getx()+striker.getVelx());
	striker.sety(striker.gety()+striker.getVely());
	for(int i=0;i<9;i++)
	{
		coins[i].setx(coins[i].getx()+coins[i].getVelx());
		coins[i].sety(coins[i].gety()+coins[i].getVely());
	}

	glutTimerFunc(10, update, 0);
}
void drawBox(box box1) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
	glVertex2f((-1 * box1.getLen()) / 2, (-1 * box1.getLen()) / 2);
	glVertex2f((box1.getLen()) / 2, (-1 * box1.getLen()) / 2);
	glVertex2f((box1.getLen()) / 2, (box1.getLen()) / 2);
	glVertex2f((-1*box1.getLen()) / 2, (box1.getLen()) / 2);
	glEnd();
}

void drawbox(box box1) {

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glVertex2f((-1 * box1.getLen()) / 2, (-1 * box1.getLen()) / 2);
	glVertex2f((box1.getLen()) / 2, (-1 * box1.getLen()) / 2);
	glVertex2f((box1.getLen()) / 2, (box1.getLen()) / 2);
	glVertex2f((-1*box1.getLen()) / 2, (box1.getLen()) / 2);
	glEnd();
}


void drawCoin(coin coin1) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f((coin1.getRad()) * cos(DEG2RAD(i)), (coin1.getRad()) * sin(DEG2RAD(i)));
	}
	glEnd();
}

void drawHole(hole hole1)
{
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f((hole1.getRad()) * cos(DEG2RAD(i)), (hole1.getRad()) * sin(DEG2RAD(i)));
	}
	glEnd();
}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

    if (key == 27) {
        exit(0);     // escape key is pressed
    }
    if (key == 97) {
        angleOfMarker+=2;
        if(angleOfMarker > 130)
            angleOfMarker = 130;
    }
    if (key == 99)
    {
	angleOfMarker-=2;
    	if(angleOfMarker < -40)
            angleOfMarker = -40;
    }
    if (key == 114)
    {
	coins[0] = coin1;
        coins[1] = coin2;
	coins[2] = coin3;
	coins[3] = coin4;
	coins[4] = coin5;
	coins[5] = coin6;
        coins[6] = coin7;
        coins[7] = coin8;
        coins[8] = coin9;
        striker.setx(0.0f);
        striker.sety(-2.0f);
        angleOfMarker=0;
	velOfMarker=0.0f;
	lenStart=0.2f;
	started=0;
	score = 0;
        flag=1;
	start=clock();
    }
    if (key == 32)
    {
        score-=5;
        started=1;
	if(striker.getVelx()==0 && striker.getVely()==0)
	{
		striker.setVelx(velOfMarker*(cos((angleOfMarker+45)*PI/180.0)));
		striker.setVely(velOfMarker*(sin((angleOfMarker+45)*PI/180.0)));
	}
    }
}

void handleKeypress2(int key, int x, int y) {

    if (key == GLUT_KEY_LEFT)
    {
	if(striker.getx()-0.1 >= -2.08f)
  		striker.setx(striker.getx()-0.1);
        
    }
    if (key == GLUT_KEY_RIGHT)
    {
	if(striker.getx()+0.1 <= 2.08f)
        	striker.setx(striker.getx()+0.1);
    }
    if (key == GLUT_KEY_UP)
    {
	velOfMarker+=0.04f;
	if(velOfMarker > 0.2f)
		velOfMarker=0.2f;
    }
    if (key == GLUT_KEY_DOWN)
    {
	velOfMarker-=0.04f;
	if(velOfMarker < 0.0f)
		velOfMarker=0.0f;
    }
}


void handleMouseclick(int button, int state, int x, int y) {

	if ((state == GLUT_UP))
	{
		but=100;
		if (button == GLUT_LEFT_BUTTON) {
			score-=5;
			started=1;
			if(striker.getVelx()==0 && striker.getVely()==0)
			{
				striker.setVelx(velOfMarker*(cos((angleOfMarker+45)*PI/180.0)));
				striker.setVely(velOfMarker*(sin((angleOfMarker+45)*PI/180.0)));
			}

		}
	}
	if ((state == GLUT_DOWN))
	{
		but=button;	
	}

}


void handleMouseActiveMotion(int x, int y) {

	if(but==GLUT_RIGHT_BUTTON) {
		mousemove(x);
	}
	if(but==GLUT_LEFT_BUTTON)
		powerstriker( x, y);

}
void mousemove(int x)
{
	if(started!=1)
        {
		if((x*10.0/glutGet(GLUT_WINDOW_WIDTH)-5.0)<=2.08f && (x*10.0/glutGet(GLUT_WINDOW_WIDTH)-5.0)>=-2.08f) 
			striker.setx(x*10.0/glutGet(GLUT_WINDOW_WIDTH)-5.0);
	}
}
void powerstriker(int x,int y)
{
	if(started==1)
		return;
	x=x*15.0/glutGet(GLUT_WINDOW_WIDTH)-7.5;
	y=y*7.5/glutGet(GLUT_WINDOW_HEIGHT)-3.75;
	angleOfMarker=atan((x-striker.getx())/(y-striker.gety()))*(-180.0/PI)+45;
	velOfMarker=((5*sqrt(0.001*sqrt(pow(x-striker.getx(),2)+pow(y-striker.gety(),2)))/0.03))/60;
        cout<<velOfMarker<<endl;
	if(velOfMarker>0.2f)
		velOfMarker=0.2f;
	if(velOfMarker<0.0f)
		velOfMarker=0.0f;
}
