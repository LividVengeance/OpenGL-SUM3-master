#include "CPlayScene.h"

CPlayScene::CPlayScene(CCamera* _gameCamera, CInput* _gameInput, FMOD::System* _audioSystem)
{
	gameCamera = _gameCamera;
	gameInput = _gameInput;
	audioSystem = _audioSystem;

	// Creates Programs For Objects In Scene
	program = CShaderLoader::CreateProgram("Resources/Shaders/Basic-Normal.vs",
		"Resources/Shaders/Blinn-Phong.fs");

	programSkybox = CShaderLoader::CreateProgram("Resources/Shaders/skybox.vs",
		"Resources/Shaders/skybox.fs");

	// Generate Texte
	const char* fileLocation = "Resources/Textures/BackgroundSprite.png";
	TextureGen(fileLocation, &actorTex);

	// Creates Mesh
	actorPyramid = new CPyramid();

	// Create Game Actors
	gameActor = new CActor(&program, actorPyramid->GetVAO(), actorPyramid->GetIndiceCount(), gameCamera, &actorTex, audioSystem);

	// Create Skybox
	gameSkybox = new CSkybox(&programSkybox, gameCamera);
}

CPlayScene::~CPlayScene()
{
}

void CPlayScene::Render()
{
	glUseProgram(program);

	gameActor->Render();
	gameSkybox->Render();

	glBindVertexArray(0);		// Unbinding VAO
	glUseProgram(0);
}

void CPlayScene::Update(GLfloat* deltaTime, ESceneManager* _currentScene)
{
	currentScene = _currentScene;
	gameCamera->Update(*deltaTime);

	gameSkybox->Update();

	if (gameInput->getKeyState('p') || gameInput->getKeyState('P') || gameInput->getClick(0))
	{
		gameCamera->MoveCamera(*deltaTime, 1);
	}
	if (gameInput->getKeyState('o') || gameInput->getKeyState('O') || gameInput->getClick(1))
	{
		gameCamera->MoveCamera(*deltaTime, 0);
	}
	if (gameInput->getKeyState('l') || gameInput->getKeyState('L'))
	{
		gameCamera->CameraRadius(0.01);
	}
	if (gameInput->getKeyState('k') || gameInput->getKeyState('K'))
	{
		gameCamera->CameraRadius(-0.01);
	}

	gameActor->Update();
}

void CPlayScene::TextureGen(const char* textureLocation, GLuint* texture)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	int width, height;
	unsigned char* image1 = SOIL_load_image(textureLocation, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}