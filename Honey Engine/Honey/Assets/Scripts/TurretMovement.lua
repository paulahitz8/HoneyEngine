name = "Turret"

function TurretRotation(width, mouseX)

	centerPos = width / 2
	mouseRot = mouseX - centerPos

	return mouseRot
end