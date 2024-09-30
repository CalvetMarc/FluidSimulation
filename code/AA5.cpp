#include "AA5.h"
#include <iostream>

bool resetScene = false;

void AA5::FluidSimulator::Update(float dt)
{
	currentTime += dt;
	if (resetScene == true)
	{
		while (waves.size() != 0)
		{
			waves.pop_back();
		}
		
		renderSphere = true;
		sphere = SphereObject();
		for (size_t i = 0; i < numWaves; i++)
		{
			waves.push_back(Wave(maxA, maxOmega, maxLanda));
		}
		/*width = ClothMesh::numCols;
		heigth = ClothMesh::numRows;
		size = width * heigth;
		positions = new glm::vec3[size];
		Oldpositions = new glm::vec3[size];
		SetInitPositions();
		*/	
		resetScene = !resetScene;
	}
	else
	{
		CalculateWavesPositions();
		int size = width * heigth;
		glm::vec3 upPoint;
		float minDistance = 100000;
		for (int y = 0; y < heigth; y++)
		{
			for (int x = 0; x < width; x++)
			{
				positions[GetIndex(x, y)] = Oldpositions[GetIndex(x, y)] - glm::vec3(allWavesPositions[GetIndex(x, y)]);
				float d = glm::abs(positions[GetIndex(x, y)].x - sphere.position.x);
				if (d <= minDistance)
				{
					minDistance = d;
					upPoint = positions[GetIndex(x, y)];
				}
			}
		}
		float h = upPoint.y - sphere.position.y + sphere.radius;
		if (h > 0)
		{
			float calc1 = 1.f / 3.f * 3.1416f;
			float calc2 = 3.f * sphere.radius - h;
			float vs = glm::abs(calc1 * glm::pow(h, 2) * (calc2));
			float flotationForce = 1 * 9.81f * vs * h;
			float A = 3.1416f * glm::pow(sphere.radius, 2);
			float U = 1;
			float dragCoeficent = 0.5f;
			float fricction = -1.f / 2.f * sphere.density * dragCoeficent;
			float force = flotationForce;
			sphere.position.y += force * dt;
		}
		sphere.Update(dt);
	}

	

}
void AA5::FluidSimulator::SetInitPositions()
{
	renderCloth = true;
	currentTime = 0;
	int size = width * heigth;
	float sizeBetweenCellsx = 11/(float)width;
	float sizeBetweenCellz = 11/(float)heigth;
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			glm::vec3 pos = glm::vec3(x * sizeBetweenCellsx, 3, y* sizeBetweenCellz) + glm::vec3(-5, 0, -5);
			positions[GetIndex(x, y)] = pos;
		    //std::cout << "x: " << x << "y: " << 5 << "z: " << y << std::endl;
		}
	}
	SafePositions();
}
void AA5::FluidSimulator::CalculateWavesPositions()
{
	allWavesPositions = new glm::vec3[size];
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			allWavesPositions[GetIndex(x, y)] = glm::vec3(0, 0, 0);
			for (int w = 0; w < waves.size(); w++)
			{
				allWavesPositions[GetIndex(x, y)] += waves[w].GetPositionAtTime(Oldpositions[GetIndex(x, y)], currentTime);
				//waves[w].amplitude *= 0.99999999f;
			}
		}
	}
	
}
void AA5::FluidSimulator::SafePositions()
{
	for (int y = 0; y < heigth; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Oldpositions[GetIndex(x, y)] = glm::vec3(positions[GetIndex(x, y)]);
		}
	}
}
void AA5::FluidSimulator::RenderUpdate()
{
	ClothMesh::updateClothMesh(&(positions[0].x));
}

void AA5::FluidSimulator::RenderGui()
{
	ImGui::InputFloat3(
		"Position",
		&sphere.position.x
	);
	ImGui::InputFloat(
		"Radius",
		&sphere.radius
		);
	ImGui::InputFloat(
		"Density",
		&sphere.density
		);


	ImGui::InputFloat(
		"maxA",
		&maxA
	);
	ImGui::InputFloat(
		"maxLanda",
		&maxLanda
	); 
	ImGui::InputFloat(
		"maxOmega",
		&maxOmega
	);
	ImGui::InputInt(
		"Number Waves",
		&numWaves
	);
	int wavesSize = waves.size();
	ImGui::InputInt(
		"Active Waves ",
		&wavesSize
	);

	if (ImGui::Button("Reset Simulation NOW"))
	{
		resetScene = !resetScene;
	}
	
}

int AA5::FluidSimulator::GetIndex(int x, int y)
{
	int index = y * width + x;
	return index;
}

float AA5::FluidSimulator::GetSphereSubmergedVolume()
{
	return 0.0f;
}

glm::vec3 AA5::Wave::GetPositionAtTime(glm::vec3 initialPosition, float time)
{
	glm::vec3 position = (direction/k) * amplitude * glm::sin(glm::dot(direction, initialPosition) - omega *time + fase);
	position.y = amplitude * glm::cos(glm::dot(direction, initialPosition) - omega * time + fase);
	return position;
}

void AA5::SphereObject::Update(float dt)
{
	position.y -= 9.81f * dt;
	Sphere::updateSphere(position, radius);
}
