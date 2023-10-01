#pragma once
#include "CELLOpenGL.h"

namespace   CELL
{ 
	class Model {
	public:
		Model() {
		}
		~Model() {}

		void initialize(CELLOpenGL* device);

		void Draw();
	private:
		unsigned int VAO;
		unsigned int VBO, EBO;
		unsigned int texture1;
		unsigned int texture2;
	};
}