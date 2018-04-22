#pragma once
#include "GameObject.h"

class Camera;
class Shader;

class Game
{
public:
	void Reset();
	Game();
	void UpdateWater();


	void Update(Camera& camera, float deltaTime);
	void Draw(Shader& shader);
	void DrawGUI(int screenWidth, int screenHeight);
	void Input();
private:
	std::vector<GameObject*> gameObjects;
	GameObject* player;
	GameObject* waterPlane;

	std::string textToType;

	bool showTyper;
	bool gameOver;
	bool firstStart;

	float speed;
	float sharkSpeed;
	float lastWaterPlaneSpawned = 0;
	
	int waterSpawned = 1;
	int score = 0;
	float countDown = 4;

	Model* waterModel;
	Model* waterBasinModel;
	Model* sharkModel;

	GameObject* rightArm;
	GameObject* leftArm;
	GameObject* waterBasinObj;
	GameObject* sharkObject;

	std::vector<char> possibleChars;
	Model* playerModel;
	Model* armModel;

	static int MapCharToKey(char character);
};

