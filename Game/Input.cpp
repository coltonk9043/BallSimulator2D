#include "Input.h"

/// <summary>
/// Constructor for Input class.
/// </summary>
/// <param name="window">The window displaying information.</param>
Input::Input(GLFWwindow* window) {
	this->window = window;
}

/// <summary>
/// Updates the input class once per tick.
/// </summary>
void Input::Update() {
	// For every mouse button.
	for (int i = 0; i < 8; i++) {
		// Check if it is not down, if not, set input to false.
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

/// <summary>
/// Get whether a key was lifted per frame (Not always up, only released).
/// </summary>
/// <param name="key">The key which is being checked.</param>
/// <returns>Whether the key is lifted.</returns>
bool Input::getKeyUp(int key) {
	if (glfwGetKey(window, key) != GLFW_PRESS && this->keyStates[key]) {
		this->keyStates[key] = false;
		return true;
	}
	return false;
}

/// <summary>
/// Gets whether a key is pressed (Triggers once).
/// </summary>
/// <param name="button">The key which is being checked.</param>
/// <returns>Whether the button is currently pressed down.</returns>
bool Input::getMouseButtonPressed(int button) {
	bool result = false;
	// If the key is pressed, check if it is currently in not in the key states array.
	if (glfwGetMouseButton(window, button)) {
		if (!this->mouseStates[button]) {
			result =  true;
		}
		// Set the mouse state to true.
		this->mouseStates[button] = true;
	}
	return result;
}

/// <summary>
/// 
/// </summary>
/// <param name="button"></param>
/// <returns></returns>
bool Input::getMouseButtonDown(int button) {
	if (glfwGetMouseButton(window, button) == GLFW_PRESS) {
		this->mouseStates[button] = true;
		return true;
	}
	this->mouseStates[button] = false;
	return false;
}

/// <summary>
/// Gets whether or not a mouse button was released.
/// </summary>
/// <param name="button">The button being checked.</param>
/// <returns>Whether or not the button is up.</returns>
bool Input::getMouseButtonUp(int button) {
	if (glfwGetMouseButton(window, button) != GLFW_PRESS && this->mouseStates[button]) {
		this->mouseStates[button] = false;
		return true;
	}
	return false;
}