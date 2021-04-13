#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>

#include "Shader.h"


//Window resize callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//ProcessInput
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}


int main()
{

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );


    GLFWwindow* window = glfwCreateWindow( 800, 600, "LearnOpenGL", NULL, NULL );
    if ( window == NULL )
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent( window );

    if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport( 0, 0, 800, 600 );

    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    

    ////VertexShader
    //unsigned int vertexShader;
    //vertexShader = glCreateShader( GL_VERTEX_SHADER );

    ////Attach shader source code to shader object and compile shader.
    //glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    //glCompileShader( vertexShader );

    ////check if shader compiled
    //int success, successShader2;
    //char infoLog[512];
    //glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );

    //if ( !success )
    //{
    //    glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
    //    std::cout << "ERROR::SHADER::VERTEX::COMPILATION FAILED\n" << infoLog << std::endl;
    //}

    ////Fragment Shader
    //unsigned int fragmentShader[2];
    //fragmentShader[0] = glCreateShader( GL_FRAGMENT_SHADER );
    //fragmentShader[1] = glCreateShader( GL_FRAGMENT_SHADER );

    ////Attach shader source code to shader object and compile shader.
    //glShaderSource( fragmentShader[0], 1, &fragmentShaderSource, NULL );
    //glCompileShader( fragmentShader[0] );

    //glShaderSource( fragmentShader[1], 1, &fragmentShaderSourceYellow, NULL );
    //glCompileShader( fragmentShader[1] );

    ////check if fragment shader compiled
    //glGetShaderiv( fragmentShader[0], GL_COMPILE_STATUS, &success );
    //glGetShaderiv( fragmentShader[1], GL_COMPILE_STATUS, &successShader2 );

    //if ( !success || !successShader2 )
    //{
    //    glGetShaderInfoLog( fragmentShader[0], 512, NULL, infoLog );
    //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION FAILED\n" << infoLog << std::endl;
    //}

    ////Shader Program (Shader Program Object is the final linked version of multiple shaders combined)
    //unsigned int shaderProgram, shaderProgram2;
    //shaderProgram = glCreateProgram();
    //shaderProgram2 = glCreateProgram();

    ////Attach previously compiled shaders and link
    //glAttachShader( shaderProgram, vertexShader );
    //glAttachShader( shaderProgram, fragmentShader[0] );
    //glAttachShader( shaderProgram2, fragmentShader[1] );
    //glLinkProgram( shaderProgram );
    //glLinkProgram( shaderProgram2 );

    ////Check for errors
    //glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    //glGetProgramiv( shaderProgram, GL_LINK_STATUS, &successShader2 );
    //if ( !success || !successShader2 )
    //{
    //    glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
    //    std::cout << "ERROR::PROGRAM::LINKING FAILED\n" << infoLog << std::endl;
    //}

    //UseProgram. //ShaderProgram must be compiled and linked.
    //glUseProgram(shaderProgram);

    //Delete shaders once linked
    //glDeleteShader( vertexShader );
    //glDeleteShader( fragmentShader[0] );
    //glDeleteShader( fragmentShader[1] );

    Shader ourShader("Shaders/3.3.shader.vs","Shaders/3.3.shader.fs");

    //Set up vertex Data (and buffer[s]) and configure vertex attribs
    float vertices[] = {
    0.0f, 0.5f, 0.0f, /*Common Origin 0*/ 1.0f, 0.0f, 0.0f, /*Red Color*/
    -0.5f, 0.0f, 0.0f, /*Left Vertex  2*/ 0.0f, 1.0f, 0.0f, /*Green Color*/
    0.5f, 0.0f, 0.0f, /*Top Left     3*/ 0.0f, 0.0f, 1.0f, /*Blue Color*/
    };

    float vertices1[] = {
        0.0f, 0.0f, 0.0f, //Common Origin 0
        1.0f, 0.0f, 0.0f, //Right Vertex  1
        0.5f, 0.5f, 0.0f  //Top Right     4
    };

    unsigned int indices[] = {
        0, 1, 4, //first triangle
        0, 2, 3 //second triangle
    };
    

    //Buffer type of a vertex buffer object is GL_ARRAY_BUFFER
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );

    //Setup 1st Triangle
    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void* )0 );
    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( float ), ( void* )( 3 * sizeof( float ) ) );
    glEnableVertexAttribArray( 1 );


    //bind the vertex array object first. then bind and set the vertex buffer[s]. and than configure vertex attribs;
    //glBindVertexArray( VAO );
    //glBindVertexArray( VAO1 );

    //Bind VertexBuffer object
    //glBindBuffer( GL_ARRAY_BUFFER, VBO );
    //glBindBuffer( GL_ARRAY_BUFFER, VBO1 );
    //Allocate memory and store data.
   //glBufferData is function specifically targeted to copy 
   //user-defined data into the currently bound buffer.
   //GL_STATIC_DRAW is used because the position of
   //triangle does not change, is used a lot and
   //will stay the same for every render call.
    //glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    //glBufferData( GL_ARRAY_BUFFER, sizeof( vertices1 ), vertices1, GL_STATIC_DRAW );

    //Bind ElementBuffer Object
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );


    //Till now we have instructed the GPU how to process vertex data in vertex and fragment shader.
    //Now we need to tell it how to interpret the vertex data in memory
    //and how to connect the vertex data to the vertex shader's attributes
    //glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
    //glEnableVertexAttribArray( 0 );

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray( 0 );

    //render loop
    //----------
    while (!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //rendering commands...
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Activate the shader
        ourShader.use();
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );

        //draw our first triangle
        //float timeValue = glfwGetTime();
        //float greenValue = ( sin( timeValue ) / 2.0f ) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation( shaderProgram, "ourColor" );
        //glUniform4f( vertexColorLocation, 0.0f, greenValue, 0.0f, 0.0f );

        //glfw:: swap buffers and poll IO events.
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //deallocate all resources once they've outlived their purpose.
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );

    glfwTerminate();
    return 0;
}


