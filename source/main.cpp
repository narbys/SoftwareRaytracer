//External includes
#include "vld.h"
#include "SDL.h"
#include "SDL_surface.h"
#undef main

//Standard includes
#include <iostream>

//Project includes
#include "ETimer.h"
#include "ERenderer.h"
#include "SceneManager.h"
#include "Sphere.h"
#include "Plane.h"
#include "CameraManager.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Material_Lambert.h"
#include "Material_LambertPhong.h"
#include "Material_CookTorrance.h"
#include "MaterialManager.h"
#include "Triangle.h"
#include "TriangleMesh.h"
#include "OBJReader.h"

#define SCENEMANAGER SceneManager::GetInstance()
#define SCENE(i) SceneManager::GetInstance()->GetScene(i)
#define MATERIALMANAGER MaterialManager::GetInstance()

void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

void Init()
{
	//print controls
	std::cout << "Controls:\nArrows to change scene\nWASD for translation\nRight mousebutton for rotation\nLeft mousebutton for forward and backward translation\nBoth mousebuttons for up and down translation\n"
		<<"J: toggle directional light in 1st scene\nK-L: toggle the pointlights in 1st scene\nZ: toggle hard shadows in 1st scene\nT: toggle Irradiance only, BRDF only or all combined\n";

	//Materials	
	Material* pLambertGray = MATERIALMANAGER->AddMaterial(new Material_Lambert{ 0.5f,Elite::RGBColor{0.3f,0.3f,0.3f} });
	Material* pLambertRed = MATERIALMANAGER->AddMaterial(new Material_Lambert{ 0.5f,Elite::RGBColor{1.f,0.89f,0.95f} });
	Material* pLambertPhong_LightGreen = MATERIALMANAGER->AddMaterial(new Material_LambertPhong{ 1.f, Elite::RGBColor(0.69f, 0.98f, 0.25f), 1.f,60 });
	Material* pLambertPhong_White = MATERIALMANAGER->AddMaterial(new Material_LambertPhong{ 1.f, Elite::RGBColor(1.f,1.f,1.f),1.f,60 });

	Material* pCookTor_NonmetalRough = MATERIALMANAGER->AddMaterial(new Material_CookTorrance{ Elite::RGBColor(0.972f, 0.96f, 0.915f), false, 1.f/*Dont put roughness on 0*/, 1.f, 1.f});
	Material* pCookTor_NonmetalHalfRough = MATERIALMANAGER->AddMaterial(new Material_CookTorrance{ Elite::RGBColor(0.972f, 0.96f, 0.915f), false, 0.6f/*Dont put roughness on 0*/, 1.f, 1.f });
	Material* pCookTor_NonmetalNotRough = MATERIALMANAGER->AddMaterial(new Material_CookTorrance{ Elite::RGBColor(0.972f, 0.96f, 0.915f), false, 0.1f/*Dont put roughness on 0*/, 1.f, 1.f});
	Material* pCookTor_MetalRough = MATERIALMANAGER->AddMaterial(new Material_CookTorrance{ Elite::RGBColor(0.972f, 0.96f, 0.915f), true, 1.f/*Dont put roughness on 0*/, 1.f, 1.f});
	Material* pCookTor_MetalHalfRough = MATERIALMANAGER->AddMaterial(new Material_CookTorrance{ Elite::RGBColor(0.972f, 0.96f, 0.915f), true, 0.6f/*Dont put roughness on 0*/, 1.f, 1.f});
	Material* pCookTor_MetalNotRough = MATERIALMANAGER->AddMaterial(new Material_CookTorrance{ Elite::RGBColor(0.972f, 0.96f, 0.915f), true, 0.1f/*Dont put roughness on 0*/, 1.f, 1.f});

	//initialise the scene and the camera
	CameraManager::GetInstance()->AddCamera(new Camera(Elite::FPoint4(0.f,3.f,10.f,1.f)));
	SCENEMANAGER->AddScene(new Scene());

	//Objects in the scene
	//the planes
	SCENE(0)->AddObject(new Plane(Elite::FPoint3(0.f, 0.f, 0.f),pLambertGray , Elite::FVector3(0.f, 1.f, 0.f)));
	SCENE(0)->AddObject(new Plane(Elite::FPoint3(0.f, 0.f, -6.f), pLambertGray, Elite::FVector3(0.f, 0.f, 1.f)));
	SCENE(0)->AddObject(new Plane(Elite::FPoint3(-6.f, 0.f, 0.f), pLambertGray, Elite::FVector3(1.f, 0.f, 0.f)));
	SCENE(0)->AddObject(new Plane(Elite::FPoint3(6.f, 0.f, 0.f), pLambertGray, Elite::FVector3(-1.f, 0.f, 0.f)));
	SCENE(0)->AddObject(new Plane(Elite::FPoint3(0.f, 15.f, 0.f), pLambertGray, Elite::FVector3(0.f, -1.f, 0.f)));

	//the balls
	SCENE(0)->AddObject(new Sphere(Elite::FPoint3(-2.5f, 1.f, 0.f), pCookTor_NonmetalRough, 1.f));
	SCENE(0)->AddObject(new Sphere(Elite::FPoint3(0.f, 1.f, 0.f), pCookTor_NonmetalHalfRough, 1.f));
	SCENE(0)->AddObject(new Sphere(Elite::FPoint3(2.5f, 1.f, 0.f), pCookTor_NonmetalNotRough, 1.f));
	SCENE(0)->AddObject(new Sphere(Elite::FPoint3(-2.5f, 3.5f, 0.f), pCookTor_MetalRough, 1.f));
	SCENE(0)->AddObject(new Sphere(Elite::FPoint3(0.f, 3.5f, 0.f), pCookTor_MetalHalfRough, 1.f));
	SCENE(0)->AddObject(new Sphere(Elite::FPoint3(2.5f, 3.5f, 0.f), pCookTor_MetalNotRough, 1.f));

	//triangles
	SCENE(0)->AddObject(new Triangle({ 0.f, 6.f, 0.f }, { -0.75f, 1.5f, 0.f }, { -0.75f, 0.f, 0.f }, { 0.75f, 0.f, 0.f }, Cullmode::backfaceCulling, pLambertGray));
	SCENE(0)->AddObject(new Triangle({ -2.5f,6.f,0.f }, { -0.75f, 1.5f, 0.f }, { -0.75f, 0.f, 0.f }, { 0.75f, 0.f, 0.f }, Cullmode::noCulling, pLambertGray));
	SCENE(0)->AddObject(new Triangle({ 2.5f,6.f,0.f }, { -0.75f, 1.5f, 0.f }, { -0.75f, 0.f, 0.f }, { 0.75f, 0.f, 0.f }, Cullmode::frontfaceCulling, pLambertGray));

	//the lights
	SCENE(0)->AddLight(new PointLight(Elite::FPoint3(0, 7.f, -2.5f), Elite::RGBColor(1, 0.7f, 1), 60.f));
	SCENE(0)->AddLight(new PointLight(Elite::FPoint3(0.f, 2.5f, 5.f), Elite::RGBColor(0.7f, 1, 1), 60.f));
	SCENE(0)->AddLight(new DirectionalLight(Elite::FVector3(0.f, 1.f, 0.7f), Elite::RGBColor(1, 1, 1), 0.7f));

	//scene 1
	SCENEMANAGER->AddScene(new Scene());

	//objects
	SCENE(1)->AddObject(new Plane(Elite::FPoint3(0.f, 0.f, 0.f), pLambertGray, Elite::FVector3(0.f, 1.f, 0.f)));
	SCENE(1)->AddObject(new Sphere(Elite::FPoint3(0.f, 1.f, 0.f), pLambertPhong_LightGreen, 1.f));
	SCENE(1)->AddObject(new TriangleMesh({ 0.f,4.f,0.f }, std::vector<Elite::FPoint3>{ {-0.75f, 1.5f, 0}, { -0.75f, 0, 0 }, { 0.75f, 0, 0 }, { 0.75f, 1.5, -1 } }, std::vector<int>{ 0, 1, 2, 0, 2, 3 }, pLambertGray, Cullmode::noCulling));

	//lights
	SCENE(1)->AddLight(new PointLight(Elite::FPoint3(0, 5.f, -2.5f), Elite::RGBColor(1, 1, 1), 50.f));
	SCENE(1)->AddLight(new PointLight(Elite::FPoint3(0.f, 2.5f, 5.f), Elite::RGBColor(1, 1, 1), 50.f));

	//scene2
	SCENEMANAGER->AddScene(new Scene());

	//objects
	SCENE(2)->AddObject(new Plane(Elite::FPoint3(0.f, 0.f, 0.f), pLambertGray, Elite::FVector3(0.f, 1.f, 0.f)));
	SCENE(2)->AddObject(new Plane(Elite::FPoint3(0.f, 0.f, -6.f), pLambertGray, Elite::FVector3(0.f, 0.f, 1.f)));
	SCENE(2)->AddObject(OBJReader::ParseObj(Elite::FPoint3(0.f, 2.f, 0.f),"lowpoly_bunny.obj", pLambertPhong_White, Cullmode::noCulling));

	//lights
	SCENE(2)->AddLight(new DirectionalLight(Elite::FVector3(0.f, 1.f, 0.7f), Elite::RGBColor(1, 1, 1), 5.f));
	SCENE(2)->AddLight(new PointLight(Elite::FPoint3(0, 2.f, 3.25f), Elite::RGBColor(1, 1, 1), 50.f));
	SCENE(2)->AddLight(new PointLight(Elite::FPoint3(0.f, 5.f, 0.f), Elite::RGBColor(1, 1, 1), 50.f));
}

