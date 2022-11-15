#ifndef GLUTILS_H
#define GLUTILS_H

#include <iostream>
#include <exception>

class GLRuntimeException: public std::exception {
public:
    GLRuntimeException(std::string msg)
            : msg(msg)
    {}
private:
    virtual const char * what() const throw(){
        return msg.c_str();
    }
    std::string msg;
};

// print buffer status errors
GLuint glBufferStatus(const std::string c = ""){
    GLuint e = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (e != GL_FRAMEBUFFER_COMPLETE){__android_log_print(ANDROID_LOG_INFO, "", "%s", c.c_str());}
    switch(e){
        case GL_FRAMEBUFFER_UNDEFINED:
            throw GLRuntimeException(" GLERROR: GL_FRAMEBUFFER_UNDEFINED");
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            throw GLRuntimeException(" GLERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            throw GLRuntimeException(" GLERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
            break;

        case GL_FRAMEBUFFER_UNSUPPORTED:
            throw GLRuntimeException(" GLERROR: GL_FRAMEBUFFER_UNSUPPORTED");
            break;

        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            throw GLRuntimeException(" GLERROR: GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE");
            break;
    }
    return e;
}

// print gl error codes
GLuint glError(const std::string c = ""){
    GLuint e = glGetError();
    if (e != GL_NO_ERROR){__android_log_print(ANDROID_LOG_INFO, "", "%s", c.c_str());}
    switch(e){
        case GL_NO_ERROR:
         break;
        case GL_INVALID_ENUM:
            throw GLRuntimeException(" GL_INVALID_ENUM");
            break;
        case GL_INVALID_VALUE:
            throw GLRuntimeException(" GLERROR: GL_INVALID_VALUE");
            break;
        case GL_INVALID_OPERATION:
            throw GLRuntimeException(" GLERROR: GL_INVALID_OPERATION");
            break;
        case GL_OUT_OF_MEMORY:
            throw GLRuntimeException(" GLERROR: GL_OUT_OF_MEMORY");
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            throw GLRuntimeException(" GLERROR: GL_INVALID_FRAMEBUFFER_OPERATION");
            break;
    }
    return e;
}

// compile a gl shader given a program and source code as const char *
void compileShader(GLuint & shaderProgram, const char * vert, const char * frag){

    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vert,NULL);
    glCompileShader(vertexShader);

    // check it worked!
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&frag,NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);

    // check it linked
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}


#endif
