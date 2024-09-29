#include <Core/EntryPoint.h>

#include <Platform/D3D11/Drawable/D3D11Box.h>
#include <Platform/D3D11/Drawable/D3D11Sphere.h>
#include <Platform/D3D11/Drawable/D3D11Plane.h>

#include <Vendor/ImGui/imgui.h>

using namespace Devil;
using namespace DirectX;

class ProvingGround : public Application
{
public:
	ProvingGround()
	{
		/*********/
		/** TEST */
		/*********/

		/** Init Window */
		m_Window = std::make_unique<Window>();
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		/** Init Camera */
		m_Camera = std::make_unique<Camera>();


		/** Init Entity */
		m_Plane = std::make_unique<D3D11Plane>(m_Window->GetRenderer(), XMFLOAT3(0.0f, -3.0f, 0.0f));
		m_Box = std::make_unique<D3D11Box>(m_Window->GetRenderer(), XMFLOAT3(2.2, 0.0f, 0.0f));
		m_Sphere = std::make_unique<D3D11Sphere>(m_Window->GetRenderer(), XMFLOAT3(-2.2, 0.0f, 0.0f));

		m_Window->GetRenderer().SetProjection(DirectX::XMMatrixPerspectiveFovLH(45.0f, 
			(float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.5f, 40.0f));
	}

	virtual ~ProvingGround()
	{
	}

	virtual void DoFrame() override
	{
		// [Get Delta Time]
		float deltaTime = m_Timer.DeltaTime();


		/******************************/
		/** Update && Draw && Present */
		/******************************/
		m_Window->GetRenderer().BeginFrame(0.0f, 0.0f, 0.0f);

		// update camera view matrix
		m_Window->GetRenderer().SetCameraMatrix(m_Camera->GetViewMatrix());
		
		m_Plane->Update(deltaTime);
		m_Plane->Draw(m_Window->GetRenderer());

		static float BoxPitch = 0;
		static float BoxYaw = 0;
		//pitch += 0.6f * deltaTime;
		//yaw += 1.2f * deltaTime;
		m_Box->SetRotationDegree(XMFLOAT3(BoxPitch, BoxYaw, 0.0f));
		m_Box->Update(deltaTime);
		m_Box->Draw(m_Window->GetRenderer());

		m_Sphere->Update(deltaTime);
		m_Sphere->Draw(m_Window->GetRenderer());


		/****************/
		/** ImGui Layer */
		/****************/
		if (ImGui::Begin("Performance Profiler"))
		{
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//ImGui::Text("Debug: ( %f, %f ), Button: %d", ImGui::GetMousePos().x, ImGui::GetMousePos().y, ImGui::IsMouseDown(0));
		}
		ImGui::End();
		// Box Controll window.
		if (ImGui::Begin("Box Control panel"))
		{
			ImGui::SliderFloat("BoxPitch", &BoxPitch, -180.0f, 180.0f);
			ImGui::SliderFloat("BoxYaw", &BoxYaw, -89.0f, 89.0f);
			if (ImGui::Button("Reset"))
			{
				BoxPitch = 0.0f;
				BoxYaw = 0.0f;
			}
		}
		ImGui::End();
		// camera imgui controll window.
		m_Camera->SpawnControllWindow();

		m_Window->GetRenderer().EndFrame();
	}

protected:
	// Entity
	std::unique_ptr<D3D11Plane> m_Plane{};
	std::unique_ptr<D3D11Box> m_Box{};
	std::unique_ptr<D3D11Sphere> m_Sphere{};
};




/***********************/
/** Create Application */
/***********************/
Devil::Application* Devil::CreateApplication()
{
	return new ProvingGround();
}