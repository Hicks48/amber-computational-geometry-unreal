#pragma once

#include "Math/Vector2D.h"

#include <numbers>
#include <cstdint>

namespace AmberScience::MathBase::Trigonometry::UnitCircle {
	static constexpr auto FullCircle = 2.0F * static_cast<float>(std::numbers::pi);

	enum class RotationDirection : std::int32_t {
		Clockwise = std::int32_t{-1},
		Counterclockwise = int32_t{1},
	};

	FVector2D AngleToVector(const float angleRad);

	float VectorToAngle(const FVector2D& vector);

	float AngleBetweenTwoAgles(const float startAngleRad, const float endAngleRad, const RotationDirection directionOfRotation);

	bool IsBetweenAngles(const float startAngleRad, const float endAngleRad, const float angleRad, const RotationDirection directionOfRotation);

	float MinAngleBetweenTwoAngles(const float aRad, const float bRad);

	RotationDirection MinRotationDirectionBetweenAngles(const float aRad, const float bRad);

	float NormalizeAngle(const float angleRad);
}
