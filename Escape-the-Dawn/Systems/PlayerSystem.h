#ifndef PlayerSystem_h__
#define PlayerSystem_h__

#include <array>

#include "System.h"
#include "Systems/SoundSystem.h"
#include "Components/Transform.h"
#include "Components/Input.h"
#include "Components/Collision.h"
#include "Components/Camera.h"
#include "Components/Bounds.h"
#include "Components/PowerUp.h"
#include "Components/PointLight.h"
#include "Components/SoundEmitter.h"

#include "logging.h"



namespace Systems
{

	class PlayerSystem : public System
	{
	public:
		PlayerSystem(World* world);

		void Update(double dt) override;
		void UpdateEntity(double dt, EntityID entity, EntityID parent) override;

	private:
		float m_PlayerSpeed;
		glm::vec3 m_PlayerOriginalBounds;

		glm::vec3 m_CameraOffset;
		glm::quat m_CameraOrientation;

		bool freecamEnabled;
		
		float m_basespeed;
		float m_maxspeed;

		float m_PowerUpTotalDuration;
		float m_poweruptimeleft;

		void SetPlayerLightColor(EntityID player, glm::vec3 color);

	};

}

#endif // InputSystem_h__
