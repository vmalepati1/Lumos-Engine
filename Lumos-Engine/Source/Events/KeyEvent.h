#pragma once

#include "Event.h"

namespace lumos {

	namespace events {

		class LS_API KeyEvent : public Event
		{

		public:
			KeyEvent(int32 keyCode, Event::Type type);

			inline int32 GetKeyCode() const { return m_keyCode; }

			inline static int32 GetStaticType() { return (int32)Event::Type::KEY_PRESSED | (int32)Event::Type::KEY_RELEASED; }

		protected:

			int32 m_keyCode;
			int32 m_Ccount;
		};

	#pragma warning(disable : 4800)
		class LS_API KeyPressedEvent : public KeyEvent
		{

		public:

			KeyPressedEvent(int32 button, int32 repeat, int32 modifiers);

			inline int32 GetRepeat() const { return m_repeat; }
			inline int32 GetModifiers() const { return m_modifiers; }
			inline bool IsModifier(int32 modifier) const { return (bool)(m_modifiers & modifier); }

			inline static Type GetStaticType() { return Event::Type::KEY_PRESSED; }

		private:

			int32 m_repeat;
			int32 m_modifiers;
		};
	#pragma warning(default : 4800)

		class LS_API KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(int32 button);

			inline static Type GetStaticType() { return Event::Type::KEY_RELEASED; }
		};

	}

}
