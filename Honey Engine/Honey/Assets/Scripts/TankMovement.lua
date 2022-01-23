name = "Tank"
position = {x, y, z}
speed = 2

function TankMovement(posX, posZ, key, rotY)23

	position.x = posX
	position.z = posZ
	position.y = rotY
	
	if(key == "W")
	then
		position.x = position.x + speed
		position.y = 1.5708
	end
	if(key == "E")
	then
		position.x = position.x - speed
		position.y = 4.71239
	end
	if(key == "N")
	then
		position.z = position.z + speed
		position.y = 0
	end
	if(key == "S")
	then
		position.z = position.z - speed
		position.y = 3.14159
	end
	if(key == "SW")
	then
		position.z = position.z - speed
		position.x = position.x + speed
		position.y = 2.35619
	end
	if(key == "NE")
	then
		position.z = position.z + speed
		position.x = position.x - speed
		position.y = 5.49779
	end
	if(key == "NW")
	then
		position.z = position.z + speed
		position.x = position.x + speed
		position.y = 0.785398
	end
	if(key == "SE")
	then
		position.z = position.z - speed
		position.x = position.x - speed
		position.y = 3.92699
	end

	return position
end