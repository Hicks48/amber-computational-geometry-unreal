#pragma once

#include "Math/Vector2D.h"

namespace AmberScience::MathBase::Geometry {

	class Circle {
		public:
			Circle();
			Circle(const float radious, const FVector2D& center);
			~Circle() = default;

			float GetPerimiter() const;
			float GetDeltaAngleRad(const float deltaArc) const;
			float GetDeltaArc(const float deltaAngleRad) const;
			FVector2D GetCircumferencePoint(const float angleRad) const;
			FVector2D GetCenter() const;
			float GetRadious() const;

		private:
			float radious;
			FVector2D center;
	};
}
