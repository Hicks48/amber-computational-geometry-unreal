#include "./GeometryRendering.h"

#include "./Circle.h"
#include "../Trigonometry/UnitCircle.h"

#include "Math/Vector2D.h"

#include <cstdint>
#include <vector>
#include <cmath>

using namespace AmberScience::MathBase::Trigonometry;

namespace AmberScience::MathBase::Geometry::GeometryRendering {

	std::vector<FVector2D> GetRenderingPointsForCircle(const Circle& circle, const float pointsPerUnit) {
        auto nPoints = static_cast<std::int32_t>(std::ceil(circle.GetPerimiter() / pointsPerUnit));

        auto points = std::vector<FVector2D>{};
        for (std::int32_t i = 0; i < nPoints; i++) {
            auto circumferenceProgress = static_cast<float>(i) / static_cast<float>(nPoints);
            auto currentRadians = circumferenceProgress * UnitCircle::FullCircle;

            points.push_back(circle.GetCircumferencePoint(currentRadians));
        }

        return points;
	}
}
