#include "ScriptingSystem.h"
#include "../ECS/Components/ScriptComponent.h"
#include "../ECS/Components/TransformComponent.h"
#include "../ECS/Components/SpriteComponent.h"
#include "../ECS/Entity.h"
#include <SP2DLogging/Log.h>

SP2D::Core::Systems::ScriptingSystem::ScriptingSystem(ECS::Registry& registry)
	:m_Registry{ registry }, m_bMainLoaded{ false }
{

}

bool SP2D::Core::Systems::ScriptingSystem::LoadMainScript(sol::state& lua)
{
	try 
	{
		auto result = lua.safe_script_file("assets/scripts/main.lua");
	}
	catch (const sol::error& err)
	{
		SP2D_CORE_ERROR("Error Loading the Main Lua Script\n{0}", err.what());
		return false;
	}

	sol::table main_lua = lua["main"];
	sol::optional<sol::table> bUpdateExists = main_lua[1];
	if (bUpdateExists == sol::nullopt)
	{
		SP2D_CORE_ERROR("No Update Function in Main Lua");
		return false;
	}

	sol::table update_script = main_lua[1];
	sol::function update = update_script["update"];

	sol::optional<sol::table> bRenderExists = main_lua[2];
	if (bRenderExists == sol::nullopt)
	{
		SP2D_CORE_ERROR("No Render Function in Main Lua");
		return false;
	}

	sol::table render_script = main_lua[2];
	sol::function render = render_script["render"];

	ECS::Entity mainLuaScript{ m_Registry, "main_script", "" };
	mainLuaScript.AddComponent<ECS::ScriptComponent>(
		ECS::ScriptComponent{
			.update = update,
			.render = render
		}
	);

	m_bMainLoaded = true;
	return true;
}

void SP2D::Core::Systems::ScriptingSystem::Update()
{
	if (!m_bMainLoaded)
	{
		SP2D_CORE_ERROR("Main Lua not loaded!");
		return;
	}

	auto view = m_Registry.GetRegistry().view<ECS::ScriptComponent>();

	for (const auto& entity : view)
	{
		ECS::Entity ent{ m_Registry, entity };
		if(ent.GetName() != "main_script")
			continue;

		auto& script = ent.GetComponent<ECS::ScriptComponent>();
		auto error = script.update(entity);
		if (!error.valid())
		{
			sol::error err = error;
			SP2D_CORE_ERROR("Error running main-update\n{0}", err.what());
		}
	}
}

void SP2D::Core::Systems::ScriptingSystem::Render()
{
	if (!m_bMainLoaded)
	{
		SP2D_CORE_ERROR("Main Lua not loaded!");
		return;
	}

	auto view = m_Registry.GetRegistry().view<ECS::ScriptComponent>();

	for (const auto& entity : view)
	{
		ECS::Entity ent{ m_Registry, entity };
		if (ent.GetName() != "main_script")
			continue;

		auto& script = ent.GetComponent<ECS::ScriptComponent>();
		auto error = script.render(entity);
		if (!error.valid())
		{
			sol::error err = error;
			SP2D_CORE_ERROR("Error running main-render\n{0}", err.what());
		}
	}
}

void SP2D::Core::Systems::ScriptingSystem::RegisterLuaBindings(sol::state& lua, SP2D::Core::ECS::Registry& registry)
{
	SP2D::Core::ECS::Entity::CreateLuaEntityBind(lua, registry);
	SP2D::Core::ECS::TransformComponent::CreateLuaTransformBind(lua);
	SP2D::Core::ECS::SpriteComponent::CreateLuaSpriteBind(lua, registry);

	SP2D::Core::ECS::Entity::RegisterMetaComponent<SP2D::Core::ECS::TransformComponent>();
	SP2D::Core::ECS::Entity::RegisterMetaComponent<SP2D::Core::ECS::SpriteComponent>();
}

