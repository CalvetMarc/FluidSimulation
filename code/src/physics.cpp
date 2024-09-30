#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdl_gl3.h>
#include <cstdio>
#include "AA5.h"

using namespace AA5;

#pragma region simulationSelection
enum class EnabledSimulation {
	AA5_Fluids,
};

Simulator* currentSimulator;
EnabledSimulation currentSimulation;
void setSimulation(EnabledSimulation simulation) {
	if (currentSimulation == simulation) {
		return;
	}

	delete currentSimulator;
	currentSimulation = simulation;
	switch (simulation) {
		case EnabledSimulation::AA5_Fluids:
			printf("AA5 Fluids");
			
			currentSimulator = new FluidSimulator();
			break;
		;;
	}
}
#pragma endregion

#pragma region GUI
bool show_test_window = false;
void GUI() {
	bool show = true;
	
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Mecanica")) {
			if (ImGui::MenuItem("AA5 Fluids")) { setSimulation(EnabledSimulation::AA5_Fluids); };

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	ImGui::Begin("Physics Parameters", &show, 0);
	{	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);//FrameRate
		
		currentSimulator->RenderGui();

		
	}
	
	ImGui::End();
}

#pragma endregion


void PhysicsInit() {
	// The default simulation
	currentSimulator = new FluidSimulator();
}

void PhysicsUpdate(float dt) {
	currentSimulator->Update(dt);
	currentSimulator->RenderUpdate();
}

void PhysicsCleanup() {
	delete currentSimulator;
}