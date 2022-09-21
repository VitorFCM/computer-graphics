import glfw
from OpenGL.GL import *
import numpy as np

glfw.init()
glfw.window_hint(glfw.VISIBLE, glfw.FALSE);
window = glfw.create_window(720, 600, "Cores", None, None)
glfw.make_context_current(window)


vertex_code = """
        attribute vec2 position;
        void main(){
            gl_Position = vec4(position,0.0,1.0);
        }
        """

fragment_code = """
        uniform vec4 color;
        void main(){
            gl_FragColor = color;
        }
        """
# Request a program and shader slots from GPU
program  = glCreateProgram()
vertex   = glCreateShader(GL_VERTEX_SHADER)
fragment = glCreateShader(GL_FRAGMENT_SHADER)

# Set shaders source
glShaderSource(vertex, vertex_code)
glShaderSource(fragment, fragment_code)

# Compile shaders
glCompileShader(vertex)
if not glGetShaderiv(vertex, GL_COMPILE_STATUS):
    error = glGetShaderInfoLog(vertex).decode()
    print(error)
    raise RuntimeError("Erro de compilacao do Vertex Shader")

glCompileShader(fragment)
if not glGetShaderiv(fragment, GL_COMPILE_STATUS):
    error = glGetShaderInfoLog(fragment).decode()
    print(error)
    raise RuntimeError("Erro de compilacao do Fragment Shader")

# Attach shader objects to the program
glAttachShader(program, vertex)
glAttachShader(program, fragment)

# Build program
glLinkProgram(program)
if not glGetProgramiv(program, GL_LINK_STATUS):
    print(glGetProgramInfoLog(program))
    raise RuntimeError('Linking error')
    
# Make program the default program
glUseProgram(program)

#Foguete

#preparando espaço para 4 vértices usando 2 coordenadas (x,y)
vertices = np.zeros(4, [("position", np.float32, 2)])

# preenchendo as coordenadas de cada vértice do retangulo
vertices['position'] = [
                            (-0.0625, -0.25), # vertice 0
                            (+0.0625, -0.25), # vertice 1
                            (-0.0625, +0.25), # vertice 2
                            (+0.0625, +0.25) #vertice 3
                        ]

#preenchendo as coordenadas do circulo
import math # para calculo com sin e cos

num_vertices = 128 # define a "qualidade" do circulo
pi = 3.14
counter = 0
radius = 0.05
verticesCirc = np.zeros(num_vertices, [("position", np.float32, 2)])

angle = 0.0
for counter in range(num_vertices):
    angle += 2*pi/num_vertices 
    x = math.cos(angle)*radius
    y = 0.125 + math.sin(angle)*radius
    verticesCirc[counter] = [x,y]

verticesTriangs = np.zeros(9, [("position", np.float32, 2)])
verticesTriangs['position'] = [
                                (-0.0625, 0.25),
                                (0.0625, 0.25),
                                (0, 0.35),

                                (-0.06, -0.25),
                                (-0.04, -0.35),
                                (-0.08, -0.35),

                                (0.06, -0.25),
                                (0.04, -0.35),
                                (0.08, -0.35)
                                
]


#Carro

verticesCar = np.zeros(4, [("position", np.float32, 2)])
verticesCar['position'] = [                            
                            (-0.9, 0.9), 
                            (-0.9, 0.8), 
                            (-0.4, 0.9), 
                            (-0.4, 0.8) 
]

counter = 0
verticesRoda1 = np.zeros(num_vertices, [("position", np.float32, 2)])
angle = 0.0
for counter in range(num_vertices):
    angle += 2*pi/num_vertices 
    x = -0.85 + math.cos(angle)*radius
    y = 0.8 + math.sin(angle)*radius
    verticesRoda1[counter] = [x,y]

counter = 0
verticesRoda2 = np.zeros(num_vertices, [("position", np.float32, 2)])
angle = 0.0
for counter in range(num_vertices):
    angle += 2*pi/num_vertices 
    x = -0.45 + math.cos(angle)*radius
    y = 0.8 + math.sin(angle)*radius
    verticesRoda2[counter] = [x,y]


#Boneco

counter = 0
verticesCabeca = np.zeros(num_vertices, [("position", np.float32, 2)])
angle = 0.0
radiusCabeca = 0.1
for counter in range(num_vertices):
    angle += 2*pi/num_vertices 
    x = 0.7 + math.cos(angle)*radiusCabeca
    y = 0.5 + math.sin(angle)*radiusCabeca
    verticesCabeca[counter] = [x,y]

counter = 0
verticesCorpo = np.zeros(num_vertices, [("position", np.float32, 2)])
angle = 0.0
radiusCorpo = 0.2
for counter in range(num_vertices):
    angle += 2*pi/num_vertices 
    x = 0.7 + math.cos(angle)*radiusCorpo
    y = 0.3 + math.sin(angle)*radiusCorpo
    verticesCorpo[counter] = [x,y]


verticesOlho1 = np.zeros(4, [("position", np.float32, 2)])
angle = 0.0
radiusOlhos = 0.05
for counter in range(num_vertices):
    angle += 2*pi/num_vertices 
    x = 0.625 + math.cos(angle)*radiusOlhos
    y = 0.5 + math.sin(angle)*radiusOlhos
    verticesCorpo[counter] = [x,y]


