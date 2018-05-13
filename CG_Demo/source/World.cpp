//
// Created by frhec on 8/05/18.
//

#include "../header/World.h"
#include "../header/glm.h"

float pi = 3.14159;

World::World() {
	angle = 0.0f;
	angle2 = 0.0f;
	dir = 1.0;
   // rotate= false;

    // ==== POSITION ====
    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;
}

World::~World() {

}



void World::draw() {

    float escala = 1;
	

    glPushMatrix();
    {
        switch(changer) {
            case 0:
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; i++)
				{
					float gradaux = i*3.14159 / 180.0; 
					glVertex3f(sin(gradaux)*17.5,
						0.0f, cos(gradaux)*35.0);
				}
				glEnd();
				
				//glTranslatef(0, 0, 35);
				glTranslatef(sin(angle *(pi/180))*17.5,
				0.0f, cos(angle *(pi / 180))*35.0);
				glRotatef(angle2, 0, 1, 0);
                glScalef(0.03505f*escala,0.03505f*escala,0.03505f*escala);
                break;
            case 1:
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; i++)
				{
					float gradaux = i*3.14159 / 180.0; 
					glVertex3f(sin(gradaux)*35.0,
						0.0f, cos(gradaux)*70.0);
				}
				glEnd();
               // glRotatef(angle,0,1,0);
				
				glTranslatef(sin(angle *(pi / 180))*35.0,
					0.0f, cos(angle *(pi / 180))*70.0);
				//glTranslatef(y * 70, 0 , 0 );
				glRotatef(angle2, 0, 1, 0);
                glScalef(0.08695f*escala,0.08695f*escala,0.08695f*escala);
                break;
            case 2: //TIERRA
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; i++)
				{
					float gradaux = i*3.14159 / 180.0; 
					glVertex3f(sin(gradaux)*50.0,
						0.0f, cos(gradaux)*100.0);
				}
				glEnd();
				//glPushMatrix();
				//{
					glTranslatef(sin(angle *(pi / 180))*50.0,
						0.0f, cos(angle *(pi / 180))*100.0);
					//glTranslatef(y * 100, 0, 0);
					glRotatef(angle2, 0, 1, 0);
					glScalef(0.09156f*escala, 0.09156f*escala, 0.09156f*escala);

					glPushMatrix();
					{
						glRotatef(angle, 0, 1, 0);
						glTranslatef(sin(angle *(pi / 180))*50.0,
							90.0f, cos(angle *(pi / 180))*100.0);
						glColor3f(0, 0, 1);
						glutSolidSphere(10, 30, 30);
					}
					glPopMatrix();

				//}
				//glPopMatrix();
                break;
            case 3:

				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; i++)
				{
					float gradaux = i*3.14159 / 180.0;
					glVertex3f(sin(gradaux)*77.25,
						0.0f, cos(gradaux)*155.0);
				}
				glEnd();

               
				glTranslatef(sin(angle *(pi / 180))*77.25,
					0.0f, cos(angle *(pi / 180))*155.0);
				//glTranslatef(y * 155, 0, 0);
				glRotatef(angle2, 0, 1, 0);
                glScalef(0.04889f*escala,0.04889f*escala,0.04889f*escala);
                break;
            case 4:
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; i++)
				{
					float gradaux = i*3.14159 / 180.0;
					glVertex3f(sin(gradaux)*257.5,
						0.0f, cos(gradaux)*515.0);
				}
				glEnd();
                
               // glRotatef(angle,0,1,0);
				//glTranslatef(y * 515,0 , 0 );
				glTranslatef(sin(angle *(pi / 180))*257.5,
					0.0f, cos(angle *(pi / 180))*515.0);
				glRotatef(angle2, 0, 1, 0);
				
                glScalef(0.98227f*escala,0.98227f*escala,0.98227f*escala);
                break;
            case 5:
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; i++)
				{
					float gradaux = i*3.14159 / 180.0; 
					glVertex3f(sin(gradaux)*475.0,
						0.0f, cos(gradaux)*950.0);
				}
				glEnd();
                
                //glRotatef(angle,0,1,0);
				glTranslatef(sin(angle *(pi / 180))*475.0,
					0.0f, cos(angle *(pi / 180))*950.0);
				glRotatef(angle2, 0, 1, 0);
				//glTranslatef(0, 0, 950);
                glScalef(0.866592f*escala,0.866592f*escala,0.866592f*escala);
                break;
            case 6:
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; i++)
				{
					float gradaux = i*3.14159 / 180.0; 
					glVertex3f(sin(gradaux)*96.0,
						0.0f, cos(gradaux)*192.0);
				}
				glEnd();
               
               // glRotatef(angle,0,1,0);
				//glTranslatef(0, 0, 192);
				glTranslatef(sin(angle *(pi / 180))*96.0,
					0.0f, cos(angle *(pi / 180))*192.0);
				glRotatef(angle2, 0, 1, 0);
                glScalef(0.36723f*escala,0.36723f*escala,0.36723f*escala);
                break;
            case 7:
				glBegin(GL_LINE_LOOP);
				for (int i = 0; i < 360; i++)
				{
					float gradaux = i*3.14159 / 180.0; 
					glVertex3f(sin(gradaux)*1527.5,
						0.0f, cos(gradaux)*3055.0);
				}
				glEnd();
                
                //glRotatef(angle,0,1,0);
				//glTranslatef(0, 0, 3055);
				glTranslatef(sin(angle *(pi / 180))*1527.5,
					0.0f, cos(angle *(pi / 180))*3055.0);
				glRotatef(angle2, 0, 1, 0);
                glScalef(0.35376f*escala,0.35376f*escala,0.35376f*escala);
                break;
            case 8: //SOL
				glTranslatef(0, 0, 0);
                glRotatef(angle/10,0,1,0);				
                glScalef(.5, .5, .5);
                break;
            case 9: //LUNA
                
               // glRotatef(angle,0,1,0);
				//glTranslatef(0, 0, 90);
				//glRotatef(angle, 0, 1, 0);
               // glScalef(0.02496f*escala,0.02496f*escala,0.02496f*escala);
                break;
        }
        glmDraw(mundo, GLM_SMOOTH | GLM_TEXTURE);
    }
    glPopMatrix();

}

