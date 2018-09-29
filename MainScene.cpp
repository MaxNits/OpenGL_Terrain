#include "ImageLoader.h"
#include "TerrainGenerator.h"
#include "TerrainHandle.h"
#include "Vec3f.h"

#include "GL/glut.h"

#include <algorithm>
#include <iostream>
#include <memory>

constexpr float SCALE = 7.0f;
constexpr float CAMERA_VIEW_ANGLE = 20.0f;

float gAngle = 60.0f;
float gTerrainColor[] = {0.85f, 0.85f, 0.85f};
float gBackgroundColor[] = { 0.1, 0.1, 0.1, 1.0 };

std::shared_ptr<TerrainGenerator> gTerrainGenerator;

void handleKeyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC key
        exit(0);
    }
}

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void update(int value)
{
    gAngle += 1.0f;
    gAngle = (float)((int)gAngle % 360);

    glutPostRedisplay();
    glutTimerFunc(50, update, 0);
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(gBackgroundColor[0], gBackgroundColor[1], gBackgroundColor[2], gBackgroundColor[3]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0f); // x = left/right; y = up/down; z = dist to camera;
    glRotatef(CAMERA_VIEW_ANGLE, 1.0f, 0.0f, 0.0f);
    glRotatef(-gAngle, 0.0f, 1.0f, 0.0f);

    GLfloat ambientColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    GLfloat lightColor0[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat lightPos0[] = { -0.5f, 0.8f, 0.1f, 0.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    const auto handle = gTerrainGenerator->getHandle();

    float scale = SCALE / std::max(handle->getWidth() - 1, handle->getLength() - 1);
    glScalef(scale, scale, scale);
    glTranslatef(-float(handle->getWidth()) / 2, 0.0f, -float(handle->getLength()) / 2);

    glColor3f(gTerrainColor[0], gTerrainColor[1], gTerrainColor[2]);

    for (int z = 0; z < handle->getLength() - 1; z++)
    {
        glBegin(GL_TRIANGLE_STRIP);

        for (int x = 0; x < handle->getWidth() - 1; x++)
        {
            Vec3f normal = handle->getNormal(x, z);
            glNormal3f(normal.x, normal.z, normal.y); // x,z,y order <- can be a source of ERROR
            glVertex3f(x, handle->getHeight(x, z), z);

            normal = handle->getNormal(x, z + 1);
            glNormal3f(normal.x, normal.z, normal.y);
            glVertex3f(x, handle->getHeight(x, z + 1), z + 1);
        }

        glEnd();
    }

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Terrain Mesh Practice");
    initRendering();

    gTerrainGenerator = std::make_shared<TerrainGenerator>(500, 500);
    gTerrainGenerator->generateTerrain();

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeyPress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;
}
