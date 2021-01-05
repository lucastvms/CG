#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_NAME "Projeto CG - Lucas Vieira"

typedef struct Vertice
{
	float x, y, z;
	float corR, corG, corB;
	float u, v;
} Vertice;

typedef struct Cubo
{
	float x, y, z; // centro da cubo
	float rotx, roty, rotz;
	float largura, altura, profundidade;
	float corR, corG, corB;
} Cubo;

typedef struct Camera
{
	float x, y, z; // posição
	float dx, dy, dz; // direção
	float angulo, fracao; // mudança de ângulo e de posição
} Camera;

typedef struct Esfera
{
	float raio;
	int slices, stacks;
	float x, y, z;
	float corR, corG, corB;
} Esfera;

// ângulos de abertura: porta e janela
float angulo_porta = 0.0f;
float angulo_janela1 = 0.0f, angulo_janela2 = 0;

// IDs das textuas
unsigned int texturaCama;
unsigned int texturaGuardaRoupa1, texturaGuardaRoupa2; // frente e lados
unsigned int texturaLivro1, texturaLivro2; // frente e lado
unsigned int texturaNotebook1, texturaNotebook2; // tela e base
unsigned int texturaPiso;
unsigned int texturaQuadro;
unsigned int texturaTV;


/*             DECLARAÇÃO DOS OBJETOS               */

Camera cam = {
	.x = 3.0f, 
	.y = 2.0f, 
	.z = 3.0f,
	.dx = -3.0f,
	.dy = 1.5f,
	.dz = -3.0f,
	.angulo = 0.0f,
	.fracao = 0.5f
};

Esfera esfera = {
	.raio = 0.16,
	.slices = 36,
	.stacks = 18,
	.x = 4.6,
	.y = 0.24,
	.z = 0.5,
	.corR = 0.996,
	.corG = 0.269,
	.corB = 0.0,
};

