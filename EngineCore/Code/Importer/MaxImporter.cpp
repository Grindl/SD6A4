#include "MaxImporter.hpp"
#include <vector>
#include "..\Rendering\Texture.hpp"
#include "..\Utility\StringUtility.hpp"

#include "Memory Manager/MemoryManager.hpp"

static float IDENTITYMAT[] = {1.f, 0.f, 0.f, 0.f,
									0.f, 1.f, 0.f, 0.f,
									0.f, 0.f, 1.f, 0.f,
									0.f, 0.f, 0.f, 1.f}; //WARNING, this ought to be const, but is not

//----------------------------------------------------------------------------------------
bool RecursiveTriFragTreeInsert(DebugMultiPoly::TriFragNode* currentParent, DebugMultiPoly::TriFragNode* nodeToInsert, int parentToFind)
{
	bool successfulInsert = false;
	if (currentParent->index == parentToFind)
	{
		currentParent->children.push_back(nodeToInsert);
		successfulInsert = true;
	}
	else for (unsigned int nodeIndex = 0; nodeIndex < currentParent->children.size(); nodeIndex++)
	{
		successfulInsert = successfulInsert || RecursiveTriFragTreeInsert(currentParent->children[nodeIndex], nodeToInsert, parentToFind);
	}
	return successfulInsert;
}

//----------------------------------------------------------------------------------------
void RecursiveTriFragVertsInsert(DebugMultiPoly::TriFragNode* currentParent, int parentToFind, int materialID, FILE* modelFile)
{
	if (currentParent->index == parentToFind)
	{
		DebugMultiPoly::TriFragNode* currentChild = new DebugMultiPoly::TriFragNode();
		currentParent->children.push_back(currentChild);
		int numVerts = 0;
		fread(&numVerts, sizeof(int), 1, modelFile);
		VertexData* localVertexAttrib = new VertexData[numVerts];
		fread(localVertexAttrib, sizeof(VertexData), numVerts, modelFile);
		for (int ii = 0; ii < numVerts; ii++)
		{
			localVertexAttrib[ii].renderData[8] = 1 - localVertexAttrib[ii].renderData[8];
		}
		currentChild->index = parentToFind;
		currentChild->materialIndex = materialID;
		currentChild->sizeOfVBO = numVerts;
		glGenBuffers(1, &currentChild->VBOID);
		glBindBuffer(GL_ARRAY_BUFFER, currentChild->VBOID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*numVerts, localVertexAttrib, GL_STATIC_DRAW);
		//TODO this needs to have an identity matrix, since ALL leaf nodes are render, and not transform
		currentChild->transform.push_back(&(IDENTITYMAT[0]));
		currentChild->keyframeTime.push_back(0.f);
	}
	else for (unsigned int nodeIndex = 0; nodeIndex < currentParent->children.size(); nodeIndex++)
	{
		RecursiveTriFragVertsInsert(currentParent->children[nodeIndex], parentToFind, materialID, modelFile);
	}
}

//----------------------------------------------------------------------------------------
void RecursiveTriFragMaterialInsert(DebugMultiPoly::TriFragNode* currentParent, int materialToFind, Material* materialToInsert, FILE* modelFile)
{

	if (currentParent->materialIndex == materialToFind)
	{
		currentParent->material = materialToInsert;
	}
	for (unsigned int nodeIndex = 0; nodeIndex < currentParent->children.size(); nodeIndex++) //intentionall not else; there can be many things using the same material
	{
		RecursiveTriFragMaterialInsert(currentParent->children[nodeIndex], materialToFind, materialToInsert, modelFile);
	}
}

//----------------------------------------------------------------------------------------
void RecursiveTriFragTransformInsert(DebugMultiPoly::TriFragNode* currentParent, int parentToFind, float* transformToInsert, float timeOfTransform, FILE* modelFile)
{

	if (currentParent->index == parentToFind)
	{
		currentParent->transform.push_back(transformToInsert);
		currentParent->keyframeTime.push_back(timeOfTransform);
	}
	for (unsigned int nodeIndex = 0; nodeIndex < currentParent->children.size(); nodeIndex++) //intentionally not else-for
	{
		RecursiveTriFragTransformInsert(currentParent->children[nodeIndex], parentToFind, transformToInsert, timeOfTransform, modelFile);
	}
}


