#include "TangentBitangentCalculator.hpp"


//-----------------------------------------------------------------------------------------------
// Returns TRUE if the Bitangent is "right handed" with respect to the Normal and Tangent;
// i.e. if [Tangent,Bitangent,Normal] is a right-handed basis.  Typically this bool is
// converted to a +/- 1.0 and passed into a vertex shader as the Tangent's "w" coordinate.
// The Bitangent is then computed within the vertex shader using cross product and "w" to
// disambiguate between which of the two possible perpendiculars to use for the Bitangent.
// 
// From Professor Eiserloh
bool ComputeSurfaceTangentsAtVertex(
	Vector3f& surfaceTangentAtVertex_out,
	Vector3f& surfaceBitangentAtVertex_out,
	const Vector3f& normalAtThisVertex,
	const Vector3f& positionOfThisVertex,
	const Vector2f& texCoordsOfThisVertex,
	const Vector3f& positionOfPreviousAdjacentVertex,
	const Vector2f& texCoordsOfPreviousAdjacentVertex,
	const Vector3f& positionOfNextAdjacentVertex,
	const Vector2f& texCoordsOfNextAdjacentVertex )
{
	Vector3f vecToPrevious	= positionOfPreviousAdjacentVertex - positionOfThisVertex;
	Vector3f vecToNext		= positionOfNextAdjacentVertex - positionOfThisVertex;

	Vector2f texToPrevious	= texCoordsOfPreviousAdjacentVertex - texCoordsOfThisVertex;
	Vector2f texToNext		= texCoordsOfNextAdjacentVertex - texCoordsOfThisVertex;

	float invDeterminant = 1.0f / ((texToPrevious.x * texToNext.y) - (texToNext.x * texToPrevious.y));
	// (U02 * V01) - (U01 * V02)

	Vector3f uDirectionInWorldSpace(	
						(texToNext.y * vecToPrevious.x - texToPrevious.y * vecToNext.x),
						(texToNext.y * vecToPrevious.y - texToPrevious.y * vecToNext.y),
						(texToNext.y * vecToPrevious.z - texToPrevious.y * vecToNext.z)
						);

	Vector3f vDirectionInWorldSpace(
						(texToPrevious.x * vecToNext.x - texToNext.x * vecToPrevious.x),
						(texToPrevious.x * vecToNext.y - texToNext.x * vecToPrevious.y),
						(texToPrevious.x * vecToNext.z - texToNext.x * vecToPrevious.z)
						);

	uDirectionInWorldSpace = uDirectionInWorldSpace* invDeterminant;
	vDirectionInWorldSpace = vDirectionInWorldSpace* invDeterminant;

	if( abs( normalAtThisVertex.magnitude() - 1.f ) > 0.01f )
	{
		//TODO come up with some other error reporting
		//FatalError( "Bad normal", "bleagh." );
	}

	Vector3f& tangentFromCalculations = uDirectionInWorldSpace;
	Vector3f& bitangentFromCalculations = vDirectionInWorldSpace;
	Vector3f bitangentFromCross = normalAtThisVertex.crossProduct(tangentFromCalculations);
	bitangentFromCross.normalize();
	Vector3f tangentFromCross = bitangentFromCross.crossProduct(normalAtThisVertex);

	float computedBitangentDotCrossBitangent = bitangentFromCalculations.dot(bitangentFromCross);
	bool isRightHanded = (computedBitangentDotCrossBitangent >= 0.f );
	if( !isRightHanded )
	{
		bitangentFromCross = bitangentFromCross * -1.f;
	}

	surfaceTangentAtVertex_out = tangentFromCross;
	surfaceBitangentAtVertex_out = bitangentFromCross;

	return( isRightHanded );
}
