#include "ls.h"

#include "WindowEvent.h"

namespace lumos {
	
	namespace events {

		ResizeWindowEvent::ResizeWindowEvent(uint width, uint height)
			: Event(ResizeWindowEvent::GetStaticType()), m_size(maths::TVec2<uint>(width, height))
		{
		}

	}

}