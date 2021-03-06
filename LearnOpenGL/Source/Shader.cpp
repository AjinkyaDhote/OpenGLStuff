#include "Shader.h"


Shader::Shader( const char* vertexPath, const char* fragmentPath )
{
    /*Retrieve vertex/fragment source code from filepath.*/

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    fShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
    
    try
    {
        vShaderFile.open( vertexPath );
        fShaderFile.open( fragmentPath );
        std::stringstream vShaderStream, fShaderStream;
        
        //read buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //close file handlers.
        vShaderFile.close();
        fShaderFile.close();

        //convert stream to string.
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch( std::ifstream::failure e )
    {
        std::cout << e.code() << std::endl;
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    /*Compile shader source code.*/
    unsigned int vertex, fragment;
    int success;
    char infoLog[32];

    vertex = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertex, 1, &vShaderCode, NULL );
    glCompileShader( vertex );

    glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( vertex, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragment, 1, &fShaderCode, NULL );
    glCompileShader( fragment );

    glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
    if( !success )
    {
        glGetShaderInfoLog( fragment, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
    }

    //shader Program
    ID = glCreateProgram();
    glAttachShader( ID, vertex );
    glAttachShader( ID, fragment );
    glLinkProgram( ID );

    //check linking errors
    glGetProgramiv( ID, GL_LINK_STATUS, &success );
    if ( !success )
    {
        glGetProgramInfoLog( ID, 512, NULL, infoLog );
        std::cout << "ERROR::SHADER::PROGRAM::LINKING FAILED\n" << infoLog << std::endl;
    }

    //delete the shaders as they are linked.
    glDeleteShader( vertex );
    glDeleteShader( fragment );
}

void Shader::use()
{
    glUseProgram( ID );
}

void Shader::setBool( const std::string& name, bool value ) const
{
    glUniform1i( glGetUniformLocation( ID, name.c_str() ), (int) value );
}

void Shader::setInt( const std::string& name, int value ) const
{
    glUniform1i( glGetUniformLocation( ID, name.c_str() ), (int) value );
}

void Shader::setFloat( const std::string& name, float value ) const
{
    glUniform1f( glGetUniformLocation( ID, name.c_str() ), (float) value );
}

void Shader::setMat4( const std::string& name, const glm::mat4 &mat ) const
{
    glUniformMatrix4fv( glGetUniformLocation( ID, name.c_str() ), 1, GL_FALSE, &mat[0][0] );
}