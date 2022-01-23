name = "Bullet"
position = {x, y, z}
speed = 2

function BulletMovement(posX, posY, posZ, rotY)

	position.x = posX
	position.y = posY
	position.z = posZ

	position.x = position.x + (math.sin(rotY) * speed)
	position.z = position.z + (math.cos(rotY) * speed)
	position.y = position.y - 0.2 + speed - 0.5 * speed * speed

	return position
end