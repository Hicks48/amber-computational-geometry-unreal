#include "Circle.h"

#include "Math/Vector2D.h"

#include "../Trigonometry/UnitCircle.h"

using namespace AmberScience::MathBase::Trigonometry;

namespace AmberScience::MathBase::Geometry {
	
	Circle::Circle() : radious(1.0F), center(FVector2D::ZeroVector) {}

	Circle::Circle(const float radious, const FVector2D& center) : radious(radious), center(center) {}

	float Circle::GetPerimiter() const {
		return UnitCircle::FullCircle * this->radious;
	}

	float Circle::GetDeltaAngleRad(const float deltaArc) const {
		return deltaArc / this->radious;
	}

	float Circle::GetDeltaArc(const float deltaAngleRad) const {
		return deltaAngleRad * this->radious;
	}

	FVector2D Circle::GetCircumferencePoint(const float angleRad) const {
		return this->center + this->radious * UnitCircle::AngleToVector(angleRad);
	}

	FVector2D Circle::GetCenter() const {
		return this->center;
	}

	float Circle::GetRadious() const {
		return this->radious;
	}
}