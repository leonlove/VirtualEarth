#ifndef MESH_H
#define MESH_H


#include <string>
#include <vector>
#include "CELLMath.hpp"
#include "CELLOpenGL.h"
#include "CELLProgramLibary.hpp"
using namespace std;

#define MAX_BONE_INFLUENCE 4

namespace CELL {
	struct Vertex {
		// position
		float3 Position;
		// normal
		float3 Normal;
		// texCoords
		float2 TexCoords;
		// tangent
		float3 Tangent;
		// bitangent
		float3 Bitangent;
		//bone indexes which will influence this vertex
		int m_BoneIDs[MAX_BONE_INFLUENCE];
		//weights from each bone
		float m_Weights[MAX_BONE_INFLUENCE];
	};

	struct Texture {
		unsigned int id;
		string type;
		string path;
	};

	class Mesh {
	public:
		// mesh Data
		vector<Vertex>       vertices;
		vector<unsigned int> indices;
		vector<Texture>      textures;
		unsigned int VAO;

		// constructor
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

		// render the mesh
		void Draw(CELLProgram &shader);

	private:
		// render data 
		unsigned int VBO, EBO;

		// initializes all the buffer objects/arrays
		void setupMesh();
	};
}

#endif