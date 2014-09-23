#include "Shader.hpp"

#include "Memory Manager/MemoryManager.hpp"

//----------------------------------------------------------------------------------------
Shader::Shader()
{
	const char* FragmentShader = ".\\Code\\Shaders\\FixedFunction.fragment.glsl";
	const char* VertexShader = ".\\Code\\Shaders\\FixedFunction.vertex.glsl";

	initOpenGLFunctions();

	bool m_fatalError = false;

	int vertexShaderID = compileShaderPart(VertexShader, GL_VERTEX_SHADER);
	int fragmentShaderID = compileShaderPart(FragmentShader, GL_FRAGMENT_SHADER);
	

	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShaderID);
	glAttachShader(m_shaderID, fragmentShaderID);
	glLinkProgram(m_shaderID);

	int infoLogLength = 0;
	glGetProgramiv(m_shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char* infoLog = new char[infoLogLength+1];

	if(infoLogLength > 1)
	{
		glGetProgramInfoLog(m_shaderID, infoLogLength, NULL, infoLog);
		OutputDebugStringA(infoLog);
		MessageBoxA(NULL, infoLog, "ERROR", MB_OK);
		m_fatalError = true;
	}

	delete[] infoLog;
	glUseProgram(m_shaderID);
}

//----------------------------------------------------------------------------------------
Shader::Shader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName)
{
	initOpenGLFunctions();

	bool m_fatalError = false;

	int vertexShaderID = compileShaderPart(vertexShaderFileName, GL_VERTEX_SHADER);
	int fragmentShaderID = compileShaderPart(fragmentShaderFileName, GL_FRAGMENT_SHADER);


	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, vertexShaderID);
	glAttachShader(m_shaderID, fragmentShaderID);
	glLinkProgram(m_shaderID);

	int infoLogLength = 0;
	glGetProgramiv(m_shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char* infoLog = new char[infoLogLength+1];

	if(infoLogLength > 1)
	{
		glGetProgramInfoLog(m_shaderID, infoLogLength, NULL, infoLog);
		OutputDebugStringA(infoLog);
		MessageBoxA(NULL, infoLog, "ERROR", MB_OK);
		m_fatalError = true;
	}

	delete[] infoLog;
	glUseProgram(m_shaderID);
}

//----------------------------------------------------------------------------------------
int Shader::compileShaderPart(const std::string& fileName, const int typeOfShader)
{
	bool fatalError = false;

	int shaderID = glCreateShader(typeOfShader);
	FILE* shaderFile = std::fopen(fileName.c_str(), "rb");
	fseek(shaderFile, 0, SEEK_END);
	int fileSizeInBytes = (int)ftell(shaderFile) + 1;
	rewind(shaderFile);
	char* vertText = new char[fileSizeInBytes];
	fread(vertText, sizeof(char), fileSizeInBytes, shaderFile);
	vertText[fileSizeInBytes-1] = 0;
	std::fclose(shaderFile);

	glShaderSource(shaderID, 1, &vertText, NULL);
	glCompileShader(shaderID);
	delete[] vertText;

	int infoLogLength = 0;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char* infoLog = new char[infoLogLength+1];
	glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);

	if(infoLogLength > 1)
	{
		OutputDebugStringA(infoLog);
		MessageBoxA(NULL, infoLog, "ERROR", MB_OK);
		fatalError = true;
		delete[] infoLog;
		return -1;
	}
	else
	{
		delete[] infoLog;
		return shaderID;
	}
}