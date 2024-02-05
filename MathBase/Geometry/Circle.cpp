#include "Circle.h"

#include "Math/Vector2D.h"

#include "../Trigonometry/UnitCircle.h"

using namespace AmberScience::MathBase::Trigonometry;

namespace AmberScience::MathBase::Geometry {
	
	Circle::Circle() : radius(1.0F), center(FVector2D::ZeroVector) {}

	Circle::Circle(const float radius, const FVector2D& center) : radius(radius), center(center) {}

	float Circle::GetPerimiter() const {
		return UnitCircle::FullCircle * this->radius;
	}

	float Circle::GetDeltaAngleRad(const float deltaArc) const {
		return deltaArc / this->radius;
	}

	float Circle::GetDeltaArc(const float deltaAngleRad) const {
		return deltaAngleRad * this->radius;
	}

	FVector2D Circle::GetCircumferencePoint(const float angleRad) const {
		return this->center + this->radius * UnitCircle::AngleToVector(angleRad);
	}

	FVector2D Circle::GetCenter() const {
		return this->center;
	}

	float Circle::GetRadius() const {
		return this->radius;
	}
}