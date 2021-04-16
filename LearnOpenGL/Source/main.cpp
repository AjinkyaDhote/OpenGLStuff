#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>

#include "Shader.h"
#include "stb_image.h"


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

    Shader ourShader("Shaders/3.3.shader.vs","Shaders/3.3.shader.fs");

    //Set up vertex Data (and buffer[s]) and configure vertex attribs. //Time to make a rectangle
    float vertices[] = {
    //Vertices          //Colors           //Texture coords
    0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,      /*Top Right Vertex */
    0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,      /*Bottom Right vertex*/
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,      /*Bottom Left Vertex*/
    -0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f       /*Top Left Vertex*/
    };

    unsigned int indices[] = {
        0, 1, 3, //first triangle
        1, 2, 3 //second triangle
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
    //vertices
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( void* )0 );
    glEnableVertexAttribArray( 0 );

    //color
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( void* )( 3 * sizeof( float ) ) );
    glEnableVertexAttribArray( 1 );

    //Texture coords
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), (void*)(6 * sizeof( float )) );
    glEnableVertexAttribArray( 2 );

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

    //Fun Part!!! TEXTURES YAY
    unsigned int texture1, texture2;
    glGenTextures( 1, &texture1 );
    glBindTexture( GL_TEXTURE_2D, texture1 );

    //Texture Wrapping
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT ); 
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    //Texture Filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR ); //Try using GL_NEAREST
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); //Try using GL_NEAREST

    //Load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load( "Resources/Textures/container.jpg", &width, &height, &nrChannels, 0 );
    if ( data )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D ); //This call will automagically generate all the required mipmaps for the currently bound texture.
    }
    else
    {\
        std::cout << "Failed to load texture1" << std::endl;
    }
    stbi_image_free( data );

    //2nd Texture
    glGenTextures( 1, &texture2 );
    glBindTexture( GL_TEXTURE_2D, texture2 );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    stbi_set_flip_vertically_on_load( true );
    data = stbi_load( "Resources/Textures/awesomeface.png", &width, &height, &nrChannels, 0 );
    if ( data )
    {
        //awesomeface.png has transparency and thus an alpha channel, which is why we need to send GL_RGBA.
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
        glGenerateMipmap( GL_TEXTURE_2D );
    }
    else
    {
        std::cout << "Failed to load texture2" << std::endl;
    }
    stbi_image_free( data );

    //Activate the program
    ourShader.use(); //Activate the shader before using uniforms
    ourShader.setInt( "texture1", 0 );
    ourShader.setInt( "texture2", 1 );


    //render loop
    //----------
    while (!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        //rendering commands...
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //bind Texture
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture1 );
        glActiveTexture( GL_TEXTURE1 );
        glBindTexture( GL_TEXTURE_2D, texture2 );


        ourShader.use();
        glBindVertexArray( VAO );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

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
    glDeleteBuffers( 1, &EBO );

    glfwTerminate();
    return 0;
}


