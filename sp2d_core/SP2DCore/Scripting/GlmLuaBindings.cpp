#include "GlmLuaBindings.h"

#include <glm/glm.hpp>
#include <cmath>
#include <algorithm>

// vec2 binding
void CreateVec2Bind(sol::state& lua)
{
	auto vec2_multiply_overloads = sol::overload(
		[](const glm::vec2& v1, const glm::vec2& v2) { return v1 * v2; },
		[](const glm::vec2& v1, float value) { return v1 * value; },
		[](float value, const glm::vec2& v1) { return v1 * value; }
	);

	auto vec2_divide_overloads = sol::overload(
		[](const glm::vec2& v1, const glm::vec2& v2) { return v1 / v2; },
		[](const glm::vec2& v1, float value) { return v1 / value; },
		[](float value, const glm::vec2& v1) { return v1 / value; }
	);

	auto vec2_add_overloads = sol::overload(
		[](const glm::vec2& v1, const glm::vec2& v2) { return v1 + v2; },
		[](const glm::vec2& v1, float value) { return v1 + value; },
		[](float value, const glm::vec2& v1) { return v1 + value; }
	);

	auto vec2_subtract_overloads = sol::overload(
		[](const glm::vec2& v1, const glm::vec2& v2) { return v1 - v2; },
		[](const glm::vec2& v1, float value) { return v1 - value; },
		[](float value, const glm::vec2& v1) { return v1 - value; }
	);

	lua.new_usertype<glm::vec2>(
		"vec2",
		sol::call_constructor,
		sol::constructors<glm::vec2(float), glm::vec2(float, float)>(),
		"x", &glm::vec2::x,
		"y", &glm::vec2::y,
		sol::meta_function::multiplication, vec2_multiply_overloads,
		sol::meta_function::division, vec2_divide_overloads,
		sol::meta_function::addition, vec2_add_overloads,
		sol::meta_function::subtraction, vec2_subtract_overloads
	);
}

// vec3 binding
void CreateVec3Bind(sol::state& lua)
{
	auto vec3_multiply_overloads = sol::overload(
		[](const glm::vec3& v1, const glm::vec3& v2) { return v1 * v2; },
		[](const glm::vec3& v1, float value) { return v1 * value; },
		[](float value, const glm::vec3& v1) { return v1 * value; }
	);

	auto vec3_divide_overloads = sol::overload(
		[](const glm::vec3& v1, const glm::vec3& v2) { return v1 / v2; },
		[](const glm::vec3& v1, float value) { return v1 / value; },
		[](float value, const glm::vec3& v1) { return v1 / value; }
	);

	auto vec3_add_overloads = sol::overload(
		[](const glm::vec3& v1, const glm::vec3& v2) { return v1 + v2; },
		[](const glm::vec3& v1, float value) { return v1 + value; },
		[](float value, const glm::vec3& v1) { return v1 + value; }
	);

	auto vec3_subtract_overloads = sol::overload(
		[](const glm::vec3& v1, const glm::vec3& v2) { return v1 - v2; },
		[](const glm::vec3& v1, float value) { return v1 - value; },
		[](float value, const glm::vec3& v1) { return v1 - value; }
	);

	lua.new_usertype<glm::vec3>(
		"vec3",
		sol::call_constructor,
		sol::constructors<glm::vec3(float), glm::vec3(float, float, float)>(),
		"x", &glm::vec3::x,
		"y", &glm::vec3::y,
		"z", &glm::vec3::z,
		sol::meta_function::multiplication, vec3_multiply_overloads,
		sol::meta_function::division, vec3_divide_overloads,
		sol::meta_function::addition, vec3_add_overloads,
		sol::meta_function::subtraction, vec3_subtract_overloads
	);
}