//----------------------------------------------------------------------------------------
RenderVector* MaxImporter::ImportFrom3DSMaxToRenderVector(const std::string& fileName, int& out_size)
{
	//TODO this
	return 0;
}

//----------------------------------------------------------------------------------------
VertexData* MaxImporter::ImportFrom3DSMaxToVertexData(const std::string& fileName, int& out_size)
{
	//TODO THIS
	
	FILE* modelFile = fopen(fileName.c_str(), "rb");
	int totalVerts = 0;
	int currentNode = 0;
	std::vector<VertexData*> vertexAttribArray = std::vector<VertexData*>();
	std::vector<int> vertexAttribLength = std::vector<int>();
	std::vector<int> vertexAttribMat = std::vector<int>();
	std::vector<std::string> materialAtlass = std::vector<std::string>();
	bool vertexParse = true;
	while(!feof(modelFile) && vertexParse)
	{
		int numVerts = 0;
		fread(&numVerts, sizeof(int), 1, modelFile);
		if(numVerts == -1)
		{
			vertexParse = false;
		}
		else
		{
			int materialID = 0;
			fread(&materialID, sizeof(int), 1, modelFile);
			VertexData* localVertexAttrib = new VertexData[numVerts];
			fread(localVertexAttrib, sizeof(VertexData), numVerts, modelFile);
			totalVerts += numVerts;
			vertexAttribLength.push_back(numVerts);
			vertexAttribArray.push_back(localVertexAttrib);
			vertexAttribMat.push_back(materialID);
			currentNode++;
		}
	}
	while (!feof(modelFile))
	{
		int lengthOfFilename = 0;
		fread(&lengthOfFilename, sizeof(int), 1, modelFile);
		int materialID = 0;
		fread(&materialID, sizeof(int), 1, modelFile);
		char* texFileName = new char[255];
		fread(texFileName, sizeof(char), lengthOfFilename, modelFile);
		std::string appendedTexFileName = ".\\Data\\";
		appendedTexFileName.append(texFileName);
		materialAtlass.push_back(appendedTexFileName);
		delete[] texFileName;
	}
	out_size = totalVerts;
	VertexData* vertexAttribCollected = new VertexData[totalVerts];
	int currentVertOffset = 0;
	while (vertexAttribArray.size() > 0)
	{
		memcpy(vertexAttribCollected+currentVertOffset, vertexAttribArray[0], vertexAttribLength[0]*sizeof(VertexData));
		currentVertOffset += vertexAttribLength[0];
		VertexData* condemnedArray = vertexAttribArray[0];
		vertexAttribArray.erase(vertexAttribArray.begin());
		vertexAttribLength.erase(vertexAttribLength.begin());
		delete[] condemnedArray;
	}
	return vertexAttribCollected;
}

