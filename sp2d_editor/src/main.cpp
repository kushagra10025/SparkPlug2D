#define SDL_MAIN_HANDLED 1;
#include <Windowing/Window/Window.h>
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2D
{
private:
	int m_Width, m_Height;
	float m_Scale;

	glm::vec2 m_Position;
	glm::mat4 m_CameraMatrix, m_OrthoProjection;

	bool m_bNeedsUpdate;
public:

	Camera2D()
		:Camera2D(640, 480)
	{

	}

	Camera2D(int width, int height)
		: m_Width{ width }, m_Height{ height }, m_Scale{ 1.f },
		m_Position{ glm::vec2{0} }, m_CameraMatrix{ 1.f }, m_OrthoProjection{ 1.f }, m_bNeedsUpdate{ true }
	{
		// Init Ortho Projection
		m_OrthoProjection = glm::ortho(
			0.f,							// Left
			static_cast<float>(m_Width),	// Right
			static_cast<float>(m_Height),	// Top
			0.f,							// Bottom
			-1.f,							// Near
			1.f								// Far
		);
	}

	inline void SetScale(float scale) { m_Scale = scale; m_bNeedsUpdate = true; }

	inline glm::mat4 GetCameraMatrix() { return m_CameraMatrix; }

	void Update()
	{
		if (!m_bNeedsUpdate)
			return;

		// Translate
		glm::vec3 translate{ -m_Position.x, -m_Position.y, 0.f };
		m_CameraMatrix = glm::translate(m_OrthoProjection, translate);

		// Scale
		glm::vec3 scale{ m_Scale, m_Scale, 0.f };
		m_CameraMatrix *= glm::scale(glm::mat4(1.f), scale);

		m_bNeedsUpdate = false;
	}

};

struct UVs
{
	float u, v, width, height;
	UVs()
		: u{ 0.f }, v{ 0.f }, width{ 0.f }, height{ 0.f }
	{

	}
};

bool LoadTexture(const std::string& filepath, int& width, int& height, bool blended)
{
	int channels = 0;

	unsigned char* image = SOIL_load_image(
		filepath.c_str(),	// Filename
		&width,				// Image Width
		&height,			// Image Height
		&channels,			// Number of Channels
		SOIL_LOAD_AUTO		// Force Channels Count
	);

	if (!image)
	{
		std::cout << "SOIL Failed to Load Image [" << filepath << "] -- " << SOIL_last_result();
		return false;
	}

	GLint format = GL_RGBA;

	switch (channels)
	{
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (!blended)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	glTexImage2D(
		GL_TEXTURE_2D,			// Target
		0,						// Level of Detail
		format,					// Number of Color Components
		width,					// Image Width
		height,					// Image Height
		0,						// Border
		format,					// Format of Pixel Data
		GL_UNSIGNED_BYTE,		// Data type of Pixel Data
		image					// Data
	);

	// Delete Image Data from SOIL
	SOIL_free_image_data(image);

	return true;
}

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

	// Enable Alpha Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Temp Load a Texture
	// Create Texture ID, Gen and Bind it
	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	// Load texture
	int width{ 0 }, height{ 0 };
	//if (!LoadTexture("assets/textures/default_texture.png", width, height, false))
	if (!LoadTexture("assets/textures/pixel_platformer/Tilemap/tilemap_packed.png", width, height, false))
	{
		std::cout << "Failed to Load the Texture!\n";
		return -1;
	}

	// Temp UVs
	UVs uvs{};

	auto generateUVs = [&](float startX, float startY, float spriteWidth, float spriteHeight)
		{
			uvs.width = spriteWidth / width;
			uvs.height = spriteHeight / height;

			uvs.u = startX * uvs.width;
			uvs.v = startY * uvs.height;
		};

	generateUVs(4, 2, 18, 18);

	// Temp Vertex Data
	// Vertices for a Triangle
	//float vertices[] =
	//{
	//	0.0f, 0.5f, 0.0f,
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f
	//};

	// Vertices for a Quad
	//float vertices[] =
	//{
	//	-0.5f, 0.5f, 0.0f, 0.f, 1.f,		// TL
	//	0.5f, 0.5f, 0.0f, 1.f, 1.f,			// TR
	//	0.5f, -0.5f, 0.0f, 1.f, 0.f,		// BR
	//	-0.5f, -0.5f, 0.0f, 0.f, 0.f,		// BL
	//};

	// Swapped Vertices for Upside down image (quick fix)
	float vertices[] =
	{
		10.f, 28.f, 0.0f, uvs.u, (uvs.v + uvs.height),						// TL
		10.f, 10.f, 0.0f, uvs.u, uvs.v,										// TR
		28.f, 10.f, 0.0f, (uvs.u + uvs.width), uvs.v,						// BR
		28.f, 28.f, 0.0f, (uvs.u + uvs.width),(uvs.v + uvs.height),			// BL
	};

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	// Create Temp Camera
	Camera2D camera{};
	camera.SetScale(3.f);

	// Temp Vertex Source
	const char* vertexSource =
		"#version 460 core\n"
		"layout (location = 0) in vec3 aPosition;\n"
		"layout (location = 1) in vec2 aTexCoords;\n"
		"out vec2 fragUVs;\n"
		"uniform mat4 uProjection;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = uProjection * vec4(aPosition, 1.0);\n"
		"	fragUVs = aTexCoords;\n"
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
		"in vec2 fragUVs;\n"
		"out vec4 color;\n"
		"uniform sampler2D uTexture;\n"
		"void main()\n"
		"{\n"
		//"	color = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
		"	color = texture(uTexture, fragUVs);\n"
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
		5 * sizeof(float),						// Stride - Specifies the byte offset b/w consecutive attribs
		(void*)0								// Pointer - Offset of the First Component
	);

	glEnableVertexArrayAttrib(VAO, 0);

	// For UVs
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		5 * sizeof(float),
		reinterpret_cast<void*>(sizeof(float) * 3)
	);

	glEnableVertexArrayAttrib(VAO, 1);

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

		glClearColor(0.f, 1.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		auto projection = camera.GetCameraMatrix();

		GLuint location = glGetUniformLocation(shaderProgram, "uProjection");
		glUniformMatrix4fv(location, 1, GL_FALSE, &projection[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);

		// Draw Triangle - 3 | Draw Quad - 6
		// glDrawArrays(GL_TRIANGLES, 0, 6); // Cannot use with IBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		SDL_GL_SwapWindow(window.GetWindow().get());

		camera.Update();
	}

	SDL_Quit();
	std::cout << "Closing!" << std::endl;

	return 0;
}