#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#undef main

class Display
{
public:
	Display(int width, int height, const std::string& title);
	void SwapBuffers();
	inline GLFWwindow* GetWindow() const {
		return m_window;
	}
	virtual ~Display();


	int Width;
	int Height;


protected:
private:
	void operator=(const Display& display) {}
	Display(const Display& display) {}

	GLFWwindow* m_window;
};