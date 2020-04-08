#pragma once

namespace lumos {

	namespace platform {

		struct LS_API Timestep
		{
		private:
			float m_timestep;
			float m_lastTime;
		public:
			inline Timestep(float initialTime)
				: m_timestep(0.0f), m_lastTime(initialTime)
			{
			}

			inline void Update(float currentTime)
			{
				m_timestep = currentTime - m_lastTime;
				m_lastTime = currentTime;
			}

			inline float GetMillis() const { return m_timestep; }
			inline float GetSeconds() const { return m_timestep * 0.001f; }
		};

	}

}