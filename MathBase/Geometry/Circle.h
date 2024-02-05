#pragma once

#include "Math/Vector2D.h"

namespace AmberScience::MathBase::Geometry {

	class Circle {
		public:
			Circle();
			Circle(const float radius, const FVector2D& center);
			~Circle() = default;

			float GetPerimiter() const;
			float GetDeltaAngleRad(const float deltaArc) const;
			float GetDeltaArc(const float deltaAngleRad) const;
			FVector2D GetCircumferencePoint(const float angleRad) const;
			FVector2D GetCenter() const;
			float GetRadius() const;

		private:
			float radius;
			FVector2D center;
	};
}
