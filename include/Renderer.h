#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl\glu.h>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include "Settings.h"
#include "Window.h"
#include "BasicGeometry.h"
#include "Transform.h"
#include "Scene.h"
class Light;
class Camera;
class Renderer{
    public:
        Renderer(Window const& window, Settings const& settings);
        ~Renderer();
        void render(Scene const& scsene);
    private:
        Settings m_settings;
        const Window& m_window;
        void initGL();


        GLuint m_programID = 0;
        GLint m_vertexPos2DLocation = -1;
        GLuint m_VBO = 0;
        GLuint m_IBO = 0;
        SDL_GLContext m_Context;



        
};

#endif