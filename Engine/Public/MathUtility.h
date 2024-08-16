#pragma once

namespace Engine
{
	class CMathUtility
	{
	public:
		static float GetRandomFloat(float _fFrom, float _fTo)
		{
			static std::random_device rd;
			static std::mt19937 generator(rd());
			std::uniform_real_distribution<float> fDistribution(_fFrom, _fTo);

			return fDistribution(generator);
		}

		static int GetRandomInteger(int _iFrom, int _iTo)
		{
			static std::random_device rd;
			static std::mt19937 generator(rd());
			std::uniform_int_distribution<int> iDistribution(_iFrom, _iTo);

			return iDistribution(generator);
		}

		static Vector3 GetRandomDirection(const Vector3& _vFrom, const Vector3& _vTo)
		{
			float fFromValues[3]{ _vFrom.x, _vFrom.y, _vFrom.z };
			float fToValues[3]{ _vTo.x, _vTo.y, _vTo.z };
			float fDirections[3]{ 0.0f, 0.0f, 0.0f };

			static std::random_device rd;
			static std::mt19937 generator(rd());

			for (int32 iIndex = 0; iIndex < 3; ++iIndex)
			{
				std::uniform_real_distribution<float> vDistribution(fFromValues[iIndex], fToValues[iIndex]);
				fDirections[iIndex] = vDistribution(generator);
			}

			Vector3 vDirection = { fDirections[0], fDirections[1], fDirections[2] };
			vDirection.Normalize();
			return vDirection;
		}

		static float GetSquaredLerpSeconds(int _iSquareRoot, float _fCurDeltaSeconds, float _fMaxDeltaSeconds)
		{
			return powf(_fCurDeltaSeconds / _fMaxDeltaSeconds, 1.0f / _iSquareRoot);
		}
	};
}