//----------------------------------------------------------------------------------------
DebugMultiPoly* MaxImporter::ImportFrom3DSMaxToDebugMultiPoly(const std::string& fileName)
{
	FILE* modelFile = fopen(fileName.c_str(), "rb");
	int currentNode = 0;
	std::vector<VertexData*> vertexAttribArray = std::vector<VertexData*>();
	std::vector<int> vertexAttribLength = std::vector<int>();
	std::vector<int> vertexAttribMat = std::vector<int>();
	std::vector<std::string> materialAtlass = std::vector<std::string>();
	std::vector<Material*> actualMaterials = std::vector<Material*>();
	
	bool treeParse = true;
	std::vector<DebugMultiPoly::TriFragNode*> triFragTree;
	while(!feof(modelFile) && treeParse)
	{
		int parentID = -1;
		int childID = -1;
		fread(&parentID, sizeof(int), 1, modelFile);
		if (parentID != -1)
		{
			fread(&childID, sizeof(int), 1, modelFile);
			DebugMultiPoly::TriFragNode* localNode = new DebugMultiPoly::TriFragNode;
			localNode->index = childID;
			localNode->materialIndex = -1;
			localNode->material = 0;
			localNode->sizeOfVBO = 0;
			localNode->transform.push_back(IDENTITYMAT);
			localNode->keyframeTime.push_back(0.f);


			bool successfulInsert = false;
			for (unsigned int nodeIndex = 0; nodeIndex < triFragTree.size(); nodeIndex++)
			{
				successfulInsert = successfulInsert|| RecursiveTriFragTreeInsert(triFragTree[nodeIndex], localNode, parentID);
			}
			if (!successfulInsert)
			{
				triFragTree.push_back(localNode);
			}
		}
		else
		{
			treeParse = false;
		}
		//TODO use the newly created tree
	}

	bool vertexParse = true;
	while(!feof(modelFile) && vertexParse)
	{
		int nodeID = 0;
		fread(&nodeID, sizeof(int), 1, modelFile);
		if(nodeID == -1)
		{
			vertexParse = false;
		}
		else
		{
			//Potential problem: this will loop over all top level nodes, even after the appropriate node has been found
			//probably not a bug, but likely will take extra time on load
			int materialID = 0;
			fread(&materialID, sizeof(int), 1, modelFile);
			for (unsigned int nodeIndex = 0; nodeIndex < triFragTree.size(); nodeIndex++)
			{
				RecursiveTriFragVertsInsert(triFragTree[nodeIndex], nodeID, materialID, modelFile);
			}
		}
	}

	bool materialsParse = true;
	while (!feof(modelFile) && materialsParse)
	{
		int materialID = 0;
		fread(&materialID, sizeof(int), 1, modelFile);
		if (materialID == -1)
		{
			materialsParse = false;
		}

		else 
		{
			int lengthOfFilename = 0;
			fread(&lengthOfFilename, sizeof(int), 1, modelFile);
			if(lengthOfFilename != 0)
			{

				char* texFileName = new char[lengthOfFilename];
				fread(texFileName, sizeof(char), lengthOfFilename, modelFile);
				std::string appendedTexFileName = ".\\Data\\";
				appendedTexFileName.append(texFileName);
				std::vector<std::string> fileTypeCheck = StringUtility::StringSplit(appendedTexFileName, ".", "");
				if (fileTypeCheck[fileTypeCheck.size()-1] == "dds")
				{
					appendedTexFileName = "";
					for (int ii = 0; ii < fileTypeCheck.size() - 1; ii++)
					{
						appendedTexFileName+= fileTypeCheck[ii];
					}
					appendedTexFileName+= ".png";
					//appendedTexFileName = ".\\Data\\cobblestonesDiffuse.png";
				}
				delete[] texFileName;

				Texture* currTex = Texture::CreateOrGetTexture(appendedTexFileName);
				Texture* HACKNORM = new Texture(".\\Data\\cobblestonesNormal.png");
				//Texture* currTex = new Texture(".\\Data\\cobblestonesDiffuse.png");
				Material* currMat = new Material();
				currMat->m_useVBO = true;
				currMat->m_useDiffuse = true;
				currMat->m_useNormal = true;
				currMat->m_normalID = HACKNORM->m_openGLTextureID;
				currMat->m_useShaderProgram = true;
				currMat->m_diffuseID = currTex->m_openGLTextureID;

				for (unsigned int nodeIndex = 0; nodeIndex < triFragTree.size(); nodeIndex++)
				{
					RecursiveTriFragMaterialInsert(triFragTree[nodeIndex], materialID, currMat, modelFile);
				}
			}
		}
	}

	//for (unsigned int materialIter = 0; materialIter < materialAtlass.size(); materialIter++)
	//{
	//
	//}


	bool matrixParse = true;
	while (!feof(modelFile) && matrixParse)
	{
		//TODO read in matrices and apply them to my transform tree
		int transformNodeID = 0;
		fread(&transformNodeID, sizeof(int), 1, modelFile);
		if (transformNodeID == -1)
		{
			matrixParse = false;
		}
		else
		{
			float matrixTimestamp = 0.f;
			fread(&matrixTimestamp, sizeof(float), 1, modelFile);
			float* transformMatrix = new float[16];
			fread(transformMatrix, sizeof(float), 16, modelFile);

			for (unsigned int nodeIndex = 0; nodeIndex < triFragTree.size(); nodeIndex++)
			{
				RecursiveTriFragTransformInsert(triFragTree[nodeIndex], transformNodeID, transformMatrix, matrixTimestamp, modelFile); //WARNING this is not sorted
			}
		}
	}

	DebugMultiPoly* theMultiPoly = new DebugMultiPoly();
	theMultiPoly->m_rootTriFragNodes = triFragTree;
	//TODO delete all the random new'd things in this function, likely MASSIVE memory leaks
	return theMultiPoly;
}