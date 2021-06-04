#include<glad/glad.h>
#include<glfw3.h>
#include<iostream>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "stb_image.h"


//Window resize callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

float g_MixValue = 0.2f;

//ProcessInput
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    //Fade Effect
    if ( glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS )
    {
        g_MixValue = g_MixValue > 1.0f ? 1.0f : g_MixValue + 0.001f;
    }

    else if ( glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS )
    {
        g_MixValue = g_MixValue < 0.0f ? 0.0f : g_MixValue - 0.001f;
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
    // positions          // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3, //first triangle
        1, 2, 3 //second triangle
    };
    

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f ),
        glm::vec3( 2.0f,  5.0f, -15.0f ),
        glm::vec3( -1.5f, -2.2f, -2.5f ),
        glm::vec3( -3.8f, -2.0f, -12.3f ),
        glm::vec3( 2.4f, -0.4f, -3.5f ),
        glm::vec3( -1.7f,  3.0f, -7.5f ),
        glm::vec3( 1.3f, -2.0f, -2.5f ),
        glm::vec3( 1.5f,  2.0f, -2.5f ),
        glm::vec3( 1.5f,  0.2f, -1.5f ),
        glm::vec3( -1.3f,  1.0f, -1.5f )
    };


    //Buffer type of a vertex buffer object is GL_ARRAY_BUFFER
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );

    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
    //Bind ElementBuffer Object
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );


    //position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), ( void* )0 );
    glEnableVertexAttribArray( 0 );

    //color
    //glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( float ), ( void* )( 3 * sizeof( float ) ) );
    //glEnableVertexAttribArray( 1 );

    //Texture coord attribute
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void*)(3 * sizeof( float )) );
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




    //Till now we have instructed the GPU how to process vertex data in vertex and fragment shader.
    //Now we need to tell it how to interpret the vertex data in memory
    //and how to connect the vertex data to the vertex shader's attributes
    //glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), (void*)0 );
    //glEnableVertexAttribArray( 0 );

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray( 0 );

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
    {
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


   // glm::mat4 trans = glm::mat4( 1.0f ); //WTF IS THIS DOING? IT SAYS IDENTITY MATRIX
   // trans = glm::rotate( trans, glm::radians( 90.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ) );
   // trans = glm::scale( trans, glm::vec3( 0.5f, 0.5f, 0.5f ) );
   //
   // unsigned int transformLoc = glGetUniformLocation( ourShader.ID, "transform" );
    //glUniformMatrix4fv( transformLoc, 1, GL_FALSE, );
   
   //Enable Depth Testing
    glEnable( GL_DEPTH_TEST );

    //render loop
    //----------
    while (!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);


        //rendering commands...
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        //Rotate and Translate
        //glm::mat4 trans = glm::mat4( 1.0f );
        //trans = glm::translate( trans, glm::vec3( 0.5f, -0.5f, 0.0f ) );
        //trans = glm::rotate( trans, (float)glfwGetTime(), glm::vec3( 0.0f, 0.0f, 1.0f ) );
        //glUniformMatrix4fv( transformLoc, 1, GL_FALSE, glm::value_ptr( trans ) );

        //bind Texture
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture1 );
        glActiveTexture( GL_TEXTURE1 );
        glBindTexture( GL_TEXTURE_2D, texture2 );
        
        //activate shader
        ourShader.use();


     //Going 3D------------------------------------------------------------------------------------------------------

    //Creating a model matrix (By multiplying the vertex coordinates with this model matrix we are transforming the 
    //vertex coordinates to world coordinates).
        glm::mat4 model = glm::mat4( 1.0f );
        model = glm::rotate( model, (float) glfwGetTime() *  glm::radians( -55.0f ), glm::vec3( 0.5f, 1.0f, 0.0f ) );
        
        //Creatring a view matrix (We need to move slightly backwards in the scene so the object becomes visible
        //To move the camera backwards is the same as moving the scene forward.)
        glm::mat4 view = glm::mat4( 1.0f );
        view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );
        
        //Creating a projection matrix. We need to use perspective projection for our scene.
        glm::mat4 projection;
        projection = glm::perspective( glm::radians( 45.0f ), 800.0f / 600.0f, 0.1f, 100.0f );
        
        
        //--------------------------------------------------------------------------------------------------------------
        
        //Going 3D
        int modelLoc = glGetUniformLocation( ourShader.ID, "model" );
        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        
        int viewLoc = glGetUniformLocation( ourShader.ID, "view" );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        
        int projectionLoc = glGetUniformLocation( ourShader.ID, "projection" );
        glUniformMatrix4fv( projectionLoc, 1, GL_FALSE, glm::value_ptr( projection ) );


        //Code to fade the 2nd texture
        //ourShader.setFloat( "fadeValue", g_MixValue );

        //Render 
        
        glBindVertexArray( VAO );
        //glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        for ( unsigned int i = 0; i < 10; i++ )
        {
            glm::mat4 model = glm::mat4( 1.0f );
            model = glm::translate( model, cubePositions[i] );
            float angle = 20.0f * i;
            if ( i % 3 == 0 )  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = glfwGetTime() * 25.0f;
            model = glm::rotate( model, glm::radians( angle ), glm::vec3( 1.0f, 0.3f, 0.5f ) );
            ourShader.setMat4( "model", model );

            glDrawArrays( GL_TRIANGLES, 0, 36 );
        }

        //trans = glm::mat4( 1.0f );
        //trans = glm::translate( trans, glm::vec3( -0.5f, 0.5f, 0.0f ) );
        //float scaleAmount = sin( glfwGetTime() );
        //trans = glm::scale( trans, glm::vec3( scaleAmount, scaleAmount, scaleAmount ));
        //glUniformMatrix4fv( transformLoc, 1, GL_FALSE,&trans[0][0] );

        //glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

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


