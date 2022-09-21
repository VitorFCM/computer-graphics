#ifndef FORMAS_H
#define FORMAS_H

#define coordinates_estrela{\
	{  -0.5f, +0.25f },\
	{ -0.75f, -0.25f },\
	{ -0.25f, -0.25f },\
	{ -0.75f, +0.10f },\
	{ -0.25f, +0.10f },\
	{ -0.5f, -0.40f }\
}\

#define desenha_estrela(vertices, loc, loc_color, matriz) 							\
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);	\
		glUniformMatrix4fv(loc, 1, GL_TRUE, matriz);								\
		glUniform4f(loc_color, 1.0, 1.0, 0.0, 1.0);									\
		glDrawArrays(GL_TRIANGLES, 0, 3);											\
		glDrawArrays(GL_TRIANGLES, 3, 3);											\

#define paredes_casa {\
	{  0.0f, -0.5f },\
	{ +0.5f, -0.5f },\
	{ 0.0f, -1.0f },\
	{ +0.5f, -1.0f }\
}\


#define janela_esq {\
	{ +0.05f, -0.6f },\
	{ +0.05f, -0.7f },\
	{ +0.15f, -0.6f },\
	{ +0.15f, -0.7f }\
}\


#define janela_dir {\
	{ +0.35f, -0.6f },\
	{ +0.35f, -0.7f },\
	{ +0.45f, -0.6f },\
	{ +0.45f, -0.7f },\
}\


#define porta_casa {\
	{ +0.2f, -0.72f },\
	{ +0.2f, -1.0f },\
	{ +0.3f, -0.72f },\
	{ +0.3f, -1.0f },\
}\


#define telhado_casa {\
	{ -0.03f, -0.5f },\
	{ +0.53f, -0.5f },\
	{ +0.25f, -0.3f },\
}\

#define desenha_casa(v_pa, v_je, v_jd, v_po, v_te, loc, loc_color, matriz)							\
		glUniformMatrix4fv(loc, 1, GL_TRUE, matriz);												\
		glBufferData(GL_ARRAY_BUFFER, sizeof(v_pa), v_pa, GL_DYNAMIC_DRAW);							\
		glUniform4f(loc_color, 0.0, 0.0, 1.0, 1.0);													\
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);														\
		glBufferData(GL_ARRAY_BUFFER, sizeof(v_je), v_je, GL_DYNAMIC_DRAW);							\
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);													\
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);														\
		glBufferData(GL_ARRAY_BUFFER, sizeof(v_jd), v_jd, GL_DYNAMIC_DRAW);							\
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);													\
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);														\
		glBufferData(GL_ARRAY_BUFFER, sizeof(v_po), v_po, GL_DYNAMIC_DRAW);							\
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);													\
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);														\
		glBufferData(GL_ARRAY_BUFFER, sizeof(v_te), v_te, GL_DYNAMIC_DRAW);							\
		glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0);													\
		glDrawArrays(GL_TRIANGLES, 0, 3);															\

#define corpo_foguete {\
	{ -0.0625f, -0.25f },\
	{ +0.0625f, -0.25f },\
	{ -0.0625f, +0.25f },\
	{ +0.0625f, +0.25f }\
}\

#define triangulos_foguete {\
	{-0.0625f, 0.25f},\
	{0.0625f, 0.25f},\
	{0.0f, 0.35f},\
	{-0.06f, -0.25f},\
	{-0.04f, -0.35f},\
	{-0.08f, -0.35f},\
	{0.06f, -0.25f},\
	{0.04f, -0.35f},\
	{0.08f, -0.35f}\
}\

#define lataria_carro(x,y) {\
	{ -0.9f+x, -0.97f+y },\
	{ -0.9f+x, -0.87f+y },\
	{ -0.4f+x, -0.97f+y },\
	{ -0.4f+x, -0.87f+y }\
}\

#endif
