#include "TerrainMesh.h"
#include "Vec3f.h"
#include "ImageLoader.h"

#include "GL/glut.h"

#include <algorithm>
#include <iostream>

#define SCALE 8.0f

float _angle = 60.0f;
TerrainMesh* _terrain;
float _terrainColor[] = {0.3f, 0.9f, 0.0f};

using namespace std;

void cleanup()
{
    delete[] _terrain;
}

void handleKeyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC key
        cleanup();
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
    _angle += 1.0f;
    if (_angle > 360) {
        _angle -= 360;
    }

    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}

TerrainMesh* loadTerrain(const char* filename, float height)
{
    Image* image = loadBMP(filename);

    TerrainMesh* terrain = new TerrainMesh(image->width, image->height);

    for (int y = 0; y < image->height; ++y)
    {
        for (int x = 0; x < image->width; ++x)
        {
            unsigned char color = (unsigned char)image->pixels[3 * (y * image->width + x)];
            float h = height * ((color / 255.0f) - 0.5f);
            terrain->setHeight(x, y, h);
        }
    }

    delete image;
    terrain->computeNormals();
    return terrain;
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-_angle, 0.0f, 1.0f, 0.0f);

    GLfloat ambientColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    GLfloat lightColor0[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    GLfloat lightPos0[] = { -0.5f, 0.8f, 0.1f, 0.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);


    float scale = SCALE / max(_terrain->getWidth() - 1, _terrain->getLength() - 1);
    glScalef(scale, scale, scale);
    glTranslatef(-float(_terrain->getWidth()) / 2, 0.0f, -float(_terrain->getLength()) / 2);

    glColor3f(_terrainColor[0], _terrainColor[1], _terrainColor[2]);

    for (int z = 0; z < _terrain->getLength() - 1; z++)
    {
        glBegin(GL_TRIANGLE_STRIP);

        for (int x = 0; x < _terrain->getWidth() - 1; x++)
        {
            Vec3f normal = _terrain->getNormal(x, z);
            glNormal3f(normal.x, normal.z, normal.y); // x,z,y order <- can be a source of ERROR
            glVertex3f(x, _terrain->getHeight(x, z), z);

            normal = _terrain->getNormal(x, z + 1);
            glNormal3f(normal.x, normal.z, normal.y);
            glVertex3f(x, _terrain->getHeight(x, z + 1), z + 1);
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

    _terrain = loadTerrain("heightmap.bmp", 20.0f);

    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeyPress);
    glutReshapeFunc(handleResize);
    glutTimerFunc(25, update, 0);

    glutMainLoop();
    return 0;
}
