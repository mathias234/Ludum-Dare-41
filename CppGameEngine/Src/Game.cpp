#include "Game.h"
#include "Camera.h"
#include "vendor/imgui/imgui.h"
#include "InputManager.h"
#include <ctime>

void Game::Reset()
{
	possibleChars = std::vector<char>{
		'a',
		'b',
		'c',
		'd',
		'e',
		'f',
		'g',
		'h',
		'i',
		'j',
		'k',
		'l',
		'm',
		'n',
		'o',
		'p',
		'q',
		'r',
		's',
		't',
		'u',
		'v',
		'w',
		'x',
		'y',
		'z'
	};

	if(!firstStart)
	{
		for (auto gameObject : gameObjects)
		{
			delete gameObject;
		}
	}

	gameObjects.clear();

	srand(time(nullptr));

	speed = 20.0f;
	sharkSpeed = 15.0f;
	showTyper = true;
	gameOver = false;
	lastWaterPlaneSpawned = 0;
	waterSpawned = 1;
	countDown = 4;
	score = 0;

	playerModel = Model::GetModel("res/models/player.obj");
	armModel = Model::GetModel("res/models/arm.obj");
	sharkModel = Model::GetModel("res/models/shark.obj");
	waterBasinModel = Model::GetModel("res/models/waterBasin.obj");
	waterModel = Model::GetModel("res/models/waterPlane.obj");
	
	player = new GameObject({ 0,0,0 }, { 1,1,1 }, Vector3f(), playerModel);
	waterPlane = new GameObject({ 0,0,0 }, { 1,1,1 }, Vector3f(), waterModel);
	waterBasinObj = new GameObject({ 0,0,0 }, { 1,1,1 }, Vector3f(), waterBasinModel);
	sharkObject = new GameObject({ 0,0.1f,50 }, { 0.5f,0.5f,0.5f }, Vector3f(5, 0, 0), sharkModel);

	waterModel->GetMaterial(0)->Diffuse = Texture::GetTexture("res/textures/WaterTexture.png");
	sharkModel->GetMaterial(0)->Diffuse = Texture::GetTexture("res/textures/sharkTexture.png");
	armModel->GetMaterial(0)->Diffuse = Texture::GetTexture("res/textures/armTexture.png");
	playerModel->GetMaterial(0)->Diffuse = Texture::GetTexture("res/textures/playerTexture.png");

	rightArm = new GameObject({ -1, 0, 0 }, { 1,1,1 }, Vector3f(), armModel);
	leftArm = new GameObject({ 1, 0, 0 }, { 1,1,1 }, Vector3f(180, 0, 0), armModel);

	gameObjects.push_back(player);
	gameObjects.push_back(waterPlane);
	gameObjects.push_back(waterBasinObj);
	gameObjects.push_back(rightArm);
	gameObjects.push_back(leftArm);
	gameObjects.push_back(sharkObject);


	for (int i = 0; i < 6; i++)
	{
		textToType.push_back(possibleChars[rand() % possibleChars.size()]);
	} 


	firstStart = false;
}

Game::Game()
{
	Reset();
}


void Game::UpdateWater()
{

	auto distance = glm::distance(player->GetPosition(), Vector3f(0, 0, lastWaterPlaneSpawned));
	if (distance >= 20 && distance <= 100)
	{
		gameObjects.push_back(new GameObject({ 0,0,-100 * waterSpawned }, { 1,1,1 }, Vector3f(), waterModel));
		gameObjects.push_back(new GameObject({ 0,0,-100 * waterSpawned }, { 1,1,1 }, Vector3f(), waterBasinModel));
		lastWaterPlaneSpawned = -100 * waterSpawned;
		waterSpawned++;
	}
}

void Game::Update(Camera& camera, float deltaTime)
{
	if(countDown > 0)
	{
		countDown -= deltaTime;
		return;
	}

	float swimAmount = -speed * 4.5f;
	leftArm->SetRotation(leftArm->GetRotation() + Vector3f(swimAmount * deltaTime, 0, 0));
	rightArm->SetRotation(rightArm->GetRotation() + Vector3f(swimAmount * deltaTime, 0, 0));
	player->SetPosition(player->GetPosition() + Vector3f(0, 0, -speed * deltaTime ));
	sharkObject->SetPosition(sharkObject->GetPosition() + Vector3f(0, 0, -sharkSpeed * deltaTime));

	leftArm->SetPosition(player->GetPosition() + Vector3f(1, 0, 0));
	rightArm->SetPosition(player->GetPosition() + Vector3f(-1, 0, 0));

	Vector3f cameraOffset = { 0, 5, 10 };
	camera.Position = player->GetPosition() + cameraOffset;

	if (speed > 0)
		speed -= 6 * deltaTime;
	else
		speed = 0;


	if (glm::distance(player->GetPosition(), sharkObject->GetPosition()) <= 5.0f)
	{
		// Game Over!
		sharkSpeed = 0;
		speed = 0;
		sharkObject->SetPosition(player->GetPosition() + Vector3f(0, 0, 5));
		gameOver = true;
	}

	UpdateWater();
}