verticesOlho2 = np.zeros(4, [("position", np.float32, 2)])
angle = 0.0
for counter in range(num_vertices):
    angle += 2*pi/num_vertices 
    x = 0.675 + math.cos(angle)*radiusOlhos
    y = 0.5 + math.sin(angle)*radiusOlhos
    verticesCorpo[counter] = [x,y]



#Requisicao de um espaco de buffer na GPU
buffer = glGenBuffers(1)

#Faz esse buffer o padrao
glBindBuffer(GL_ARRAY_BUFFER, buffer)

#Foguete

## Faz upload dos dados do retangulo
glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)

#circulo
glBufferData(GL_ARRAY_BUFFER, verticesCirc.nbytes, verticesCirc, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)

#os triangulos
glBufferData(GL_ARRAY_BUFFER, verticesTriangs.nbytes, verticesTriangs, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)

#Carro

glBufferData(GL_ARRAY_BUFFER, verticesCar.nbytes, verticesCar, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)

glBufferData(GL_ARRAY_BUFFER, verticesRoda1.nbytes, verticesRoda1, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)


glBufferData(GL_ARRAY_BUFFER, verticesRoda2.nbytes, verticesRoda2, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)


#Boneco

glBufferData(GL_ARRAY_BUFFER, verticesCabeca.nbytes, verticesCabeca, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)

glBufferData(GL_ARRAY_BUFFER, verticesCorpo.nbytes, verticesCorpo, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)

glBufferData(GL_ARRAY_BUFFER, verticesOlho1.nbytes, verticesOlho1, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)

glBufferData(GL_ARRAY_BUFFER, verticesOlho2.nbytes, verticesOlho2, GL_DYNAMIC_DRAW)
glBindBuffer(GL_ARRAY_BUFFER, buffer)

# Bind the position attribute
# --------------------------------------
#strideCirc = verticesCirc.strides[0]
stride = vertices.strides[0]
offset = ctypes.c_void_p(0)

loc = glGetAttribLocation(program, "position")
glEnableVertexAttribArray(loc)

glVertexAttribPointer(loc, 2, GL_FLOAT, False, stride, offset)
#glVertexAttribPointer(loc, 2, GL_FLOAT, False, strideCirc, offset)

glfw.show_window(window)
loc_color = glGetUniformLocation(program, "color")

while not glfw.window_should_close(window):

    glfw.poll_events() 
    
    #glPolygonMode(GL_FRONT_AND_BACK,GL_LINE) ## ative esse comando para enxergar os triângulos
    glClear(GL_COLOR_BUFFER_BIT) 
    glClearColor(0.3, 0.3, 0.3, 1.0)
    
    #Desenho do foguete
    glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 0.0, 0.0, 0.0, 1.0) ###cor do objeto
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4) #retangulo

    glBufferData(GL_ARRAY_BUFFER, verticesCirc.nbytes, verticesCirc, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 0.0, 0.0, 1.0, 1.0) ###cor do objeto
    glDrawArrays(GL_TRIANGLE_FAN, 0, len(verticesCirc)) #circulo 

    glBufferData(GL_ARRAY_BUFFER, verticesTriangs.nbytes, verticesTriangs, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 0.0, 0.0, 1.0, 1.0)
    glDrawArrays(GL_TRIANGLES, 0, 3)
    glDrawArrays(GL_TRIANGLES, 3, 3)
    glDrawArrays(GL_TRIANGLES, 6, 3)

    #Desenho do carro
    glBufferData(GL_ARRAY_BUFFER, verticesCar.nbytes, verticesCar, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 1.0, 0.0, 0.0, 1.0)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4)

    glBufferData(GL_ARRAY_BUFFER, verticesRoda1.nbytes, verticesRoda1, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 0.0, 0.0, 0.0, 1.0)
    glDrawArrays(GL_TRIANGLE_FAN, 0, len(verticesRoda1))

    glBufferData(GL_ARRAY_BUFFER, verticesRoda2.nbytes, verticesRoda2, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 0.0, 0.0, 0.0, 1.0)
    glDrawArrays(GL_TRIANGLE_FAN, 0, len(verticesRoda2))


    #Desenho do boneco
    glBufferData(GL_ARRAY_BUFFER, verticesCabeca.nbytes, verticesCabeca, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 1.0, 1.0, 1.0, 1.0)
    glDrawArrays(GL_TRIANGLE_FAN, 0, len(verticesCabeca))

    glBufferData(GL_ARRAY_BUFFER, verticesCorpo.nbytes, verticesCorpo, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 1.0, 1.0, 1.0, 1.0)
    glDrawArrays(GL_TRIANGLE_FAN, 0, len(verticesCorpo))

    glBufferData(GL_ARRAY_BUFFER, verticesOlho1.nbytes, verticesOlho1, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 1.0, 1.0, 1.0, 1.0)
    glDrawArrays(GL_TRIANGLE_FAN, 0, len(verticesOlho1))
    glBufferData(GL_ARRAY_BUFFER, verticesOlho2.nbytes, verticesOlho2, GL_DYNAMIC_DRAW)
    glUniform4f(loc_color, 1.0, 1.0, 1.0, 1.0)
    glDrawArrays(GL_TRIANGLE_FAN, 0, len(verticesOlho2))


    glfw.swap_buffers(window)

glfw.terminate()