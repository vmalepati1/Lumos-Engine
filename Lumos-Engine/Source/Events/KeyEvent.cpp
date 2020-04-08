#include "ls.h"

#include "KeyEvent.h"

namespace lumos {

	namespace events {

		KeyEvent::KeyEvent(int32 keyCode, Event::Type type)
			: Event(type), m_keyCode(keyCode)
		{
		}

		KeyPressedEvent::KeyPressedEvent(int32 button, int32 repeat, int32 modifiers)
			: KeyEvent(button, KeyPressedEvent::GetStaticType()), m_repeat(repeat), m_modifiers(modifiers)
		{
		}

		KeyReleasedEvent::KeyReleasedEvent(int32 button)
			: KeyEvent(button, KeyReleasedEvent::GetStaticType())
		{
		}

	}

}