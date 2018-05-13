//
// Created by frhec on 8/05/18.
//
#pragma once

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include "freeglut.h"
#endif

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "glm.h"

#ifndef SOLAR_SYSTEM_WORLD_H
#define SOLAR_SYSTEM_WORLD_H

#include <stdio.h>

class World {

public:
    ~World();
    float pos[3];
    float angle;
	float angle2;
	float dir;
    float rotate;
	float x;
	float y;
    GLMmodel * mundo;
    void update();
    World();
    void assign(int pos);
    int changer;
    void draw();
	
};


#endif //SOLAR_SYSTEM_WORLD_H
