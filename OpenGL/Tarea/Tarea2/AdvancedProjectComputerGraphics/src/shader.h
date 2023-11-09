#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
	std::string geometrySource;
};
//uniform es la variable que se comunica entre CPU y GPU

class Shader {
private:
	unsigned int rendererId;
	std::unordered_map<std::string, int> uniformLocationCache;//para no necesitar andar buscando los uniforms, es una tabla de hash
	ShaderProgramSource shaders;

public:
	//constructores
	Shader( const std::string& vertexFilePath, const std::string& fragmentFilePath );//lo minimo que necesito para que funcione
	Shader( const std::string& vertexFilePath, const std::string& fragmentFilePath, const std::string& geometryFilePath );
	~Shader();

	void bind() const;
	void unBind() const;

	// set uniforms
	void setUniform1i( const std::string& name, int value );
	// set uniforms.
	void setUniform4f( const std::string& name, glm::vec4 vector );//para modificar un vector de 4 flotantes
	void SetuniformsMat4f( const std::string& name, const glm::mat4& mat4 );//modificar matriz de 4x4

private:
	std::string parseShader( const std::string& filepath );//le das la ubicacion de tu archivo, lo abre y pasas un string
	unsigned int compileShader( unsigned int type, const std::string& source );
	unsigned int createShader( const std::string& vertexShader, const std::string& fragmentShader );
	unsigned int createShader( const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader );
	int getUniformLocation( const std::string& name );
};