void World::update() {
	angle += 0.1;
	angle2 += 0.2;
	x = cos(angle*(3.14 / 180))*6.0f;
	y = sin(angle*(3.14 / 180))*2.3f;
}

void World::assign(int pos) {
    
    changer = pos;
    
    switch(changer) {
        case 0:
            mundo = glmReadOBJ(const_cast<char *>("assets/Mercury/Mercury.obj"));
            break;
        case 1:
            mundo = glmReadOBJ(const_cast<char *>("assets/Venus/Venus.obj"));
            break;
        case 2:
            mundo = glmReadOBJ(const_cast<char *>("assets/Earth/Earth.obj"));
            break;
        case 3:
            mundo = glmReadOBJ(const_cast<char *>("assets/Mars/Mars.obj"));
            break;
        case 4:
            mundo = glmReadOBJ(const_cast<char *>("assets/Jupiter/Jupiter.obj"));
            break;
        case 5:
            mundo = glmReadOBJ(const_cast<char *>("assets/Saturn/Saturn.obj"));
            break;
        case 6:
            mundo = glmReadOBJ(const_cast<char *>("assets/Uranus/Uranus.obj"));
            break;
        case 7:
            mundo = glmReadOBJ(const_cast<char *>("assets/Neptune/Neptune.obj"));
            break;
        case 8:
            mundo = glmReadOBJ(const_cast<char *>("assets/Sol/Sol.obj"));
            break;
        case 9:
            mundo = glmReadOBJ(const_cast<char *>("assets/Sol/Sol.obj"));
            break;
    }

    glmFacetNormals(mundo);
    glmVertexNormals(mundo, 45.0f);

}

