#pragma once

#include "ls.h"

#include "Core/String.h"

namespace lumos {

	namespace events {

#undef MOUSE_PRESSED
#undef MOUSE_RELEASED
#undef MOUSE_MOVED
#undef KEY_PRESSED
#undef KEY_RELEASED

		class LS_API Event {
		public:

			enum class Type {
				KEY_PRESSED = BIT(0),
				KEY_RELEASED = BIT(1),

				MOUSE_PRESSED = BIT(2),
				MOUSE_RELEASED = BIT(3),
				MOUSE_MOVED = BIT(4),

				WINDOW_RESIZE = BIT(5)
			};

		public:

			inline Type GetType() const { return m_type; }
			inline bool IsHandled() const { return m_handled; }

			virtual String ToString() const;

			static String TypeToString(Type type);

		protected:

			Event(Type type);

		protected:

			bool m_handled;
			Type m_type;

		private:

			friend class EventDispatcher;
		};

	}

}