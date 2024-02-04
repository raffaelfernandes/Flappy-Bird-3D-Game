#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <iostream>
#include <stdio.h>

class Object{
private:
    float xCoord;  
    float yCoord;  
    float zCoord; 
    
public:
    Object() : xCoord(0.0f), yCoord(0.0f), zCoord(0.0f) {}

    Object(float x, float y, float z) : xCoord(x), yCoord(y), zCoord(z) {}
    
    float getXCoord() const {
        return xCoord;
    }

    float getYCoord() const {
        return yCoord;
    }

    float getZCoord() const {
        return zCoord;
    }

    void setXCoord(float x) {
        xCoord = x;
    }

    void setYCoord(float y) {
        yCoord = y;
    }

    void setZCoord(float z) {
        zCoord = z;
    }
};

class Player : public Object {
private:
    bool isJumping;

public:
    Player() : Object(), isJumping(false) {}

    Player(float x, float y, float z, bool jumping) : Object(x, y, z), isJumping(jumping) {}

    bool getIsJumping() const {
        return isJumping;
    }

    void setIsJumping(bool jumping) {
        isJumping = jumping;
    }
 	
 	void drawPlayer(bool lavenderHaze){
 		glPushMatrix();
			glTranslatef(getXCoord(), getYCoord(), getZCoord());
			if(lavenderHaze){
				glPushMatrix();
					glScalef(0.7, 0.7, 0.7);
					glColor3f(0.4f, 0.25f, 0.4f);
					glutWireSphere(0.7 , 15, 15);
				glPopMatrix();
				glPushMatrix();
					glColor3f(0.8f, 0.5f, 0.8f);
					glScalef(4.0, 4.0, 4.0);
					glutWireDodecahedron();
					glPushMatrix();
						glScalef(0.8, 0.8, 0.8);
						glutWireDodecahedron();
					glPopMatrix();
					glPushMatrix();
						glScalef(0.5, 0.5, 0.5);
						glutWireDodecahedron();
					glPopMatrix();
				glPopMatrix();
				
			}
			glColor3f(0.85f, 0.85f, 0.0f);
	    	//glutSolidSphere(0.22f, 20, 20);
	    	glPushMatrix();
	    		glScalef(0.14, 0.12, 0.14);
	    		glutSolidDodecahedron();
	    	glPopMatrix();
	    	// Asinha
	    	glPushMatrix();
	    		glTranslatef(-0.04f, 0.f, 0.18f);
	    		glColor3f(1.0f, 1.0f, 1.0f);
	    		glutSolidCube(0.19f);
	    	glPopMatrix();
	    	
	    	// Branco do olho direito
	    	glPushMatrix();
	    		glTranslatef(0.18f, 0.08f, 0.05f);
	    		glColor3f(1.0f, 1.0f, 1.0f);
	    		glutSolidCube(0.08f);
	    		// Preto do olho
		    	glPushMatrix();
		    		glTranslatef(0.02f, 0.0f, 0.0f);
		    		glColor3f(0.0f, 0.0f, 0.0f);
		    		glutSolidCube(0.045f);
		    	glPopMatrix();
	    	glPopMatrix();
	    	
	    	//Branco do olho esquerdo
	    	glPushMatrix();
	    		glTranslatef(0.18f, 0.08f, -0.05f);
	    		glColor3f(1.0f, 1.0f, 1.0f);
	    		glutSolidCube(0.08f);
	    		// Preto do olho
		    	glPushMatrix();
		    		glTranslatef(0.02f, 0.0f, 0.0f);
		    		glColor3f(0.0f, 0.0f, 0.0f);
		    		glutSolidCube(0.045f);
		    	glPopMatrix();
	    	glPopMatrix();
	    	
	    	//Boca
	    	glPushMatrix();
	    		glTranslatef(0.22f, -0.03f, 0.0f);
	    		glColor3f(1.0f, 0.0f, 0.0f);
	    		glutSolidCube(0.14f);
	    	glPopMatrix();
	    	
	    glPopMatrix();
	}
    
};

class Pipe : public Object {
private:
	float gap;
	
public:
    Pipe() : Object() {}

    Pipe(float x, float y, float z, float hole) : Object(x, y, z), gap(hole) {}

