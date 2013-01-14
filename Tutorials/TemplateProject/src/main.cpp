// Include OpenGL ES Engine utils
#include "es_util.h"

float count = 0.0f;

using namespace yam2d;

///
// Initialize the shader and program object
//
int init ( ESContext *esContext )
{

	return TRUE;
}

///
// Draw a triangle using the shader pair created in Init()
//
void draw ( ESContext *esContext )
{
	float vertexData[] = 
	{
		0.3f, -0.3f, 0.0f,
	   -0.3f, -0.3f, 0.0f,
		0.0f, 0.3f, 0.0f,
	};

	// Set the viewport
	glViewport( 0, 0, esContext->width, esContext->height );
   
	// Set OpenGL clear color
	glClearColor( float(count), 0.0f, 0.0f, 0.0f );

	// Clear the color buffer
	glClear ( GL_COLOR_BUFFER_BIT );
	
	// Enable vertex arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	
	// Set vertex data
	glVertexPointer( 3, GL_FLOAT, 0, &vertexData );

	// Draw one triangle
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Disable vertex arrays
	glDisableClientState(GL_VERTEX_ARRAY);
	
	// Swap to back buffer
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void update( ESContext*, float deltaTime )
{
	count += deltaTime;

	if( count > 1.0f )
		count = 0.0f;
}


int main ( int argc, char *argv[] )
{
	ESContext esContext;
	esInitContext ( &esContext );
	esCreateWindow( &esContext, "Hello Triangle", 1280, 720, ES_WINDOW_DEFAULT );
   
	if ( !init ( &esContext ) )
		return 0;

	esRegisterDrawFunc( &esContext, draw );
	esRegisterUpdateFunc( &esContext, update );
      
	esMainLoop ( &esContext );
	return 0;
}