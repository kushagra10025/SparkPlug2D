#pragma once

#include <spdlog/spdlog.h>

namespace SP2D::Logging
{
	class Log
	{
	private:
		
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

		static bool m_bInitialized;

	public:
		Log() = delete;
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		inline static bool GetLogInitialized() { return m_bInitialized; }
		
	};
}

#define SP2D_LOG_INITIALIZED()	::SP2D::Logging::Log::GetLogInitialized()

#if defined(SP2D_SOURCE_DETAILS_LOG) && (SP2D_SOURCE_DETAILS_LOG==1)
	// Core Logger Macros
	#define SP2D_CORE_TRACE(...)	::SP2D::Logging::Log::GetCoreLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::trace, __VA_ARGS__)
	#define SP2D_CORE_INFO(...)		::SP2D::Logging::Log::GetCoreLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::info, __VA_ARGS__)
	#define SP2D_CORE_WARN(...)		::SP2D::Logging::Log::GetCoreLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::warn, __VA_ARGS__)
	#define SP2D_CORE_ERROR(...)	::SP2D::Logging::Log::GetCoreLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::err, __VA_ARGS__)
	#define SP2D_CORE_FATAL(...)	::SP2D::Logging::Log::GetCoreLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::critical, __VA_ARGS__)

	// Client Logger Macros
	#define SP2D_TRACE(...)			::SP2D::Logging::Log::GetClientLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::trace, __VA_ARGS__)
	#define SP2D_INFO(...)			::SP2D::Logging::Log::GetClientLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::info, __VA_ARGS__)
	#define SP2D_WARN(...)			::SP2D::Logging::Log::GetClientLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::warn, __VA_ARGS__)
	#define SP2D_ERROR(...)			::SP2D::Logging::Log::GetClientLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::err, __VA_ARGS__)
	#define SP2D_FATAL(...)			::SP2D::Logging::Log::GetClientLogger()->log(spdlog::source_loc{ __FILE__, __LINE__, SPDLOG_FUNCTION }, spdlog::level::critical, __VA_ARGS__)
#else
	// Core Logger Macros
	#define SP2D_CORE_TRACE(...)	::SP2D::Logging::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define SP2D_CORE_INFO(...)		::SP2D::Logging::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define SP2D_CORE_WARN(...)		::SP2D::Logging::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define SP2D_CORE_ERROR(...)	::SP2D::Logging::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define SP2D_CORE_FATAL(...)	::SP2D::Logging::Log::GetCoreLogger()->critical(__VA_ARGS__

	// Client Logger Macros
	#define SP2D_TRACE(...)			::SP2D::Logging::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define SP2D_INFO(...)			::SP2D::Logging::Log::GetClientLogger()->info(__VA_ARGS__)
	#define SP2D_WARN(...)			::SP2D::Logging::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define SP2D_ERROR(...)			::SP2D::Logging::Log::GetClientLogger()->error(__VA_ARGS__)
	#define SP2D_FATAL(...)			::SP2D::Logging::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif