name = "Bullet"
position = {x, y, z}
speed = 1
callatelua = 8

function BulletMovement(posX, posY, posZ, rotY)

	--print("[LUA] SetPosX is being called\n")

	--FindBulletName(name)
	
	position.x = posX
	position.y = posY
	position.z = posZ

	--print("rotY", rotY)
	--position.x = (-((-tank.x * math.sin(position.y)) + (tank.z * math.cos(position.y))) + (math.cos(position.y) - tank.x))
	position.x = position.x + (math.sin(rotY) * speed)
	position.z = position.z + (math.cos(rotY) * speed)
	--position.y = position.y + (speed * timepo) + 0.5 * lagravedaddelasunto * timepo * timepo
	
	--print("dt: ", dt)
	-- movimiento parabolico equisde

	--position.x = position.x + speed
	--position.z = position.z + speed
	--position.y = posY + (speed) + (0.5 * (-9.8))

	return position
end

