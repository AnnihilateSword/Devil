#pragma once

#include "Event.h"

namespace Devil
{
	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(unsigned int button)
			: m_Button(button) {}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	public:
		inline unsigned int GetMouseButton() const { return m_Button; }

	protected:
		unsigned int m_Button{};
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(unsigned int button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "[MouseButtonPressedEvent]: " << m_Button << std::endl;;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(unsigned int button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "[MouseButtonReleasedEvent]: " << m_Button << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y, WPARAM wparam)
			:m_MouseX(x), m_MouseY(y), m_WParam(wparam) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "[MouseMovedEvent]: " << m_MouseX << ", " << m_MouseY << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	public:
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
		inline WPARAM GetWParam() const { return m_WParam; }

	private:
		float m_MouseX{}, m_MouseY{};
		WPARAM m_WParam{};
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "[MouseScrolledEvent]: " << GetXOffset() << ", " << GetYOffset() << std::endl;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	public:
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

	private:
		float m_XOffset{}, m_YOffset{};
	};

}