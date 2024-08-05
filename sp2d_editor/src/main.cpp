#define SDL_MAIN_HANDLED 1;
#include <SP2DWindowing/Window/Window.h>
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SP2DRendering/Essentials/ShaderLoader.h>
#include <SP2DRendering/Essentials/TextureLoader.h>
#include <SP2DRendering/Essentials/Vertex.h>
#include <SP2DRendering/Core/Camera2D.h>
#include <SP2DLogging/Log.h>

struct UVs
{
	float u, v, width, height;
	UVs()
		: u{ 0.f }, v{ 0.f }, width{ 0.f }, height{ 0.f }
	{

	}
};

int main(int argc, char** argv)
{
	bool running = true;

	SP2D::Logging::Log::Init();
	if (SP2D_LOG_INITIALIZED())
	{
		SP2D_CORE_INFO("Logging has Initialized!");
		SP2D_INFO("Logging has Initialized!");
	}
	else
	{
		std::cout << "Logging initialization failed!" << std::endl;
		return -1;
	}


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
	
	// Temp Texture
	auto texture = SP2D::Rendering::TextureLoader::Create(SP2D::Rendering::Texture::TextureType::PIXEL, "assets/textures/pixel_platformer/Tilemap/tilemap_packed.png");
	if (!texture)
	{
		SP2D_ERROR("Failed to Create Texture!");
	}

	// Temp UVs
	UVs uVs{};
	SP2D_INFO("Loaded Texture : [Width = {0} ; Height = {1}]", texture->GetWidth(), texture->GetHeight());

	auto generateUVs = [&](float startX, float startY, float spriteWidth, float spriteHeight)
		{
			uVs.width = spriteWidth / texture->GetWidth();
			uVs.height = spriteHeight / texture->GetHeight();

			uVs.u = startX * uVs.width;
			uVs.v = startY * uVs.height;
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
	//float vertices[] =
	//{
	//	10.f, 28.f, 0.0f, uvs.u, (uvs.v + uvs.height),						// TL
	//	10.f, 10.f, 0.0f, uvs.u, uvs.v,										// TR
	//	28.f, 10.f, 0.0f, (uvs.u + uvs.width), uvs.v,						// BR
	//	28.f, 28.f, 0.0f, (uvs.u + uvs.width),(uvs.v + uvs.height),			// BL
	//};

	std::vector<SP2D::Rendering::Vertex> vertices{};
	SP2D::Rendering::Vertex vTL{}, vTR{}, vBL{}, vBR{};

	vTL.position = glm::vec2{ 10.f, 28.f };
	vTL.uvs = glm::vec2{ uVs.u, (uVs.v + uVs.height) };

	vTR.position = glm::vec2{ 10.f, 10.f };
	vTR.uvs = glm::vec2{ uVs.u, uVs.v };

	vBR.position = glm::vec2{ 28.f, 28.f };
	vBR.uvs = glm::vec2{ (uVs.u + uVs.width),(uVs.v + uVs.height) };

	vBL.position = glm::vec2{ 28.f, 10.f };
	vBL.uvs = glm::vec2{ (uVs.u + uVs.width), uVs.v };

	vertices.push_back(vTL);
	vertices.push_back(vTR);
	vertices.push_back(vBL);
	vertices.push_back(vBR);

	GLuint indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	// Create Temp Camera
	SP2D::Rendering::Camera2D camera{};
	camera.SetScale(3.f);

	// Create First Shader
	auto shader = SP2D::Rendering::ShaderLoader::Create("assets/shaders/basicShader.vert", "assets/shaders/basicShader.frag");

	if (!shader)
	{
		std::cout << "Failed to create the Shader!" << std::endl;
		return -1;
	}

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
		GL_ARRAY_BUFFER,									// Target Buffer Type
		vertices.size() * sizeof(SP2D::Rendering::Vertex),	// The size in Bytes of the Buffer Object's New Data Store
		vertices.data(),									// Pointer to data that will be copied into Data Store
		GL_STATIC_DRAW										// Expected usage pattern of the data store
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,				// Target Buffer Type
		6 * sizeof(GLuint),						// The size in Bytes of the Buffer Object's New Data Store
		indices,								// Pointer to data that will be copied into Data Store
		GL_STATIC_DRAW							// Expected usage pattern of the data store
	);

	glVertexAttribPointer(
		0,													// Attrib 0 - The layout position in the vertex shader
		2,													// Size - Number of components per vertex
		GL_FLOAT,											// Type - data type of above component
		GL_FALSE,											// Normalized - Specifies if fixed-point data values should be normalized
		sizeof(SP2D::Rendering::Vertex),					// Stride - Specifies the byte offset b/w consecutive attribs
		(void*)offsetof(SP2D::Rendering::Vertex, position)	// Pointer - Offset of the First Component
	);

	glEnableVertexArrayAttrib(VAO, 0);

	// For UVs
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(SP2D::Rendering::Vertex),
		(void*)offsetof(SP2D::Rendering::Vertex, uvs)
	);

	glEnableVertexArrayAttrib(VAO, 1);

	// For Color
	glVertexAttribPointer(
		2,
		4,
		GL_UNSIGNED_BYTE,
		GL_TRUE,
		sizeof(SP2D::Rendering::Vertex),
		(void*)offsetof(SP2D::Rendering::Vertex, color)
	);

	glEnableVertexArrayAttrib(VAO, 2);

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
		shader->Enable();
		glBindVertexArray(VAO);

		auto projection = camera.GetCameraMatrix();

		shader->SetUniformMat4("uProjection", projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetID());

		// Draw Triangle - 3 | Draw Quad - 6
		// glDrawArrays(GL_TRIANGLES, 0, 6); // Cannot use with IBO
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		SDL_GL_SwapWindow(window.GetWindow().get());

		camera.Update();
		shader->Disable();
	}

	SDL_Quit();
	SP2D_CORE_INFO("Closing!");

	return 0;
}