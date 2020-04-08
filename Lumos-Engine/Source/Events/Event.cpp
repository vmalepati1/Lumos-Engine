#include "ls.h"

#include "Event.h"

namespace lumos {

	namespace events {

		Event::Event(Type type)
			: m_type(type), m_handled(false)
		{
		}

		String Event::ToString() const
		{
			return "Event: ";
		}

		String Event::TypeToString(Type type)
		{
			switch (type)
			{
			case Type::KEY_PRESSED:
				return "KEY_PRESSED";
			case Type::KEY_RELEASED:
				return "KEY_RELEASED";
			case Type::MOUSE_PRESSED:
				return "MOUSE_PRESSED";
			case Type::MOUSE_RELEASED:
				return "MOUSE_RELEASED";
			case Type::MOUSE_MOVED:
				return "MOUSE_MOVED";
			}
			return "INVALID";
		}

	}

}