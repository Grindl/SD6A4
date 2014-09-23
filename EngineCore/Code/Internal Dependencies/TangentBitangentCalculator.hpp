
#include "..\Primitives\Vector3f.hpp"
#include "..\Primitives\Vector2f.hpp"

bool ComputeSurfaceTangentsAtVertex(
	Vector3f& surfaceTangentAtVertex_out,
	Vector3f& surfaceBitangentAtVertex_out,
	const Vector3f& normalAtThisVertex,
	const Vector3f& positionOfThisVertex,
	const Vector2f& texCoordsOfThisVertex,
	const Vector3f& positionOfPreviousAdjacentVertex,
	const Vector2f& texCoordsOfPreviousAdjacentVertex,
	const Vector3f& positionOfNextAdjacentVertex,
	const Vector2f& texCoordsOfNextAdjacentVertex );