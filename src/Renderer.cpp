#include "Renderer.h"
#include "Camera.h"
#include "Light.h"
#include <float.h>
Renderer::Renderer(Window const& window, Settings const& settings):m_settings(settings), m_window(window){
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE ); 
    m_Context = SDL_GL_CreateContext( window.gWindow );


    glewInit();

    SDL_GL_SetSwapInterval(1);

    initGL();
}
Renderer::~Renderer(){

}


void Renderer::render(Scene const& scsene)
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    

        
    glUseProgram( m_programID );

 
    glEnableVertexAttribArray( m_vertexPos2DLocation );

     
    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
    glVertexAttribPointer( m_vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );


    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
    glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );


    glDisableVertexAttribArray( m_vertexPos2DLocation );


    glUseProgram( NULL );

    SDL_GL_SwapWindow(m_window.gWindow);

}


void Renderer::initGL(){
    m_programID = glCreateProgram();


    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

    const GLchar* vertexShaderSource[] =
    {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };


    glShaderSource( vertexShader, 1, vertexShaderSource, NULL );


    glCompileShader( vertexShader );


    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
    if( vShaderCompiled != GL_TRUE )
    {
        printf( "Unable to compile vertex shader %d!\n", vertexShader );

    }
    else
    {

        glAttachShader( m_programID, vertexShader );



        GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );


        const GLchar* fragmentShaderSource[] =
        {
            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
        };


        glShaderSource( fragmentShader, 1, fragmentShaderSource, NULL );


        glCompileShader( fragmentShader );


        GLint fShaderCompiled = GL_FALSE;
        glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
        if( fShaderCompiled != GL_TRUE )
        {
            printf( "Unable to compile fragment shader %d!\n", fragmentShader );

        }
        else
        {

            glAttachShader( m_programID, fragmentShader );



            glLinkProgram( m_programID );


            GLint programSuccess = GL_TRUE;
            glGetProgramiv( m_programID, GL_LINK_STATUS, &programSuccess );
            if( programSuccess != GL_TRUE )
            {
                printf( "Error linking program %d!\n", m_programID );

            }
            else
            {
                //Get vertex attribute location
                m_vertexPos2DLocation = glGetAttribLocation( m_programID, "LVertexPos2D" );
                if( m_vertexPos2DLocation == -1 )
                {
                    printf( "LVertexPos2D is not a valid glsl program variable!\n" );
                }
                else
                {
                    //Initialize clear color
                    glClearColor( 0.f, 0.f, 0.f, 1.f );

                    //VBO data
                    GLfloat vertexData[] =
                    {
                        -0.5f, -0.5f,
                         0.5f, -0.5f,
                         0.5f,  0.5f,
                        -0.5f,  0.5f
                    };

                    //IBO data
                    GLuint indexData[] = { 0, 1, 2, 3 };

                    //Create VBO
                    glGenBuffers( 1, &m_VBO );
                    glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
                    glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

                    //Create IBO
                    glGenBuffers( 1, &m_IBO );
                    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
                    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
                }                
            }
            
              
        }      
    }
}