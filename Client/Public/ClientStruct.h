#pragma once
#include <vector>

namespace Client
{
	struct TSkillInfo
	{
		std::vector<float> m_vecDamages;
		std::vector<float> m_vecAdditionalDamages;
		std::vector<float> m_vecDefenseBoost;
		std::vector<float> m_vecMoveSpeedBoost;
		std::vector<float> m_vecStamina;
		std::vector<float> m_vecCoolDown;
	};
}