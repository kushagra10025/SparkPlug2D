-- Main Lua Script!

gEntity = Entity("TestEntity", "DefaultGroup")

local transform = gEntity:add_component(
	-- Transform(100, 100, 10, 10, 0)
	Transform(vec2(100, 100), vec2(10, 10), 0)
)

local sprite = gEntity:add_component(
	Sprite("sample_packed_tilemap", 18.0, 18.0, 4, 2, 0)
)

-- Test for entities and view
gEntity2 = Entity("TestEntity2", "DefaultGroup")
gEntity2:add_component(Transform(200, 100, 10, 10, 0))
local sprite2 = gEntity2:add_component(Sprite("sample_packed_characters", 24.0, 24.0, 6, 2, 0))
sprite2:generate_uvs()
local anim2 = gEntity2:add_component(Animation(3, 2, 0, false))

local view = Registry.get_entities(Transform)

print("Before Excluding Transform Comp")

view:for_each(
	function(entity)
		print(entity:name())
	end
)
print("After Excluding Transform Comp")

view:exclude(Transform)
view:for_each(
	function(entity)
		print(entity:name())
	end
)

-- Test For has_component, get_component
-- remove_component is giving assert

local hasSprite = gEntity:has_component(Sprite)

if has_component == false then
	print("gEntity has Sprite: false")
else
	print("gEntity has Sprite: true")
	--gEntity:remove_component(Sprite)
end

local gotSprite = gEntity:get_component(Sprite)

if gotSprite == nil then
	print("gEntity got Sprite Failed")
else
	print("gEntity got Sprite Success")
	print("Sprite texture_name : " ..gotSprite.texture_name)
end

-- Test GLM Function binds

vecA = vec2(10, 10)
vecB = vec2(15, 15)

vecA3 = vec3(1, 2, 3)
vecB3 = vec3(4, 5, 6)

vecDist = vector_distance(vecA, vecB)
vecANormalized = vector_normalize(vecA)
vecCross = vector_cross(vecA3, vecB3)

print("vecDist = " .. tostring(vecDist))
print("vecANormalzied = x : " .. tostring(vecANormalized.x) ..  " y : " .. tostring(vecANormalized.y))
print("vecCross = x : " .. tostring(vecCross.x) ..  " y : " .. tostring(vecCross.y) .. " z : " .. tostring(vecCross.z))


sprite:generate_uvs()

local rotation = 0.0
local x_pos = 10.0
local scale = 1.0
local move_right = true
local value = 0


main = {
	[1] = {
		update = function()
			if rotation >= 360 then
				rotation = 0
			end 

			if move_right and x_pos < 300 then 
				x_pos = x_pos + 3 
				value = value + 0.01
			elseif move_right and x_pos >= 300 then 
				move_right = false
			end 

			if not move_right and x_pos > 10 then 
				x_pos = x_pos - 3
				value = value - 0.01 
			elseif not move_right  and x_pos <= 10 then 
				move_right = true 
			end 

			transform.position.x = x_pos
			transform.rotation = rotation 
			--transform:set_pos(pos_x, pos_y)

			if move_right then 
				rotation = rotation + 9
			else
				rotation = rotation - 9
			end 

			scale = math.sin(value) * 10 

			if scale >= 10 then 
				scale = 10 
			elseif scale <= 1 then 
				scale = 1 
			end 

			if value >= 1 then 
				value = 1 
			elseif value <= 0 then
				value = 0
			end 

			transform.scale = vec2(scale, scale)
			--transform:set_scale(scale, scale)

			-- Test Keyboard Input
			if Keyboard.just_pressed(KEY_W) then
				print("Key W was just pressed")
			elseif Keyboard.just_pressed(KEY_S) then
				print("Key S was just pressed")
			elseif Keyboard.just_pressed(KEY_A) then
				print("Key A was just pressed")
			elseif Keyboard.just_pressed(KEY_D) then
				print("Key D was just pressed")
			end

			-- Test Mouse Input
			if Mouse.just_pressed(LEFT_MOUSE_BTN) then
				print("Mouse LEFT Button Pressed")
			elseif Mouse.just_pressed(MIDDLE_MOUSE_BTN) then
				print("Mouse MIDDLE Button Pressed") 
			elseif Mouse.just_pressed(RIGHT_MOUSE_BTN) then
				print("Mouse RIGHT Button Pressed") 
			end

			local mouse_x, mouse_y = Mouse.screen_position()
			-- print("Mouse pos[" ..mouse_x ..", " ..mouse_y .."]")
			local wheel_y = Mouse.wheel_y()
			-- print("Wheel Y: " ..wheel_y)

		end
	},
	[2] = {
		render = function()
			
		end
	}
}