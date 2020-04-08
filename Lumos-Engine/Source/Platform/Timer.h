#pragma once

#include "ls.h"

namespace lumos {

	namespace platform {

		struct Members;

		class LS_API Timer {

		public:
			
			/* Creates and starts timer. */

			Timer();

			/* Resets and restarts timer. */

			virtual void Reset();

			/* Returns current time in seconds. */

			virtual float Elapsed();

			/* Returns current time in milliseconds. */

			virtual float ElapsedMillis();

		private:

			byte m_reserved[32];
			Members *m_members;
		};

	}

}