	void drawPipe(float decremento, bool lavenderHaze){
		glPushMatrix();
			glTranslatef(getXCoord(), getYCoord(), getZCoord());
			glColor3f(0.0f, 1.0f, 0.0f);
			if(lavenderHaze){
				glColor3f(0.8f, 0.5f, 0.8f);
			}
		
			//Metade de cima
			glPushMatrix();
				glTranslatef(0.0, gap/2, 0.0);
				glBegin(GL_QUADS);
				    // Face frontal
				    glNormal3f(0.f, 0.f, 1.f);
				    glVertex3f(0.5, 0.0, 0.5);
				    glVertex3f(0.5, 15.0, 0.5);
				    glVertex3f(-0.5, 15.0, 0.5);
				    glVertex3f(-0.5, 0.0, 0.5);
				
				    // Face traseira
				    glNormal3f(0.f, 0.f, -1.f);
				    glVertex3f(0.5, 0.0, -0.5);
				    glVertex3f(0.5, 15.0, -0.5);
				    glVertex3f(-0.5, 15.0, -0.5);
				    glVertex3f(-0.5, 0.0, -0.5);
				
				    // Face superior
				    glNormal3f(0.f, 1.f, 0.f);
				    glVertex3f(0.5, 15.0, 0.5);
				    glVertex3f(0.5, 15.0, -0.5);
				    glVertex3f(-0.5, 15.0, -0.5);
				    glVertex3f(-0.5, 15.0, 0.5);
				
				    // Face inferior
				    glNormal3f(0.f, -1.f, 0.f);
				    glVertex3f(0.5, 0.0, 0.5);
				    glVertex3f(0.5, 0.0, -0.5);
				    glVertex3f(-0.5, 0.0, -0.5);
				    glVertex3f(-0.5, 0.0, 0.5);
				
				    // Face esquerda
				    glNormal3f(-1.f, 0.f, 0.f);
				    glVertex3f(-0.5, 0.0, 0.5);
				    glVertex3f(-0.5, 15.0, 0.5);
				    glVertex3f(-0.5, 15.0, -0.5);
				    glVertex3f(-0.5, 0.0, -0.5);
				
				    // Face direita
				    glNormal3f(1.f, 0.f, 0.f);
				    glVertex3f(0.5, 0.0, 0.5);
				    glVertex3f(0.5, 15.0, 0.5);
				    glVertex3f(0.5, 15.0, -0.5);
				    glVertex3f(0.5, 0.0, -0.5);					
				glEnd();
			glPopMatrix();
			
			// Metade de baixo
			glPushMatrix();
				glTranslatef(0.0, -gap/2, 0.0);
				glBegin(GL_QUADS);
				    // Face frontal
				    glNormal3f(0.f, 0.f, 1.f);
				    glVertex3f(0.5, 0.0, 0.5);
				    glVertex3f(0.5, -15.0, 0.5);
				    glVertex3f(-0.5, -15.0, 0.5);
				    glVertex3f(-0.5, 0.0, 0.5);
				
				    // Face traseira
				    glNormal3f(0.f, 0.f, -1.f);
				    glVertex3f(0.5, 0.0, -0.5);
				    glVertex3f(0.5, -15.0, -0.5);
				    glVertex3f(-0.5, -15.0, -0.5);
				    glVertex3f(-0.5, 0.0, -0.5);
				
				    // Face superior
				    glNormal3f(0.f, 1.f, 0.f);
				    glVertex3f(0.5, -15.0, 0.5);
				    glVertex3f(0.5, -15.0, -0.5);
				    glVertex3f(-0.5, -15.0, -0.5);
				    glVertex3f(-0.5, -15.0, 0.5);
				
				    // Face inferior
				    glNormal3f(0.f, -1.f, 0.f);
				    glVertex3f(0.5, 0.0, 0.5);
				    glVertex3f(0.5, 0.0, -0.5);
				    glVertex3f(-0.5, 0.0, -0.5);
				    glVertex3f(-0.5, 0.0, 0.5);
				
				    // Face esquerda
				    glNormal3f(-1.f, 0.f, 0.f);
				    glVertex3f(-0.5, 0.0, 0.5);
				    glVertex3f(-0.5, -15.0, 0.5);
				    glVertex3f(-0.5, -15.0, -0.5);
				    glVertex3f(-0.5, 0.0, -0.5);
				
				    // Face direita]
				    glNormal3f(1.f, 0.f, 0.f);
				    glVertex3f(0.5, 0.0, 0.5);
				    glVertex3f(0.5, -15.0, 0.5);
				    glVertex3f(0.5, -15.0, -0.5);
				    glVertex3f(0.5, 0.0, -0.5);					
				glEnd();
			glPopMatrix();
	    glPopMatrix();		
	}
};