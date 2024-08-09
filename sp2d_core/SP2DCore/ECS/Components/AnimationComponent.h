#pragma once

#include <sol/sol.hpp>
#include <entt/entt.hpp>

namespace SP2D::Core::ECS
{
	struct AnimationComponent
	{
		int numFrames{ 1 }, frameRate{ 1 }, frameOffset{ 1 }, currentFrame{ 0 };
		bool bVertical{ false };
		
		static void CreateLuaAnimationBind(sol::state& lua)
		{
			lua.new_usertype<AnimationComponent>(
				"Animation",
				"type_id", &entt::type_hash<AnimationComponent>::value,
				sol::call_constructor,
				sol::factories(
					[](int numFrames, int frameRate, int frameOffset, bool bVertical) {
						return AnimationComponent{
							.numFrames = numFrames,
							.frameRate = frameRate,
							.frameOffset = frameOffset,
							.currentFrame = 0,
							.bVertical = bVertical
						};
					}
				),
				"num_frames", &AnimationComponent::numFrames,
				"frame_rate", &AnimationComponent::frameRate,
				"frame_offset", &AnimationComponent::frameOffset,
				"current_frame", &AnimationComponent::currentFrame,
				"bVertical", &AnimationComponent::bVertical
			);
		}
	};
}
