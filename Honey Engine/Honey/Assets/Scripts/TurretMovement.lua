name = "Turret"

function TurretRotation(width, mouseX)

	--FindTurretName(name)

	centerPos = width / 2
	mouseRot = mouseX - centerPos

	return mouseRot
end