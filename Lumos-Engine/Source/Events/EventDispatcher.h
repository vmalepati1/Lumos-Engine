#pragma once

#include "ls.h"
#include "Event.h"

namespace lumos {

	namespace events {

		class LS_API EventDispatcher {
		public:

			EventDispatcher(Event &event) 
				: m_event(event) {

			}

			template<typename T>
			void Dispatch(std::function<bool(T&)> func)
			{
				if ((int32)m_event.GetType() & (int32)T::GetStaticType())
					m_event.m_handled = func(*(T*)&m_event);
			}
		private:
			Event &m_event;
		};

	}
}