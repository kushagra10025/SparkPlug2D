#include "Log.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> SP2D::Logging::Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> SP2D::Logging::Log::s_ClientLogger;
bool SP2D::Logging::Log::m_bInitialized = false;

void SP2D::Logging::Log::Init()
{
	if (m_bInitialized)
		return;

	spdlog::set_pattern("%^[%T][%l][%n] | %v%$");

	s_CoreLogger = spdlog::stdout_color_mt("SP2D");
	s_CoreLogger->set_level(spdlog::level::trace);

	s_ClientLogger = spdlog::stdout_color_mt("APP");
	s_ClientLogger->set_level(spdlog::level::trace);

	if (s_CoreLogger == nullptr || s_ClientLogger == nullptr)
	{
		std::cout << "Loggers failed to initialize\n";
		m_bInitialized = false;
		return;
	}	

	m_bInitialized = true;
}
