name = "GameObject 3"
position = {x, y, z}
speed = 0.01

function BulletMovement(posX, posY, posZ, dt)

	--print("[LUA] SetPosX is being called\n")

	FindBulletName(name)
	
	position.x = posX
	position.y = posY
	position.z = posZ

	--print("dt: ", dt)
	-- movimiento parabolico equisde

	position.x = position.x + speed ;
	position.z = position.z + speed ;
	position.y = posY + (speed) + (0.5 * (-9.8))

	return position
end