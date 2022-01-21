name = "GameObject 1"
position = {x, z}
speed = 0.5

function Movement(posX, posZ, key)
	--print("[LUA] SetPosX is being called\n")
	test(name)
	
	position.x = posX
	position.z = posZ

	if(key == "A")
	then
		position.x = position.x + speed
	elseif(key == "D")
	then
		position.x = position.x - speed
	elseif(key == "W")
	then
		position.z = position.z + speed
	elseif(key == "S")
	then
		position.z = position.z - speed
	end

	return position
end

