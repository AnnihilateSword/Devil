#pragma once

#include <DirectXMath.h>

#include "Platform/D3D11/D3D11Renderer.h"
#include "Platform/D3D11/Bindable/D3D11IndexBuffer.h"

class D3D11Bindable;

namespace Devil
{
	class D3D11Drawable
	{
	public:
		template<class T>
		friend class D3D11DrawableBase;
	public:
		D3D11Drawable() = default;
		virtual ~D3D11Drawable() = default;
		D3D11Drawable(const D3D11Drawable&) = delete;
		D3D11Drawable& operator=(const D3D11Drawable&) = delete;

	public:
		virtual void Draw(D3D11Renderer& renderer) const noexcept;
		virtual void Update(float deltaTime) noexcept {}
		virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;

	public:
		void AddBind(std::unique_ptr<D3D11Bindable> bind) noexcept;
		void AddIndexBuffer(std::unique_ptr<D3D11IndexBuffer> indexBuffer) noexcept;


		/***********************************************************************************************************/
		/** Memory is released at the end of each frame to illuminate objects in the scene to prevent memory leaks */
		/***********************************************************************************************************/
		void AddBindAndCleanupFrame(std::unique_ptr<D3D11Bindable> bind) noexcept;
		void CleanupFrameBinds() noexcept;

	protected:
		virtual const std::vector<std::unique_ptr<D3D11Bindable>>& GetStaticBinds() const noexcept = 0;

	protected:
		const D3D11IndexBuffer* m_IndexBuffer{ nullptr };
		std::vector<std::unique_ptr<D3D11Bindable>> m_Binds{};
		std::vector<std::unique_ptr<D3D11Bindable>> m_BindsCleanupFrame{};
	};
}