//External includes
#include "SDL.h"
#include "SDL_surface.h"

//Project includes
#include "ERenderer.h"
#include "ERGBColor.h"
#include "Ray.h"
#include "HitRecord.h"
#include "Sphere.h"
#include "Plane.h"
#include "SceneManager.h"
#include "CameraManager.h"
Elite::Renderer::Renderer(SDL_Window* pWindow)
	: m_RenderMode{ RenderMode::Combined }
{
	//Initialize
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
}

void Elite::Renderer::Render()
{
	//variables
	const std::vector<Object*>&  sceneObjects = SceneManager::GetInstance()->GetActiveScene()->GetObjectsInScene();
	const std::vector<Light*>& sceneLights = SceneManager::GetInstance()->GetActiveScene()->GetLightsInScene();
	const int nrOfObjects = int(sceneObjects.size());
	const int nrOfLights = int(sceneLights.size());

	const float FOV = CameraManager::GetInstance()->GetCamera(0)->GetFOV();
	const float aspectRatio = float(m_Width) / float(m_Height);
	const Elite::FMatrix4 ONB = CameraManager::GetInstance()->GetCamera(0)->GetONB();
	const Elite::FPoint3 cameraPos{ ONB[3].xyz };

	for (Object* pObj : sceneObjects)
	{
		pObj->Rotate();
	}

	SDL_LockSurface(m_pBackBuffer);

	//Loop over all the pixels
#pragma omp parallel for			//just for making it a bit faster because I don't know how to do multithreading myself yet
	for (int32_t r = 0; r < int(m_Height); ++r)
	{
		HitRecord hitRecord{};
		Ray ray{};
		const float yss = (1 - 2 * ((r + 0.5f) / m_Height)) * FOV;
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			//reset the screen
			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(0),
				static_cast<uint8_t>(0),
				static_cast<uint8_t>(0));

			//do the raytracing
			const float xss = (2 * ((c + 0.5f) / m_Width) - 1) * aspectRatio * FOV;
			const Elite::FPoint4 samplePos{ ONB * Elite::FPoint4{xss,yss,-1.f,1.f} };
			ray.origin = samplePos.xyz;
			ray.direction = { ray.origin - cameraPos };
			Elite::Normalize(ray.direction);
			Elite::RGBColor finalPixelColor{};
			Object* pClosestObj{ nullptr };

			for (Object* pObj : sceneObjects)
			{
				if (pObj->Hit(ray, hitRecord))
				{
					pClosestObj = pObj;
				}
			}
			for (Light* pLight : sceneLights)
			{
				//check if the light hits the pixel
				bool isVisible{ true };
				const Elite::FVector3 lightVec = pLight->GetLightVector(hitRecord.hitPoint);
				const float lightVecLen = Elite::Magnitude(lightVec);
				const Elite::FVector3 lightDir = lightVec / lightVecLen;
				if (m_IsHardshadowsEnables)
				{
					for (Object* pObj2 : sceneObjects)
					{
						const Ray lightRay{ hitRecord.hitPoint , lightDir, 0.00001f,lightVecLen };
						HitRecord lightHitRecord{};
						if (pObj2->Hit(lightRay, lightHitRecord, true))
						{
							isVisible = false;
							break;
						}
					}
				}
				const float lambertCos = Elite::Dot(hitRecord.normal, lightDir);

				//check if object is in view
				if (isVisible && lambertCos > 0)
				{
					const Elite::RGBColor ergb = pLight->CalculateIrradiance(hitRecord.hitPoint);
					Elite::RGBColor materialShade{};
					if(pClosestObj!=nullptr) materialShade = pClosestObj->GetMaterial()->Shade(hitRecord, lightDir, -ray.direction);
					switch (m_RenderMode)
					{
					case Elite::Renderer::RenderMode::Combined:
						finalPixelColor += ergb * materialShade * lambertCos;
						break;
					case Elite::Renderer::RenderMode::Ergb:
						finalPixelColor += ergb * lambertCos;
						break;
					case Elite::Renderer::RenderMode::BRDF:
						finalPixelColor += materialShade * lambertCos;
						break;
					default:
						break;
					}
				}
			}
			hitRecord.tValue = FLT_MAX;

			finalPixelColor.MaxToOne();		//tonemapping is a better method, maybe look into that later
			//Color the pixels
			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(finalPixelColor.r * 255),
				static_cast<uint8_t>(finalPixelColor.g * 255),
				static_cast<uint8_t>(finalPixelColor.b * 255));
		}
	}
	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

void Elite::Renderer::ToggleHardshadows()
{
	m_IsHardshadowsEnables = !m_IsHardshadowsEnables;
}

void Elite::Renderer::ToggleRenderMode()
{
	m_RenderMode = RenderMode((int(m_RenderMode) + 1) % int(RenderMode::NrOfModes));
}
