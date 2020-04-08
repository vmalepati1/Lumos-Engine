#pragma once

#include "Event.h"
#include "Maths/TVec2.h"

namespace lumos {
	
	namespace events {

		class LS_API ResizeWindowEvent : public Event
		{
		public:

			ResizeWindowEvent(uint width, uint height);

			inline const maths::TVec2<uint>& GetSize() const { return m_size; }
			inline const uint GetWidth() const { return m_size.x; }
			inline const uint GetHeight() const { return m_size.y; }

		public:

			inline static Type GetStaticType() { return Event::Type::WINDOW_RESIZE; }

		protected:

			maths::TVec2<uint> m_size;
		};

	}

}
