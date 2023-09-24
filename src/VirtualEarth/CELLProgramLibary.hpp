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
	public:
		virtual bool    initialize(CELLOpenGL* device)
		{
			const char* vs =
			{
				"#version   330 core\n"
				"layout (location = 0) in vec3 aPos; \n"
				"layout (location = 1) in vec3 aColor;\n"
				"out vec3 ourColor;\n"
				"void main()\n"
				"{\n"
				"	gl_Position = vec4(aPos, 1.0);\n"
				"   ourColor = aColor;\n"
				"}\n"
			};
			const char* ps =
			{
				"#version   330 core\n"
				"out vec4 FragColor;\n"
				"in vec3 ourColor;\n"
				"void main()\n"
				"{\n"
				"   FragColor = vec4(ourColor, 1.0);\n"
				"}\n"
			};
			bool    result = device->createProgram(*this, vs, ps);
			if (result)
			{
				//_position = device->getAttribLocation(_program, "_position");
				//_color = device->getUniformLocation(_program, "ourColor");
				//_mvp = device->getUniformLocation(_program, "_MVP");
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