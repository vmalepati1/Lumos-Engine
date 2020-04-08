#pragma once

#include "Event.h"
#include "Maths/Vec2.h"

namespace lumos {

	namespace events {

		class LS_API MouseButtonEvent : public Event
		{

		public:
			inline const int32 GetButton() const { return m_button; }
			inline const float GetX() const { return m_position.x; }
			inline const float GetY() const { return m_position.y; }
			inline const maths::Vec2& GetPosition() const { return m_position; }

			inline static int32 GetStaticType() { return (int32)Event::Type::MOUSE_PRESSED | (int32)Event::Type::MOUSE_RELEASED; }

		protected:

			int32 m_button;
			maths::Vec2 m_position;

		protected:

			MouseButtonEvent(int32 button, float x, float y, Event::Type type);
		};

		class LS_API MousePressedEvent : public MouseButtonEvent
		{
		public:
			MousePressedEvent(int32 button, float x, float y);

			String ToString() const override;

			inline static Type GetStaticType() { return Event::Type::MOUSE_PRESSED; }
		};

		class LS_API MouseReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseReleasedEvent(int32 button, float x, float y);

			inline static Type GetStaticType() { return Event::Type::MOUSE_RELEASED; }
		};

		class LS_API MouseMovedEvent : public Event
		{
		public:

			MouseMovedEvent(float x, float y, bool dragged);

			inline const float GetX() const { return m_position.x; }
			inline const float GetY() const { return m_position.y; }
			inline const maths::Vec2& GetPosition() const { return m_position; }
			inline const bool IsDragged() const { return m_dragged; }

			inline static Type GetStaticType() { return Event::Type::MOUSE_MOVED; }

		private:

			maths::Vec2 m_position;
			bool m_dragged;
		};

	}

}