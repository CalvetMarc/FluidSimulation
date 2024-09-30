#pragma once
#include "Simulator.h"
#include <vector>
#include <glm/glm.hpp>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
extern bool renderCloth;
namespace ClothMesh {
	extern void updateClothMesh(float* array_data);
	extern const int numCols;
	extern const int numRows;
};
extern bool renderSphere;
namespace Sphere
{
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
}
namespace AA5 {
	class Wave {
	public:
		Wave(float maxA,float maxOmega,float maxLanda)
		{
			float ka = 0;
			do
			{
				direction = glm::normalize(glm::vec3(RandomNumber(-1, 1), 0, RandomNumber(-1, 1)));
				amplitude = RandomNumber(0.1,maxA);
				omega = RandomNumber(3,maxOmega);
				fase = 0;
				wavelength = RandomNumber(0.75f, maxLanda);
				k = 2.f * 3.1416f / wavelength;
				ka = k * amplitude;

			} while (ka > 1 && ka < 0);
		}
		glm::vec3 GetPositionAtTime(glm::vec3 initialPosition, float time);
		float RandomNumber(float Min, float Max)
		{
			return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
		}
	public:
		glm::vec3 direction;
		float amplitude;
		float omega;
		float fase;
		float wavelength;
		float k;
	};

	class SphereObject {
	public:
		SphereObject()
		{
			position = glm::vec3(0,5,0);
			radius = 1;
			density = 0.6f;
		}
		glm::vec3 position;
		float radius;
		float density;
		void Update(float dt);
		float RandomNumber(float Min, float Max)
		{
			return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
		}
		glm::vec3 GetPosition() { return position; }
		float GetRadius() { return radius; }
		float GetDensity() { return density; }

		void SetPosition(glm::vec3 _pos) { position = _pos; }
		void SetRadius(float _radius) { radius = _radius; }
		void SetDensity(float _density) { density = _density; }
	};

	class FluidSimulator : public Simulator {
	public:
		float maxA = 0.3f;
		float maxLanda = 1;
		float maxOmega = 8;
		int numWaves = 5;
		FluidSimulator()
		{
			renderSphere = true;
			sphere = SphereObject();
			for (size_t i = 0; i < numWaves; i++)
			{
				waves.push_back(Wave(maxA, maxOmega, maxLanda));
			}
			width = ClothMesh::numCols;
			heigth = ClothMesh::numRows;
			size = width * heigth;
			positions = new glm::vec3[size];
			Oldpositions = new glm::vec3[size];
			SetInitPositions();
		}
		void Update(float dt);
		void RenderUpdate();
		void RenderGui();
		int GetIndex(int x, int y);
		int width;
		int heigth;
		float currentTime;
		int size;
	private:
		glm::vec3* positions;
		glm::vec3* Oldpositions;
		glm::vec3* allWavesPositions;
		float GetSphereSubmergedVolume();
		void SetInitPositions();
		void CalculateWavesPositions();
		void SafePositions();
		std::vector<Wave> waves;
		SphereObject sphere;
	};
}