
name = "GameObject 1"
position = {x, z}
speed = 1

function Update(posX, posZ, dt)
	position.x = posX
	position.z = posZ

	position.x = position.x + (speed * dt)
	position.z = position.z + (speed * dt)

	return position
end

function Movement(posX, posZ, key)
	--print("[LUA] SetPosX is being called\n")
	test(name)
	
	position.x = posX
	position.z = posZ

	if key == "I" then
	
		position.x = position.x + speed
	end
	if key == "K" then
	
		position.x = position.x - speed
	end
	if key == "J" then
	
		position.z = position.z + speed
	end
	if key == "L" then
	
		position.z = position.z - speed
	end

	-- set position ?
	return position
end