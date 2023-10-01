#pragma once


#include "CELLOpenGL.h"

namespace CELL
{
    class   PROGRAM_P2_UC :public CELLProgram
    {
    public:
        attribute   _position;
        uniform     _color;
        uniform     _mvp;
    public:
        virtual bool    initialize(CELLOpenGL* device)
        {
            const char* vs =
            {
                "#version   330 \n"
                "precision  highp float; \n"
                "uniform    mat4    _MVP; \n"
                "attribute  vec2    _position;\n"
                "void main()\n"
                "{"
                "   vec4   pos  =   vec4(_position.x,_position.y,0,1);\n"
                "   gl_Position =   _MVP * pos;\n"
                "}"
            };
            const char* ps  =   
            {
                "#version   330 \n"
                "precision  highp float; "
                "uniform    vec4    _color;\n"
                "void main()\n"
                "{\n"
                "   gl_FragColor   =   _color;\n"
                "}\n"
            };
            bool    result  =   device->createProgram(*this,vs,ps);
            if (result)
            {
                _position   =   device->getAttribLocation(_program,    "_position");
                _color      =   device->getUniformLocation(_program,   "_color");
                _mvp        =   device->getUniformLocation(_program,   "_MVP");
            }
            else
            {
                assert(result == true);
            }
            return  result;
        }
        /**
        *   使用shader
        */
        virtual void    begin()
        {
            _device->useProgram(_program);
            _device->enableVertexAttribArray(_position);
        }
        /**
        *   结束
        */
        virtual void    end()
        {
            _device->disableVertexAttribArray(_position);
            _device->useProgram(0);
        }

    };

	class   PROGRAM_P3_UC :public CELLProgram
	{
	public:
	//	attribute   _position;
	//	uniform     _color;
	//	uniform     _mvp;
		uniform     _texture1;
		uniform     _texture2;
		uniform     _model;
		uniform     _view;
		uniform     _projection;
	public:
		virtual bool    initialize(CELLOpenGL* device)
		{
			const char* vs =
			{
				"#version   330 core\n"
				"layout (location = 0) in vec3 aPos; \n"
				"layout (location = 1) in vec2 aTexCoord;\n"
				"uniform mat4 model;\n"
				"uniform mat4 view;\n"
				"uniform mat4 projection;\n"
				"out vec3 ourColor;\n"
				"out vec2 TexCoord;\n"
				"void main()\n"
				"{\n"
				"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
				"	TexCoord = aTexCoord;\n"
				"}\n"
			};
			const char* ps =
			{
				"#version   330 core\n"
				"out vec4 FragColor;\n"
				"in vec2 TexCoord;\n"
				"uniform sampler2D texture1;\n"
				"uniform sampler2D texture2;\n"
				"void main()\n"
				"{\n"
				"   FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
				"}\n"
			};
			bool    result = device->createProgram(*this, vs, ps);
			if (result)
			{
				//_position = device->getAttribLocation(_program, "_position");
				//_color = device->getUniformLocation(_program, "ourColor");
				//_mvp = device->getUniformLocation(_program, "_MVP");
				_model = device->getUniformLocation(_program, "model");
				_view = device->getUniformLocation(_program, "view");
				_projection = device->getUniformLocation(_program, "projection");
				_texture1 = device->getUniformLocation(_program, "texture1");
				_texture2 = device->getUniformLocation(_program, "texture2");
			}
			else
			{
				assert(result == true);
			}
			return  result;
		}
		/**
		*   使用shader
		*/
		virtual void    begin()
		{
			_device->useProgram(_program);
			//_device->enableVertexAttribArray(_position);
		}
		/**
		*   结束
		*/
		virtual void    end()
		{
			//_device->disableVertexAttribArray(_position);
			_device->useProgram(0);
		}

	};
}