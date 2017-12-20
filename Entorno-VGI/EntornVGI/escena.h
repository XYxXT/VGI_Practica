//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2013 MULTIFINESTRA amb OpenGL, interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2017)
// escena.h : interface de escena.cpp
//

#ifndef GLSOURCE_H
#define GLSOURCE_H

#include "MyVariable.h"

/* ------------------------------------------------------------------------- */
/*                            Funcions de les escenes                        */
/* ------------------------------------------------------------------------- */
// Entorn VGI: dibuixa_EscenaGL -> Dibuix de l'escena GL
void dibuixa_EscenaGL(char objecte, CColor col_object, bool ref_mat, bool sw_mat[4], bool textur);

// Entorn VGI: dibuixa -> Funció que dibuixa objectes simples de la llibreria GLUT segons obj
void dibuixa(char obj);

// Entorn VGI: Truck
void truck(bool textu,GLuint VTextu[NUM_MAX_TEXTURES]);
void neumatic(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void llanta(bool textur, GLuint VTextur[NUM_MAX_TEXTURES]);
void sea(void);

//void robot(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
void camio(bool textu, GLuint VTextu[NUM_MAX_TEXTURES]);
void aerportPrat(CColor col_object, bool ref_mat, bool sw_mat[4], bool textur, GLuint VTextu[NUM_MAX_TEXTURES]);
void animationAirport(CColor col_object, bool ref_mat, bool sw_mat[4], bool textur, GLuint VTextu[NUM_MAX_TEXTURES]);

void cilindre(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks);

#endif