#include "Application.h"

#include <SDL.h>
#include <iostream>
#include <SOIL2/SOIL2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <entt/entt.hpp>

#include <SP2DRendering/Essentials/ShaderLoader.h>
#include <SP2DRendering/Essentials/TextureLoader.h>
#include <SP2DRendering/Essentials/Vertex.h>
#include <SP2DRendering/Core/Camera2D.h>
#include <SP2DLogging/Log.h>
#include <SP2DCore/ECS/Entity.h>
#include <SP2DCore/ECS/Components/SpriteComponent.h>
#include <SP2DCore/ECS/Components/TransformComponent.h>
#include <SP2DCore/ECS/Components/IdentificationComponent.h>
#include <SP2DCore/Systems/ScriptingSystem.h>
#include <SP2DCore/Systems/RenderSystem.h>
#include <SP2DCore/Resources/AssetManager.h>

bool SP2D::Editor::Application::Initialize()
{
	SP2D::Logging::Log::Init();
	if (SP2D_LOG_INITIALIZED())
	{
		SP2D_CORE_INFO("Logging has Initialized!");
		SP2D_INFO("Logging has Initialized!");
	}
	else
	{
		std::cout << "Logging initialization failed!" << std::endl;

		return false;
	}

	// Init SDL
	SDL_SetMainReady();

	//if (SDL_Init(SDL_INIT_EVERYTHING) != 0) // This can be used instead of individually adding the INIT Flags.
		// Removed the SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER flags as they were adding Delay in INIT
		// The Delay is sometimes sorted out by restarting the computer.
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_HAPTIC) != 0)
	{
		std::string error = SDL_GetError();
		SP2D_FATAL("SDL Init Failed!\n{0}", error);

		return false;
	}

	// Setup OpenGL
	if (SDL_GL_LoadLibrary(NULL) != 0)
	{
		std::string error = SDL_GetError();
		SP2D_FATAL("SDL OpenGL Load Failed!\n{0}", error);

		return false;
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
	m_pWindow = std::make_unique<SP2D::Windowing::Window>(
		"Demo Window", 640, 480, 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		true, (SDL_WINDOW_OPENGL)
	);

	if (!m_pWindow->GetWindow())
	{
		SP2D_FATAL("SDL Window Creation Failed!");

		return false;
	}

	// Create the OpenGL Context
	m_pWindow->SetGLContext(SDL_GL_CreateContext(m_pWindow->GetWindow().get()));

	if (!m_pWindow->GetGLContext())
	{
		std::string error = SDL_GetError();
		SP2D_FATAL("SDL Failed to Create OpenGL Context!\n{0}", error);

		return false;
	}

	SDL_GL_MakeCurrent(m_pWindow->GetWindow().get(), m_pWindow->GetGLContext());
	SDL_GL_SetSwapInterval(1);

	// Initialize Glad
	if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
	{
		SP2D_FATAL("Failed to Initialize GLAD!");
		return false;
	}

	// Enable Alpha Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto assetManager = std::make_shared<SP2D::Core::Resources::AssetManager>();
	if (!assetManager)
	{
		SP2D_ERROR("Failed to create the Asset Manager!");
		return false;
	}

	if (!assetManager->AddTexture("sample_packed_tilemap", "assets/textures/pixel_platformer/Tilemap/tilemap_packed.png", true))
	{
		SP2D_ERROR("Failed to Add the Texture to Asset Manager!");
		return false;
	}

	// Temp Texture
	auto texture = assetManager->GetTexture("sample_packed_tilemap");

	SP2D_INFO("Loaded Texture : [Width = {0} ; Height = {1}]", texture.GetWidth(), texture.GetHeight());

	// Temp Entity Stuff
	m_pRegistry = std::make_unique<SP2D::Core::ECS::Registry>();
	if (!m_pRegistry)
	{
		SP2D_ERROR("Failed to Create an ECS Registry!");
		return false;
	}

	SP2D::Core::ECS::Entity entity1{ *m_pRegistry, "Entity1", "TestGroup" };

	auto& transform = entity1.AddComponent<SP2D::Core::ECS::TransformComponent>(
		SP2D::Core::ECS::TransformComponent{
			.position = glm::vec2{10.f, 10.f},
			.scale = glm::vec2{5.f, 5.f},
			.rotation = 0.f
		}
	);

	auto& sprite = entity1.AddComponent<SP2D::Core::ECS::SpriteComponent>(
		SP2D::Core::ECS::SpriteComponent{
			.width = 18.f,
			.height = 18.f,
			.color = SP2D::Rendering::Color{.r = 255, .g = 255, .b = 255, .a = 255},
			.start_x = 4,
			.start_y = 2,
			.layer = 0,
			.texture_name="sample_packed_tilemap"
		}
	);

	sprite.generate_uvs(texture.GetWidth(), texture.GetHeight());

	// Test Component
	auto& id = entity1.GetComponent<SP2D::Core::ECS::IdentificationComponent>();
	SP2D_INFO("Name : {0}, Group : {1}, ID : {2}", id.name, id.group, id.entity_id);

	// Create the Lua State
	auto lua = std::make_shared<sol::state>();
	if (!lua)
	{
		SP2D_ERROR("Failed to create Lua State!");
		return false;
	}

	lua->open_libraries(
		sol::lib::base, 
		sol::lib::math, 
		sol::lib::os, 
		sol::lib::table, 
		sol::lib::io, 
		sol::lib::string
	);

	if (!m_pRegistry->AddToContext<std::shared_ptr<sol::state>>(lua))
	{
		SP2D_ERROR("Failed to add the sol::state to Registry Context!");
		return false;
	}

	// Creating Scripting System
	auto scriptSystem = std::make_shared<SP2D::Core::Systems::ScriptingSystem>(*m_pRegistry);
	if (!scriptSystem)
	{
		SP2D_ERROR("Failed to create Scripting System!");
		return false;
	}

	if (!scriptSystem->LoadMainScript(*lua))
	{
		SP2D_ERROR("Failed to load main-lua script!");
		return false;
	}

	if (!m_pRegistry->AddToContext<std::shared_ptr<SP2D::Core::Systems::ScriptingSystem>>(scriptSystem))
	{
		SP2D_ERROR("Failed to add the ScriptSystem to Registry Context!");
		return false;
	}

	// Creating Render System
	auto renderSystem = std::make_shared<SP2D::Core::Systems::RenderSystem>(*m_pRegistry);
	if (!renderSystem)
	{
		SP2D_ERROR("Failed to create Rendering System!");
		return false;
	}
	if (!m_pRegistry->AddToContext<std::shared_ptr<SP2D::Core::Systems::RenderSystem>>(renderSystem))
	{
		SP2D_ERROR("Failed to add the RenderSystem to Registry Context!");
		return false;
	}

	// Create Temp Camera
	auto camera = std::make_shared<SP2D::Rendering::Camera2D>();
	//camera->SetScale(3.f);

	if (!m_pRegistry->AddToContext(std::shared_ptr<SP2D::Core::Resources::AssetManager>(assetManager)))
	{
		SP2D_ERROR("FAILED to add the Asset Manager to Registry Context");
		return false;
	}

	if (!m_pRegistry->AddToContext(std::shared_ptr<SP2D::Rendering::Camera2D>(camera)))
	{
		SP2D_ERROR("FAILED to add the Camera2D to Registry Context");
		return false;
	}

	if (!LoadShaders())
	{
		SP2D_ERROR("Failed to load the Shaders!");
		return false;
	}

	return true;
}