Vertice cama1[] = { // cama atrás
	{4.0f, 0.6f, 4.999f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{6.0f, 0.6f, 4.999f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{6.0f, 0.0f, 4.999f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
	{4.0f, 0.0f, 4.999f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
};

Vertice cama2[] = { // cama lado esquerdo
	{3.999f, 0.6f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{3.999f, 0.6f, 6.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{3.999f, 0.0f, 6.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
	{3.999f, 0.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
};

Vertice guardaroupa1[] = { // guarda-roupa lado esquerdo
	{5.0f, 2.0f, 1.999f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{6.0f, 2.0f, 1.999f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{6.0f, 0.0f, 1.999f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
	{5.0f, 0.0f, 1.999f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
};

Vertice guardaroupa2[] = { // guarda-roupa lado direito
	{5.0f, 2.0f, 3.601f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{6.0f, 2.0f, 3.601f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{6.0f, 0.0f, 3.601f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
	{5.0f, 0.0f, 3.601f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
};

Vertice guardaroupa3[] = { // guarda-roupa lado cima
	{5.0f, 2.001f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{6.0f, 2.001f, 2.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{6.0f, 2.001f, 3.6f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	{5.0f, 2.001f, 3.6f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
};


Vertice guardaroupa4[] = { // guarda-roupa frente
	{4.999f, 2.0f, 3.6f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	{4.999f, 0.0f, 3.6f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{4.999f, 0.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{4.999f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
};

Vertice livro1[] = { // frente
	{0.55f, 1.501f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{0.55f, 1.501f, 0.6f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{1.05f, 1.501f, 0.6f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	{1.05f, 1.501f, 0.2f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
};

Vertice livro2[] = { // lado
	{1.05f, 1.5f, 0.601f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	{0.55f, 1.5f, 0.601f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
	{0.55f, 1.45f, 0.601f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{1.05f, 1.45f, 0.601f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
};

Vertice notebook1[] = { // tela
	{0.701f, 1.47f, 0.95f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	{0.701f, 1.87f, 0.95f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{0.701f, 1.87f, 1.45f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{0.701f, 1.47f, 1.45f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
};

Vertice notebook2[] = { // base
	{0.7f, 1.471f, 1.45f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{0.7f, 1.471f, 0.95f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{1.1f, 1.471f, 0.95f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	{1.1f, 1.471f, 1.45f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
};

Vertice quadro[] = {
	{3.3f, 2.3f, 0.101f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{3.3f, 1.5f, 0.101f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
	{2.7f, 1.5f, 0.101f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	{2.7f, 2.3f, 0.101f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
};

Vertice tv[] = {
	{0.201f, 1.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
	{0.201f, 2.5f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
	{0.201f, 2.5f, 3.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f},
	{0.201f, 1.0f, 3.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
};

Cubo porta = {
	.x = 2.25f,
	.y = 1.25f,
	.z = 6.0f,
	.rotx = 0.0,
	.roty = angulo_porta,
	.rotz = 0.0,
	.largura = 1.5,
	.altura = 2.5,
	.profundidade= 0.1,
	.corR = 0.625,
	.corG = 0.320,
	.corB = 0.175,
};

Cubo janela1 = {
	.x = 4.25,
	.y = 2.0,
	.z = 6.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.5,
	.altura = 1.0,
	.profundidade= 0.1,
	.corR = 0.7,
	.corG = 0.5,
	.corB = 0.2,
};

Cubo janela2 = 	{
	.x = 4.75,
	.y = 2.0,
	.z = 6.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.5,
	.altura = 1.0,
	.profundidade= 0.1,
	.corR = 0.7,
	.corG = 0.5,
	.corB = 0.2,
};

Cubo cubos[] = {
	{ // parede lado esquerdo [0]
	.x = 0.0,
	.y = 1.5,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 90.0,
	.rotz = 0.0,
	.largura = 6.0,
	.altura = 3.0,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // parede lado direito [1]
	.x = 6.0,
	.y = 1.5,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 90.0,
	.rotz = 0.0,
	.largura = 6.0,
	.altura = 3.0,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // parede trás [2]
	.x = 3.0,
	.y = 1.5,
	.z = 0.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 6.0,
	.altura = 3.0,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // teto [3]
	.x = 3.0,
	.y = 3.0,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 6.0,
	.altura = 0.1,
	.profundidade= 6.0,
	.corR = 0.85,
	.corG = 0.85,
	.corB = 0.85,
	},
	{ // piso [4]
	.x = 3.0,
	.y = 0.0,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 6.0,
	.altura = 0.1,
	.profundidade= 6.0,
	.corR = 0.85,
	.corG = 0.85,
	.corB = 0.85,
	},
	{ // parede porta 1 [5]
	.x = 0.75,
	.y = 1.5,
	.z = 6.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 1.5,
	.altura = 3.0,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // parede porta 2 [6]
	.x = 2.25,
	.y = 2.75,
	.z = 6.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 1.5,
	.altura = 0.5,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // parede porta 3 [7]
	.x = 3.5,
	.y = 1.5,
	.z = 6.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 1.0,
	.altura = 3.0,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // parede janela 1 [8]
	.x = 4.5,
	.y = 2.75,
	.z = 6.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 1.0,
	.altura = 0.5,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // parede janela 2 [9]
	.x = 4.5,
	.y = 0.75,
	.z = 6.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 1.0,
	.altura = 1.5,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // parede janela 3 [10]
	.x = 5.5,
	.y = 1.5,
	.z = 6.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 1.0,
	.altura = 3.0,
	.profundidade= 0.1,
	.corR = 0.95,
	.corG = 0.95,
	.corB = 0.95,
	},
	{ // cama [11]
	.x = 5.0,
	.y = 0.3,
	.z = 5.5,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 2.0,
	.altura = 0.6,
	.profundidade= 1.0,
	.corR = 0.542,
	.corG = 0.269,
	.corB = 0.074,
	},
	{ // colchão [12]
	.x = 5.0,
	.y = 0.8,
	.z = 5.5,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 2.0,
	.altura = 0.4,
	.profundidade= 1.0,
	.corR = 0.593,
	.corG = 0.980,
	.corB = 0.593,
	},
	{ // travesseiro [13]
	.x = 5.7,
	.y = 1.1,
	.z = 5.5,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.4,
	.altura = 0.2,
	.profundidade= 0.8,
	.corR = 0.558,
	.corG = 0.734,
	.corB = 0.558,
	},
	{ // tv [14]
	.x = 0.1,
	.y = 1.75,
	.z = 4.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.2,
	.altura = 1.5,
	.profundidade= 2.0,
	.corR = 0.01,
	.corG = 0.01,
	.corB = 0.01,
	},
	{ // mesa [15]
	.x = 0.6,
	.y = 1.4,
	.z = 0.8,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 1.2,
	.altura = 0.1,
	.profundidade= 1.6,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // pé mesa 1 [16]
	.x = 0.1,
	.y = 0.7,
	.z = 0.1,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.05,
	.altura = 1.4,
	.profundidade= 0.05,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // pé mesa 2 [17]
	.x = 1.15,
	.y = 0.7,
	.z = 0.1,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.05,
	.altura = 1.4,
	.profundidade= 0.05,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // pé mesa 3 [18]
	.x = 0.1,
	.y = 0.7,
	.z = 1.55,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.05,
	.altura = 1.4,
	.profundidade= 0.05,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // pé mesa 4 [19]
	.x = 1.15,
	.y = 0.7,
	.z = 1.55,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.05,
	.altura = 1.4,
	.profundidade= 0.05,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // assento cadeira [20]
	.x = 1.2,
	.y = 0.7,
	.z = 0.8,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.8,
	.altura = 0.2,
	.profundidade= 0.6,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // costas cadeira [21]
	.x = 1.55,
	.y = 1.1,
	.z = 0.8,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.1,
	.altura = 0.6,
	.profundidade= 0.6,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // acolchoado cadeira [22]
	.x = 1.48,
	.y = 1.1,
	.z = 0.8,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.04,
	.altura = 0.56,
	.profundidade= 0.6,
	.corR = 0.500,
	.corG = 0.01,
	.corB = 0.01,
	},
	{ // pé cadeira 1 [23]
	.x = 0.85,
	.y = 0.4,
	.z = 0.55,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.05,
	.altura = 0.8,
	.profundidade= 0.05,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // pé cadeira 2 [24]
	.x = 1.55,
	.y = 0.4,
	.z = 0.55,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.05,
	.altura = 0.8,
	.profundidade= 0.05,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // pé cadeira 3 [25]
	.x = 0.85,
	.y = 0.4,
	.z = 1.05,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.05,
	.altura = 0.8,
	.profundidade= 0.05,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // pé cadeira 4 [26]
	.x = 1.55,
	.y = 0.4,
	.z = 1.05,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.05,
	.altura = 0.8,
	.profundidade= 0.05,
	.corR = 0.867,
	.corG = 0.718,
	.corB = 0.527,
	},
	{ // ventilador teto, suporte [27]
	.x = 3.0,
	.y = 2.8,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.1,
	.altura = 0.4,
	.profundidade= 0.1,
	.corR = 0.6,
	.corG = 0.6,
	.corB = 0.6,
	},
	{ // ventilador teto, centro 1 [28]
	.x = 3.0,
	.y = 2.95,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.4,
	.altura = 0.1,
	.profundidade= 0.4,
	.corR = 0.6,
	.corG = 0.6,
	.corB = 0.6,
	},
	{ // ventilador teto, centro 2 [29]
	.x = 3.0,
	.y = 2.5,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.2,
	.altura = 0.2,
	.profundidade= 0.2,
	.corR = 0.6,
	.corG = 0.6,
	.corB = 0.6,
	},
	{ // ventilador teto, espátula 1 [30]
	.x = 3.0,
	.y = 2.57,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 2.0,
	.altura = 0.06,
	.profundidade= 0.2,
	.corR = 0.7,
	.corG = 0.7,
	.corB = 0.7,
	},
	{ // ventilador teto, espátula 2 [31]
	.x = 3.0,
	.y = 2.57,
	.z = 3.0,
	.rotx = 0.0,
	.roty = 90.0,
	.rotz = 0.0,
	.largura = 2.0,
	.altura = 0.06,
	.profundidade= 0.2,
	.corR = 0.7,
	.corG = 0.7,
	.corB = 0.7,
	},
	{ // notebook, base [32]
	.x = 0.9,
	.y = 1.460,
	.z = 1.2,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.4,
	.altura = 0.02,
	.profundidade= 0.5,
	.corR = 0.5,
	.corG = 0.5,
	.corB = 0.5,
	},
	{ // notebook, tela [33]
	.x = 0.69,
	.y = 1.670,
	.z = 1.2,
	.rotx = 0.0,
	.roty = 90.0,
	.rotz = 0.0,
	.largura = 0.5,
	.altura = 0.4,
	.profundidade= 0.02,
	.corR = 0.55,
	.corG = 0.55,
	.corB = 0.55,
	},
	{ // livro [34]
	.x = 0.8,
	.y = 1.475,
	.z = 0.4,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.5,
	.altura = 0.05,
	.profundidade= 0.4,
	.corR = 0.88,
	.corG = 0.88,
	.corB = 0.88,
	},
	{ // guarda-roupa [35]
	.x = 5.5,
	.y = 1.0,
	.z = 2.8,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 1.0,
	.altura = 2.0,
	.profundidade= 1.6,
	.corR = 0.4,
	.corG = 0.6,
	.corB = 0.6,
	},
	{ // lixeira base [36]
	.x = 5.5,
	.y = 0.05,
	.z = 0.4,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.4,
	.altura = 0.1,
	.profundidade= 0.4,
	.corR = 0.437,
	.corG = 0.5,
	.corB = 0.562,
	},
	{ // lixeira trás [37]
	.x = 5.5,
	.y = 0.3,
	.z = 0.23,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.4,
	.altura = 0.4,
	.profundidade= 0.06,
	.corR = 0.687,
	.corG = 0.765,
	.corB = 0.867,
	},
	{ // lixeira frente [38]
	.x = 5.5,
	.y = 0.3,
	.z = 0.57,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.4,
	.altura = 0.4,
	.profundidade= 0.06,
	.corR = 0.687,
	.corG = 0.765,
	.corB = 0.867,
	},
	{ // lixeira lado direito [39]
	.x = 5.67,
	.y = 0.3,
	.z = 0.4,
	.rotx = 0.0,
	.roty = 90.0,
	.rotz = 0.0,
	.largura = 0.4,
	.altura = 0.4,
	.profundidade= 0.06,
	.corR = 0.687,
	.corG = 0.765,
	.corB = 0.867,
	},
	{ // lixeira lado esquerdo [40]
	.x = 5.33,
	.y = 0.3,
	.z = 0.4,
	.rotx = 0.0,
	.roty = 90.0,
	.rotz = 0.0,
	.largura = 0.4,
	.altura = 0.4,
	.profundidade= 0.06,
	.corR = 0.687,
	.corG = 0.765,
	.corB = 0.867,
	},
	{ // quadro [41]
	.x = 3.0,
	.y = 1.9,
	.z = 0.05,
	.rotx = 0.0,
	.roty = 0.0,
	.rotz = 0.0,
	.largura = 0.6,
	.altura = 0.8,
	.profundidade= 0.1,
	.corR = 0.7,
	.corG = 0.5,
	.corB = 0.2,
	},
};




/*             FUNÇÕES               */

void desenharBola(Esfera esfera) {
	glPushMatrix();

	glTranslatef(esfera.x, esfera.y, esfera.z);

    GLUquadric *formato = gluNewQuadric();
    gluQuadricDrawStyle(formato, GLU_FILL);
    gluQuadricNormals(formato, GLU_SMOOTH);
    glColor3f(esfera.corR, esfera.corG, esfera.corB);

    gluSphere(formato, esfera.raio, esfera.slices, esfera.stacks);

    glPopMatrix();
}


void desenharPorta(Cubo porta) {
	glPushMatrix();

	glTranslatef(porta.x + (porta.largura/2), porta.y, porta.z);
	glRotatef(porta.roty, 0.0f, 1.0f, 0.0f);
	glTranslatef(-(porta.largura/2), 0.0, 0.0);
	glScalef(porta.largura, porta.altura, porta.profundidade); 
	glColor3f(porta.corR, porta.corG, porta.corB);
	glutSolidCube(1.0f);

	glPopMatrix();
}


void desenharJanela(Cubo janela1, Cubo janela2) {
	glPushMatrix();

	glTranslatef(janela1.x - (janela1.largura/2), janela1.y, janela1.z);
	glRotatef(janela1.roty, 0.0f, -1.0f, 0.0f);
	glTranslatef(+(janela1.largura/2), 0.0, 0.0);
	glScalef(janela1.largura, janela1.altura, janela1.profundidade); 
	glColor3f(janela1.corR, janela1.corG, janela1.corB);
	glutSolidCube(1.0f);

	glPopMatrix();


	glPushMatrix();

	glTranslatef(janela2.x + (janela2.largura/2), janela2.y, janela2.z);
	glRotatef(janela2.roty, 0.0f, 1.0f, 0.0f);
	glTranslatef(-(janela2.largura/2), 0.0, 0.0);
	glScalef(janela2.largura, janela2.altura, janela2.profundidade); 
	glColor3f(janela2.corR, janela2.corG, janela2.corB);
	glutSolidCube(1.0f);

	glPopMatrix();
}

void desenharCubo(Cubo cubo) {
	glPushMatrix();

	glTranslatef(cubo.x, cubo.y, cubo.z);
	glRotatef(cubo.roty, 0.0f, 1.0f, 0.0f);
	glScalef(cubo.largura, cubo.altura, cubo.profundidade); 
	glColor3f(cubo.corR, cubo.corG, cubo.corB);
	glutSolidCube(1.0f);

	glPopMatrix();
}


unsigned int loadTexture(char const * path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        // glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        printf("Texture failed to load at path: %s", path);
        stbi_image_free(data);
    }

    return textureID;
}

void setup_lighting() {  
	float mat_specular[] = {1.0f, 1.0f, 1.0f};
	float mat_shininess[] = {50.0f};
	float light_ambient[] = {0.1f, 0.1f, 0.1f};
	float light_position[] = {0.0f, 4.0f, 3.0f};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void processarTeclado(unsigned char key, int xx, int yy){
    switch (key) {
    	printf("a");
        case 'a' :
            cam.angulo -= 0.05f;
            cam.dx = sin(cam.angulo);
            cam.dz = -cos(cam.angulo);
        break;

        case 'd' :
            cam.angulo += 0.05f;
            cam.dx = sin(cam.angulo);
            cam.dz = -cos(cam.angulo);
        break;

        case 'w' :
            cam.x += cam.dx * cam.fracao;
            cam.z += cam.dz * cam.fracao;
        break;

        case 's' :
            cam.x -= cam.dx * cam.fracao;
            cam.z -= cam.dz * cam.fracao;
        break;

        case 'q' :
            cam.y += cam.y * (cam.fracao/2);
        break;

        case 'e' :
            cam.y -= cam.y * (cam.fracao/2);
        break;

        case 'o':
            if(porta.roty <= 118.0f) porta.roty += 2.0f;
        break;

        case 'p':
            if(porta.roty >= 2.0f) porta.roty -= 2.0f;
        break;

        case 'n':
            if(janela1.roty <= 118.0f){
            	janela1.roty += 2.0f;
            	janela2.roty += 2.0f;
            }
        break;

        case 'm':
            if(janela1.roty >= 2.0f){
            	janela1.roty -= 2.0f;
            	janela2.roty -= 2.0f;
            }
        break;

        case 27:
            exit(0);
        break;
    }
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam.x, cam.y, cam.z, cam.x + cam.dx, cam.dy, cam.z + cam.dz, 0.0f, 1.0f, 0.0f);

    for(int i=0; i < (sizeof(cubos)/sizeof(Cubo)); i++)
    {
    	desenharCubo(cubos[i]);
    }


    desenharPorta(porta);
    desenharJanela(janela1, janela2);
    desenharBola(esfera);
    


    /*             TEXTURA CAMA               */
    glBindTexture(GL_TEXTURE_2D, texturaCama);
    //glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(cama1)/sizeof(Vertice)); i++)
	{
		glColor3f(cama1[i].corR, cama1[i].corG, cama1[i].corB);
		glTexCoord2f(cama1[i].u, cama1[i].v);
		glVertex3f(cama1[i].x, cama1[i].y, cama1[i].z);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(cama2)/sizeof(Vertice)); i++)
	{
		glColor3f(cama2[i].corR, cama2[i].corG, cama2[i].corB);
		glTexCoord2f(cama2[i].u, cama2[i].v);
		glVertex3f(cama2[i].x, cama2[i].y, cama2[i].z);
	}
	glEnd();



	/*             TEXTURA GUARDA-ROUPA               */

	glBindTexture(GL_TEXTURE_2D, texturaGuardaRoupa2);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(guardaroupa1)/sizeof(Vertice)); i++)
	{
		glColor3f(guardaroupa1[i].corR, guardaroupa1[i].corG, guardaroupa1[i].corB);
		glTexCoord2f(guardaroupa1[i].u, guardaroupa1[i].v);
		glVertex3f(guardaroupa1[i].x, guardaroupa1[i].y, guardaroupa1[i].z);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(guardaroupa2)/sizeof(Vertice)); i++)
	{
		glColor3f(guardaroupa2[i].corR, guardaroupa2[i].corG, guardaroupa2[i].corB);
		glTexCoord2f(guardaroupa2[i].u, guardaroupa2[i].v);
		glVertex3f(guardaroupa2[i].x, guardaroupa2[i].y, guardaroupa2[i].z);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(guardaroupa3)/sizeof(Vertice)); i++)
	{
		glColor3f(guardaroupa3[i].corR, guardaroupa3[i].corG, guardaroupa3[i].corB);
		glTexCoord2f(guardaroupa3[i].u, guardaroupa3[i].v);
		glVertex3f(guardaroupa3[i].x, guardaroupa3[i].y, guardaroupa3[i].z);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texturaGuardaRoupa1);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(guardaroupa4)/sizeof(Vertice)); i++)
	{
		glColor3f(guardaroupa4[i].corR, guardaroupa4[i].corG, guardaroupa4[i].corB);
		glTexCoord2f(guardaroupa4[i].u, guardaroupa4[i].v);
		glVertex3f(guardaroupa4[i].x, guardaroupa4[i].y, guardaroupa4[i].z);
	}
	glEnd();



	/*             TEXTURA LIVRO               */

	glBindTexture(GL_TEXTURE_2D, texturaLivro1);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(livro1)/sizeof(Vertice)); i++)
	{
		glColor3f(livro1[i].corR, livro1[i].corG, livro1[i].corB);
		glTexCoord2f(livro1[i].u, livro1[i].v);
		glVertex3f(livro1[i].x, livro1[i].y, livro1[i].z);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texturaLivro2);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(livro2)/sizeof(Vertice)); i++)
	{
		glColor3f(livro2[i].corR, livro2[i].corG, livro2[i].corB);
		glTexCoord2f(livro2[i].u, livro2[i].v);
		glVertex3f(livro2[i].x, livro2[i].y, livro2[i].z);
	}
	glEnd();


	/*             TEXTURA NOTEBOOK               */

	glBindTexture(GL_TEXTURE_2D, texturaNotebook1);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(notebook1)/sizeof(Vertice)); i++)
	{
		glColor3f(notebook1[i].corR, notebook1[i].corG, notebook1[i].corB);
		glTexCoord2f(notebook1[i].u, notebook1[i].v);
		glVertex3f(notebook1[i].x, notebook1[i].y, notebook1[i].z);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texturaNotebook2);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(notebook2)/sizeof(Vertice)); i++)
	{
		glColor3f(notebook2[i].corR, notebook2[i].corG, notebook2[i].corB);
		glTexCoord2f(notebook2[i].u, notebook2[i].v);
		glVertex3f(notebook2[i].x, notebook2[i].y, notebook2[i].z);
	}
	glEnd();



	/*             TEXTURA QUADRO               */

	glBindTexture(GL_TEXTURE_2D, texturaQuadro);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(quadro)/sizeof(Vertice)); i++)
	{
		glColor3f(quadro[i].corR, quadro[i].corG, quadro[i].corB);
		glTexCoord2f(quadro[i].u, quadro[i].v);
		glVertex3f(quadro[i].x, quadro[i].y, quadro[i].z);
	}
	glEnd();


	/*             TEXTURA TV               */

	glBindTexture(GL_TEXTURE_2D, texturaTV);

	glBegin(GL_POLYGON);
	for(int i = 0; i < (sizeof(tv)/sizeof(Vertice)); i++)
	{
		glColor3f(tv[i].corR, tv[i].corG, tv[i].corB);
		glTexCoord2f(tv[i].u, tv[i].v);
		glVertex3f(tv[i].x, tv[i].y, tv[i].z);
	}
	glEnd();



	/*             ROTAÇÃO VENTILADOR               */

	cubos[30].roty += 0.4;
	cubos[31].roty += 0.4;

	glBindTexture(GL_TEXTURE_2D, 0);
    glutPostRedisplay();
    glutSwapBuffers();
}



int main(int argc, char **argv){

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_NAME);

    glutKeyboardFunc(processarTeclado); 

	float fov_y = 80.0f; // 80 graus
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov_y, 1.0f * WINDOW_WIDTH / WINDOW_HEIGHT, 0.001f, 1000.0f);

    glutDisplayFunc(display);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);


    //setup_lighting();

    // CARREGAMENTO DE TEXTURAS
    texturaCama = loadTexture("cama.jpeg");
    texturaGuardaRoupa1 = loadTexture("guardaroupa-frente.jpeg");
    texturaGuardaRoupa2 = loadTexture("guardaroupa-lado.jpeg");
	texturaLivro1 = loadTexture("livro-frente.jpeg");
	texturaLivro2 = loadTexture("livro-lado.jpeg");
	texturaNotebook1 = loadTexture("notebook-tela.jpeg");
	texturaNotebook2 = loadTexture("notebook-base.jpeg");
	texturaPiso = loadTexture("piso.jpeg");
	texturaQuadro = loadTexture("quadro.jpeg");
	texturaTV = loadTexture("tv.jpeg");


    glutMainLoop();

    return 1;
}   