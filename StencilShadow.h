#ifndef _STENCILSHADOW_H_
#define _STENCILSHADOW_H_

float floorShadow[4][4];	// matrix used to calculate our projected floor shadow
float groundplane[]   = {0.0f, 1.0f, 0.0f, 1.0f}; // The normal of the floor
float backplan[]   = {1.0f, 0.0f, 0.0f, 1.0f}; // The normal of the floor
enum { X, Y, Z, W };

void shadowmatrix(float shadowMat[4][4], float groundplane[4], float lightpos[4])
{
	float dot = groundplane[X] * lightpos[X] + groundplane[Y] * lightpos[Y] + groundplane[Z] * lightpos[Z] + groundplane[W] * lightpos[W];

	shadowMat[0][0] = dot - lightpos[X] * groundplane[X];
	shadowMat[1][0] = 0.f - lightpos[X] * groundplane[Y];
	shadowMat[2][0] = 0.f - lightpos[X] * groundplane[Z];
	shadowMat[3][0] = 0.f - lightpos[X] * groundplane[W];

	shadowMat[X][1] = 0.f - lightpos[Y] * groundplane[X];
	shadowMat[1][1] = dot - lightpos[Y] * groundplane[Y];
	shadowMat[2][1] = 0.f - lightpos[Y] * groundplane[Z];
	shadowMat[3][1] = 0.f - lightpos[Y] * groundplane[W];

	shadowMat[X][2] = 0.f - lightpos[Z] * groundplane[X];
	shadowMat[1][2] = 0.f - lightpos[Z] * groundplane[Y];
	shadowMat[2][2] = dot - lightpos[Z] * groundplane[Z];
	shadowMat[3][2] = 0.f - lightpos[Z] * groundplane[W];

	shadowMat[X][3] = 0.f - lightpos[W] * groundplane[X];
	shadowMat[1][3] = 0.f - lightpos[W] * groundplane[Y];
	shadowMat[2][3] = 0.f - lightpos[W] * groundplane[Z];
	shadowMat[3][3] = dot - lightpos[W] * groundplane[W];
}

void Shadow()
{	
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glPushMatrix();
		//draw floor
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(-13.0, 0.0, -13.0);
			glVertex3f(13.0, 0.0, -13.0);
			glVertex3f(13.0, 0.0, 3.0);
			glVertex3f(-13.0, 0.0, 3.0);
		glEnd();
	glPopMatrix();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glPushMatrix();
		// Draw the floor
		glColor3f(1.0, 0.5, 0.8);
		glBegin(GL_QUADS);
			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(-13.0, 0.0, -13.0);
			glVertex3f(13.0, 0.0, -13.0);
			glVertex3f(13.0, 0.0, 3.0);
			glVertex3f(-13.0, 0.0, 3.0);
		glEnd();
	glPopMatrix();

	glPushMatrix();
		//Shadow Color
		glTranslatef(0.0, 1.0, 0.0);
		glColor4f(0.0, 0.0, 0.0, 0.5f);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
		shadowmatrix(floorShadow, groundplane, lightPosition);
		glMultMatrixf((float *)floorShadow);
		//Draw Shadow
		glTranslatef(-2.0, 0.0, 0.0);
		glRotatef(20.0f,0,1.0f,0);
		glutSolidCube(2.0);
		glTranslatef(4.0, 0.5, 0.0);
		glutSolidTorus(0.5, 1.0, 30, 30);
	//	glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		//Draw OBJ
		glDisable(GL_STENCIL_TEST);
		glTranslatef(-2.0, 1.0, 0.0);
		glRotatef(20.0f,0,1.0f,0);
	//	glEnable(GL_TEXTURE_2D);
		glColor3f(0.3, 2.0, 0.8);
		glutSolidCube(2.0);
		glColor3f(0.0, 0.0, 0.8);
		glTranslatef(4.0, 0.5, 0.0);
		glutSolidTorus(0.5, 1.0, 30, 30);
	glPopMatrix();
}

#endif
