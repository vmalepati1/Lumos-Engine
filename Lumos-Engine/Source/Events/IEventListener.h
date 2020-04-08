#pragma once

#include "Event.h"

namespace lumos {

	namespace events {

		class LS_API IEventListener
		{
		public:
			virtual void OnEvent(Event& event) = 0;
		};

	}
}