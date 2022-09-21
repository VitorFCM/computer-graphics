#ifndef GLOBJECTS_H
#define GLOBJECTS_H

#define translation_matrix(t_x,t_y,t_z) {   \
            1.0f, 0.0f, 0.0f, t_x,          \
            0.0f, 1.0f, 0.0f, t_y,          \
            0.0f, 0.0f, 1.0f, t_z,          \
            0.0f, 0.0f, 0.0f, 1.0f          \
        }                                   \

#define rotation_z_matrix(theta) {                                                  \
            cos(((theta)*M_PI/180.0)), -sin(((theta)*M_PI/180.0)), 0.0f, 0.0f,      \
            sin(((theta)*M_PI/180.0)),  cos(((theta)*M_PI/180.0)), 0.0f, 0.0f,      \
            0.0f, 0.0f, 1.0f, 0.0f,                                                 \
            0.0f, 0.0f, 0.0f, 1.0f                                                  \
        }
        
#define scale_matrix(s_x,s_y,s_z) {     \
            s_x, 0.0f, 0.0f, 0.0f,      \
            0.0f, s_y, 0.0f, 0.0f,      \
            0.0f, 0.0f, s_z, 0.0f,      \
            0.0f, 0.0f, 0.0f, 1.0f      \
        }                               \

typedef struct coordinates {
    float x, y;
} coordinates;


typedef struct glObject {
    
    unsigned int number_vertices;
    coordinates *vertices;

    float t_x;
    float t_y;
    float t_z;

    float s_x;
    float s_y;
    float s_z;

    float theta;

} glObject;


void initializeObject(glObject *o, unsigned int number_verticex);
void destroyObject(glObject *o);

/* ---------------------------------------- */
void veccpy(coordinates *dest, unsigned int size_dest, coordinates *origin, unsigned int size_origin);
coordinates* veccnt(coordinates *c1, unsigned int size_1, coordinates *c2, unsigned int size_2);
#endif