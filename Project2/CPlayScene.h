#pragma once
#include "CShaderLoader.h"
#include "CCamera.h"
#include "CInput.h"
#include "CTextLabel.h"

#include "CActorEnemy.h"
#include "CActor.h"
#include "CActorPickupHealth.h"
#include "CActorPickupScore.h"

#include "CActorEnemyManager.h"

#include "CPyramid.h"
#include "CSphere.h"
#include "CSkybox.h"
#include "Model.h"

class CPlayScene
{
public:
	CPlayScene(CCamera* _gameCamera, CInput* _gameInput, FMOD::System* _audioSystem);
	~CPlayScene();

	void Render();
	void Update(GLfloat* deltaTime, ESceneManager* _currentScene);

private:
	void TextureGen(const char* textureLocation, GLuint* texture);

	// Programs
	GLint program;
	GLint programSkybox;

	// Audio
	FMOD::System* audioSystem;

	// Utilities
	ESceneManager* currentScene;
	CCamera* gameCamera;
	CInput* gameInput;

	CPyramid* actorPyramid;

	CActor* gameActor;
	CSkybox* gameSkybox;

	// Textures
	GLuint actorTex;
};