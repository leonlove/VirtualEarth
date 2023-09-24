#pragma once

#include "CELLProgramLibary.hpp"
namespace CELL
{
	class Model {
	public:
		Model() {
		}
		~Model(){}

		void initialize(CELLOpenGL* device) {
			// set up vertex data (and buffer(s)) and configure vertex attributes
			// ------------------------------------------------------------------
			//float vertices[] = {
			//	0.5f,  0.5f, 0.0f,  // top right
			//	0.5f, -0.5f, 0.0f,  // bottom right
			//	-0.5f, -0.5f, 0.0f,  // bottom left
			//	-0.5f,  0.5f, 0.0f   // top left 
			//};
			//unsigned int indices[] = {  // note that we start from 0!
			//	0, 2, 1,  // first Triangle
			//	0, 3, 2   // second Triangle
			//};

			float vertices[] = {
				// 位置              // 颜色
				0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
				0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // 顶部
				- 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f   // 左下
			};
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			//glGenBuffers(1, &EBO);
			// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			glBindVertexArray(VAO);

			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// 颜色属性
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

			// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			glBindVertexArray(0);

			//float vertices[] = {
			//	-0.5f, -0.5f, 0.0f, // left  
			//	0.5f, -0.5f, 0.0f, // right 
			//	0.0f,  0.5f, 0.0f  // top   
			//};

			//glGenVertexArrays(1, &VAO);
			//glGenBuffers(1, &VBO);
			//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
			//glBindVertexArray(VAO);

			//glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			//glEnableVertexAttribArray(0);

			//// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
			//glBindBuffer(GL_ARRAY_BUFFER, 0);

			//// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
			//// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
			//glBindVertexArray(0);
		}

		void Draw()
		{
			// draw mesh
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//glBindVertexArray(0);
		}
	private:
		unsigned int VAO;
		unsigned int VBO, EBO;
	};

    class   CELLResourceMgr
    {
    public:
        /// 针对绘制屏幕二维数据
        PROGRAM_P2_UC   _PROGRAM_P2_UC;
		/// 针对绘制屏幕三维数据
		PROGRAM_P3_UC   _PROGRAM_P3_UC;

		Model _Model;
    public:
        CELLResourceMgr()
        {}
        ~CELLResourceMgr()
        {}
    public:
        void    initialize(CELLOpenGL* device)
        {
            _PROGRAM_P2_UC.initialize(device);
			_PROGRAM_P3_UC.initialize(device);
			_Model.initialize(device);
        }

        void    destroy()
        {
            _PROGRAM_P2_UC.destroy();
			_PROGRAM_P3_UC.destroy();
        }
    };
}
