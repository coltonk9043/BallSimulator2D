#pragma once

#ifndef INPUT_H
#define INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vector2.h"
#include <vector>
class Input {
public:
	Input(GLFWwindow* window);
	void Update();
	bool getKeyPressed(int key);
	bool getKeyDown(int key);
	bool getKeyUp(int key);

	Vector2 getMousePosition();
	bool getMouseButtonPressed(int button);
	bool getMouseButtonDown(int button);
	bool getMouseButtonUp(int button);
private:
	bool keyStates[65535];
	bool mouseStates[8];
	GLFWwindow* window;
};

#endif