void Cleanup()
{
	CameraManager::GetInstance()->Cleanup();								
	SCENEMANAGER->Cleanup();
	MATERIALMANAGER->Cleanup();
}
void Update(float deltaTime)
{
	CameraManager::GetInstance()->GetCamera(0)->Update(deltaTime);
}

int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;

	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 640;
	const uint32_t height = 480;
	SDL_Window* pWindow = SDL_CreateWindow(
		"RayTracer - **Sybran Aerts**",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize "framework"
	Elite::Timer* pTimer = new Elite::Timer();
	Elite::Renderer* pRenderer = new Elite::Renderer(pWindow);

	//Initialize objects
	Init();

	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	bool takeScreenshot = false;
	while (isLooping)
	{
		//--------- Get input events ---------
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isLooping = false;
				break;
			case SDL_KEYUP:
				if(e.key.keysym.scancode == SDL_SCANCODE_X)
					takeScreenshot = true;
				if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
					SCENEMANAGER->NextScene();
				if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
					SCENEMANAGER->PreviousScene();
				//Light toggles, only for scene 0 and is hardcoded (very ew)
				if (e.key.keysym.scancode == SDL_SCANCODE_K)
					SCENE(0)->GetLightsInScene()[0]->Toggle();
				if (e.key.keysym.scancode == SDL_SCANCODE_L)
					SCENE(0)->GetLightsInScene()[1]->Toggle();
				if (e.key.keysym.scancode == SDL_SCANCODE_J)
					SCENE(0)->GetLightsInScene()[2]->Toggle();
				//Rendering roggles
				if (e.key.keysym.scancode == SDL_SCANCODE_Z)
					pRenderer->ToggleHardshadows();
				if (e.key.keysym.scancode == SDL_SCANCODE_T)
					pRenderer->ToggleRenderMode();
				break;
			}
		}
		//--------- Update ---------
		Update(pTimer->GetElapsed());

		//--------- Render ---------
		pRenderer->Render();

		//--------- Timer ---------
		pTimer->Update();
		printTimer += pTimer->GetElapsed();
		if (printTimer >= 1.f)
		{
			printTimer = 0.f;
			std::cout << "FPS: " << pTimer->GetFPS() << std::endl;
		}

		//Save screenshot after full render
		if (takeScreenshot)
		{
			if (!pRenderer->SaveBackbufferToImage())
				std::cout << "Screenshot saved!" << std::endl;
			else
				std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
			takeScreenshot = false;
		}
	}
	pTimer->Stop();

	//Shutdown "framework"
	delete pRenderer;
	delete pTimer;

	//Cleaning up my singletons
	Cleanup();

	ShutDown(pWindow);
	return 0;
}