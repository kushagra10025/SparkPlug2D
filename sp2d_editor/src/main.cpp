#define SDL_MAIN_HANDLED 1;
#include <Windowing/Window/Window.h>
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

int main(int argc, char** argv)
{
	bool running = true;

	// Init SDL
	SDL_SetMainReady();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // This can be used instead of individually adding the INIT Flags.
		// Removed the SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER flags as they were adding Delay in INIT
		// The Delay is sometimes sorted out by restarting the computer.
		//if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_HAPTIC) != 0)
	{
		std::string error = SDL_GetError();
		std::cout << "SDL Init Failed! : " << error << std::endl;
		running = false;
		return -1;
	}

	// Setup OpenGL
	if (SDL_GL_LoadLibrary(NULL) != 0)
	{
		std::string error = SDL_GetError();
		std::cout << "SDL OpenGL Load Failed! : " << error << std::endl;
		running = false;
		return -1;
	}

	// Set OpenGL Attribs
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Set Number of Bits per Channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // Hardware Acceleration

	// Create the Window
	//SP2D::Windowing::Window window("Demo Window", 640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true, SDL_WINDOW_OPENGL);
	SP2D::Windowing::Window window("Demo Window", 640, 480, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, true, (SDL_WINDOW_OPENGL));

	if (!window.GetWindow())
	{
		std::cout << "SDL Window Creation Failed! : " << std::endl;
		running = false;
		return -1;
	}

	// Create the OpenGL Context
	window.SetGLContext(SDL_GL_CreateContext(window.GetWindow().get()));

	if (!window.GetGLContext())
	{
		std::string error = SDL_GetError();
		std::cout << "SDL Failed to Create OpenGL Context! : " << error << std::endl;
		running = false;
		return -1;
	}

	SDL_GL_MakeCurrent(window.GetWindow().get(), window.GetGLContext());
	SDL_GL_SetSwapInterval(1);

	// Initialize Glad
	if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
	{
		std::cout << "Failed to Initialize GLAD! : " << std::endl;
		running = false;
		return -1;
	}

	// Temp Vertex Data
	// Vertices for a Triangle
	//float vertices[] =
	//{
	//	0.0f, 0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f
	//};

	// Vertices for a Quad
	float vertices[] =
	{
		-0.5f, 0.5f, 0.0f,		// TL
		0.5f, 0.5f, 0.0f,		// TR
		0.5f, -0.5f, 0.0f,		// BR
		-0.5f, -0.5f, 0.0f,		// BL
	};

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	// Temp Vertex Source
	const char* vertexSource =
		"#version 460 core\n"
		"layout (location = 0) in vec3 aPosition;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPosition, 1.0);\n"
		"}\0";

	// Create the shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Add Vertex Shader Source
	glShaderSource(vertexShader, 1, &vertexSource, NULL);

	// Compile the Vertex Shader
	glCompileShader(vertexShader);

	int vertexStatus;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexStatus);

	if (!vertexStatus)
	{
		char infoLog[512];
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Failed to Compile Vertex Shader!\n" << infoLog << std::endl;
		return -1;
	}

	// Temp Fragment Source
	const char* fragmentSource =
		"#version 460 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"	color = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\0";

	// Create the shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Add Fragment Shader Source
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

	// Compile the Fragment Shader
	glCompileShader(fragmentShader);

	int fragmentStatus;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentStatus);

	if (!fragmentStatus)
	{
		char infoLog[512];
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Failed to Compile Fragment Shader!\n" << infoLog << std::endl;
		return -1;
	}

	// Create the Shader Program
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	// Attach the above shaders to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link Program
	glLinkProgram(shaderProgram);

	// Check link Status
	int programStatus;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programStatus);

	if (!programStatus)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Failed to Link the Shader Program!\n" << infoLog << std::endl;
		return -1;
	}

	// Enabled ShaderProgram
	glUseProgram(shaderProgram);

	// Safe to delete the shaders once shaderprogram is created and linked
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// VAO and VBO creation
	GLuint VAO, VBO, IBO;

	// Generate VAO & VBO & IBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	// Bind VAO & VBO & IBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(
		GL_ARRAY_BUFFER,						// Target Buffer Type
		sizeof(vertices) * 3 * sizeof(float),	// The size in Bytes of the Buffer Object's New Data Store
		vertices,								// Pointer to data that will be copied into Data Store
		GL_STATIC_DRAW							// Expected usage pattern of the data store
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,				// Target Buffer Type
		6 * sizeof(GLuint),						// The size in Bytes of the Buffer Object's New Data Store
		indices,								// Pointer to data that will be copied into Data Store
		GL_STATIC_DRAW							// Expected usage pattern of the data store
	);

	glVertexAttribPointer(
		0,										// Attrib 0 - The layout position in the vertex shader
		3,										// Size - Number of components per vertex
		GL_FLOAT,								// Type - data type of above component
		GL_FALSE,								// Normalized - Specifies if fixed-point data values should be normalized
		3 * sizeof(float),						// Stride - Specifies the byte offset b/w consecutive attribs
		(void*)0								// Pointer - Offset of the First Component
	);

	glEnableVertexArrayAttrib(VAO, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	SDL_Event event{};

	// Window Loop
	while (running)
	{
		// Process Events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym = SDLK_ESCAPE)
					running = false;
				break;
			default:
				break;
			}
		}

		glViewport(
			0,
			0,
			window.GetWidth(),
			window.GetHeight()
		);

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		// Draw Triangle - 3 | Draw Quad - 6
		// glDrawArrays(GL_TRIANGLES, 0, 6); // Cannot use with IBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		SDL_GL_SwapWindow(window.GetWindow().get());
	}

	SDL_Quit();
	std::cout << "Closing!" << std::endl;

	return 0;
}