void Game::Draw(Shader& shader)
{
	for (auto gameObject : gameObjects)
	{
		gameObject->Draw(shader);
	}
}

void Game::DrawGUI(const int screenWidth, const int screenHeight)
{
	if(countDown > 0)
	{
		ImGui::SetNextWindowPos({ (float)screenWidth / 2.0f - 120 / 2, (float)screenHeight / 2.0f - 45/2 }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ 120, 45 }, ImGuiCond_Always);
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::Begin("Countdown", &showTyper, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::SetWindowFontScale(2);
			ImGui::TextColored({ 0,0,0,1 }, std::to_string((int)countDown).c_str());
		}
		ImGui::End();

		return;
	}

	if (gameOver)
	{
		ImGui::SetNextWindowPos({ (float)screenWidth / 2.0f - 220/2, (float)screenHeight / 2.0f - 50 }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ 220, 100 }, ImGuiCond_Always);
		ImGui::Begin("GameOver!", &showTyper, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove  | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::SetWindowFontScale(2);
			ImGui::Text("You were eaten!");
			if(ImGui::Button("Restart"))
			{
				Reset();
			}
		}
		ImGui::End();
	}
	else {
		ImGui::SetNextWindowPos({ (float)screenWidth / 2.0f - 120 / 2, (float)screenHeight / 2.0f + 50 }, ImGuiCond_Always);
		ImGui::SetNextWindowSize({ 120, 45 }, ImGuiCond_Always);
		ImGui::SetNextWindowBgAlpha(0.0f);
		ImGui::Begin("Typer", &showTyper, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
		{
			ImGui::SetWindowFontScale(2);
			ImGui::TextColored({ 0,0,0,1 }, textToType.c_str());
		}
		ImGui::End();
	}

	ImGui::SetNextWindowPos({0, 0}, ImGuiCond_Always);
	ImGui::SetNextWindowSize({ 200, 45 }, ImGuiCond_Always);
	ImGui::SetNextWindowBgAlpha(0.0f);
	ImGui::Begin("Score", &showTyper, ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
	{
		ImGui::SetWindowFontScale(2);
		ImGui::TextColored({ 0,0,0,1 }, ("Score: " + std::to_string(score)).c_str());
	}
	ImGui::End();
}

void Game::Input()
{
	if (InputManager::GetKeyDown(MapCharToKey(textToType[0])))
	{
		textToType.erase(0, 1);
		textToType.push_back(possibleChars[rand() % possibleChars.size()]);
		speed += 5;
		score += 1;
	}

	if (speed >= 20)
		speed = 20;
}

int Game::MapCharToKey(const char character)
{
	switch (character)
	{
	case 'a':
		return GLFW_KEY_A;
	case 'b':
		return GLFW_KEY_B;
	case 'c':
		return GLFW_KEY_C;
	case 'd':
		return GLFW_KEY_D;
	case 'e':
		return GLFW_KEY_E;
	case 'f':
		return GLFW_KEY_F;
	case 'g':
		return GLFW_KEY_G;
	case 'h':
		return GLFW_KEY_H;
	case 'i':
		return GLFW_KEY_I;
	case 'j':
		return GLFW_KEY_J;
	case 'k':
		return GLFW_KEY_K;
	case 'l':
		return GLFW_KEY_L;
	case 'm':
		return GLFW_KEY_M;
	case 'n':
		return GLFW_KEY_N;
	case 'o':
		return GLFW_KEY_O;
	case 'p':
		return GLFW_KEY_P;
	case 'q':
		return GLFW_KEY_Q;
	case 'r':
		return GLFW_KEY_R;
	case 's':
		return GLFW_KEY_S;
	case 't':
		return GLFW_KEY_T;
	case 'u':
		return GLFW_KEY_U;
	case 'v':
		return GLFW_KEY_V;
	case 'w':
		return GLFW_KEY_W;
	case 'x':
		return GLFW_KEY_X;
	case 'y':
		return GLFW_KEY_Y;
	case 'z':
		return GLFW_KEY_Z;
	case ' ':
		return GLFW_KEY_SPACE;
	}
	return -1;
}
