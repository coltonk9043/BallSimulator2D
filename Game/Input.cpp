#include "Input.h"

Input::Input(GLFWwindow* window) {
	this->window = window;
}

void Input::Update() {
	for (int i = 0; i < 8; i++) {
		if (!glfwGetMouseButton(window, i)) {
			mouseStates[i] = false;
		}
	}
}

/// <summary>
/// Gets whether a mouse button is currently pressed down.
/// </summary>
/// <param name="key">The integer code of the key being checked.</param>
/// <returns>True if the key is down.</returns>
bool Input::getKeyDown(int key) {
	if (glfwGetKey(window, key) == GLFW_PRESS) {
		this->keyStates[key] = true;
		return true;
	}
	this->keyStates[key] = false;
	return false;
}

/// <summary>
/// Gets whether a mouse button was pressed. Only returns one tick.
/// </summary>
/// <param name="key">The integer code of the key being checked</param>
/// <returns>True if the key was pressed.</returns>
bool Input::getKeyPressed(int key) {
	if (glfwGetKey(window, key) == GLFW_PRESS) {
		this->keyStates[key] = true;
		if (!this->keyStates[key]) {
			return true;
		}
	}
	
	this->keyStates[key] = false;
	return false;
}

bool Input::getKeyUp(int key) {
	if (glfwGetKey(window, key) != GLFW_PRESS && this->keyStates[key]) {
		this->keyStates[key] = false;
		return true;
	}
	return false;
}

bool Input::getMouseButtonPressed(int button) {
	bool result = false;
	if (glfwGetMouseButton(window, button)) {
		if (!this->mouseStates[button]) {
			result =  true;
		}
		this->mouseStates[button] = true;
	}
	return result;
}

bool Input::getMouseButtonDown(int button) {
	return false;
}

bool Input::getMouseButtonUp(int button) {
	return false;
}