// vec4 binding
void CreateVec4Bind(sol::state& lua)
{
	auto vec4_multiply_overloads = sol::overload(
		[](const glm::vec4& v1, const glm::vec4& v2) { return v1 * v2; },
		[](const glm::vec4& v1, float value) { return v1 * value; },
		[](float value, const glm::vec4& v1) { return v1 * value; }
	);

	auto vec4_divide_overloads = sol::overload(
		[](const glm::vec4& v1, const glm::vec4& v2) { return v1 / v2; },
		[](const glm::vec4& v1, float value) { return v1 / value; },
		[](float value, const glm::vec4& v1) { return v1 / value; }
	);

	auto vec4_add_overloads = sol::overload(
		[](const glm::vec4& v1, const glm::vec4& v2) { return v1 + v2; },
		[](const glm::vec4& v1, float value) { return v1 + value; },
		[](float value, const glm::vec4& v1) { return v1 + value; }
	);

	auto vec4_subtract_overloads = sol::overload(
		[](const glm::vec4& v1, const glm::vec4& v2) { return v1 - v2; },
		[](const glm::vec4& v1, float value) { return v1 - value; },
		[](float value, const glm::vec4& v1) { return v1 - value; }
	);

	lua.new_usertype<glm::vec4>(
		"vec4",
		sol::call_constructor,
		sol::constructors<glm::vec4(float), glm::vec4(float, float, float, float)>(),
		"x", &glm::vec4::x,
		"y", &glm::vec4::y,
		"z", &glm::vec4::z,
		"w", &glm::vec4::w,
		sol::meta_function::multiplication, vec4_multiply_overloads,
		sol::meta_function::division, vec4_divide_overloads,
		sol::meta_function::addition, vec4_add_overloads,
		sol::meta_function::subtraction, vec4_subtract_overloads
	);
}

void MathHelperFunctions(sol::state& lua)
{
	// TODO : Add more functions as needed
	// GLM Functions Reference - https://glm.g-truc.net/0.9.9/api/modules.html
	// TODO : Trigonometric Functions - https://glm.g-truc.net/0.9.9/api/a00373.html
	// TODO : Add Generation Macros for the Function

	// Distance between two vectors -> float
	lua.set_function("vector_distance", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::distance(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::distance(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::distance(a, b); }
	));

	// Normalized Vector -> Vector
	lua.set_function("vector_normalize", sol::overload(
		[](glm::vec2& a) { return glm::normalize(a); },
		[](glm::vec3& a) { return glm::normalize(a); },
		[](glm::vec4& a) { return glm::normalize(a); }
	));

	// cross -> Vector3
	lua.set_function("vector_cross", [](glm::vec3& a, glm::vec3& b) { return glm::cross(a, b); });

	// dot -> float
	lua.set_function("vector_dot", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::dot(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::dot(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::dot(a, b); }
	));

	// length -> float
	lua.set_function("vector_length", sol::overload(
		[](glm::vec2& a) { return glm::length(a); },
		[](glm::vec3& a) { return glm::length(a); },
		[](glm::vec4& a) { return glm::length(a); }
	));

	// reflect -> vector
	lua.set_function("vector_reflect", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::reflect(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::reflect(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::reflect(a, b); }
	));

	// Lerped Value -> float
	lua.set_function("lerp", [](float a, float b, float t) { return std::lerp(a, b, t); });

	// Clamped Value(Datatype) -> Datatype
	lua.set_function("clamp", sol::overload(
		[](float value, float min, float max) { return std::clamp(value, min, max); },
		[](double value, double min, double max) { return std::clamp(value, min, max); },
		[](int value, int min, int max) { return std::clamp(value, min, max); }
	));

	// Component wise Vector Comparision -> bool
	// equal
	lua.set_function("vector_equal", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::equal(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::equal(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::equal(a, b); }
	));

	// notEqual
	lua.set_function("vector_notEqual", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::notEqual(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::notEqual(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::notEqual(a, b); }
	));

	// greaterThan
	lua.set_function("vector_greaterThan", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::greaterThan(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::greaterThan(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::greaterThan(a, b); }
	));

	// greaterThanEqual
	lua.set_function("vector_greaterThanEqual", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::greaterThanEqual(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::greaterThanEqual(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::greaterThanEqual(a, b); }
	));

	// lessThan
	lua.set_function("vector_lessThan", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::lessThan(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::lessThan(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::lessThan(a, b); }
	));

	// lessThanEqual
	lua.set_function("vector_lessThanEqual", sol::overload(
		[](glm::vec2& a, glm::vec2& b) { return glm::lessThanEqual(a, b); },
		[](glm::vec3& a, glm::vec3& b) { return glm::lessThanEqual(a, b); },
		[](glm::vec4& a, glm::vec4& b) { return glm::lessThanEqual(a, b); }
	));
}

void SP2D::Core::Scripting::GLMBindings::CreateLuaGLMBindings(sol::state& lua)
{
	CreateVec2Bind(lua);
	CreateVec3Bind(lua);
	CreateVec4Bind(lua);

	MathHelperFunctions(lua);
}