bool SP2D::Editor::Application::LoadShaders()
{
	auto& assetManager = m_pRegistry->GetContext<std::shared_ptr<SP2D::Core::Resources::AssetManager>>();

	if (!assetManager)
	{
		SP2D_ERROR("Failed to get the AssetManager from Registry Context!");
		return false;
	}

	// Add and Create First Shader
	if (!assetManager->AddShader("basicShader", "assets/shaders/basicShader.vert", "assets/shaders/basicShader.frag"))
	{
		SP2D_ERROR("Failed to add the Shader to AssetManager!");
		return false;
	}

	return true;
}

void SP2D::Editor::Application::ProcessEvents()
{
	// Process Events
	while (SDL_PollEvent(&m_Event))
	{
		switch (m_Event.type)
		{
		case SDL_QUIT:
			m_bIsRunning = false;
			break;
		case SDL_KEYDOWN:
			if (m_Event.key.keysym.sym = SDLK_ESCAPE)
				m_bIsRunning = false;
			break;
		default:
			break;
		}
	}
}

void SP2D::Editor::Application::Update()
{
	auto& camera = m_pRegistry->GetContext<std::shared_ptr<SP2D::Rendering::Camera2D>>();

	if (!camera)
	{
		SP2D_ERROR("Failed to get the Camera from Registry Context!");
		return;
	}

	camera->Update();

	auto& scriptSystem = m_pRegistry->GetContext<std::shared_ptr<SP2D::Core::Systems::ScriptingSystem>>();

	if (!scriptSystem)
	{
		SP2D_ERROR("Failed to get the ScriptSystem from Registry Context!");
		return;
	}

	scriptSystem->Update();
}

void SP2D::Editor::Application::Render()
{
	auto& renderSystem = m_pRegistry->GetContext<std::shared_ptr<SP2D::Core::Systems::RenderSystem>>();
	if (!renderSystem)
	{
		SP2D_ERROR("Failed to get the RenderSystem from Registry Context!");
		return;
	}

	glViewport(
		0,
		0,
		m_pWindow->GetWidth(),
		m_pWindow->GetHeight()
	);

	glClearColor(0.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	auto& scriptSystem = m_pRegistry->GetContext<std::shared_ptr<SP2D::Core::Systems::ScriptingSystem>>();

	if (!scriptSystem)
	{
		SP2D_ERROR("Failed to get the ScriptSystem from Registry Context!");
		return;
	}

	scriptSystem->Render();
	renderSystem->Update();

	SDL_GL_SwapWindow(m_pWindow->GetWindow().get());
}

void SP2D::Editor::Application::Cleanup()
{
	SDL_Quit();
	SP2D_INFO("Closing!");
}

SP2D::Editor::Application::Application()
	: m_pWindow{ nullptr }, m_pRegistry{ nullptr }, m_Event{}, m_bIsRunning{ true }
{

}

SP2D::Editor::Application& SP2D::Editor::Application::GetInstance()
{
	static SP2D::Editor::Application app{};
	return app;
}

void SP2D::Editor::Application::Run()
{
	if (!Initialize())
	{
		SP2D_FATAL("Initialization Failed!");
		return;
	}

	// Window Loop
	while (m_bIsRunning)
	{
		ProcessEvents();
		Update();
		Render();
	}

	Cleanup();
}

