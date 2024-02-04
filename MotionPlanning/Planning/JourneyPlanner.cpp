#include "./JourneyPlanner.h"

#include "Math/Vector2D.h"

#include "../MovementConfiguration.h"
#include "../MovementConstraints.h"
#include "../Journey/Journey.h"
#include "../Journey/SimpleJourney.h"
#include "../Trajectories/ITrajectory.h"
#include "../Trajectories/Arc.h"
#include "../Trajectories/Straight.h"
#include "../../MathBase/Geometry/Circle.h"
#include "../../MathBase/Geometry/GeometryQueries.h"
#include "../../MathBase/Trigonometry/UnitCircle.h"
#include "../../MathBase/Vectors/VectorLocationQueries.h"
#include "../../MathBase/Vectors//VectorTransformations.h"

#include <cmath>
#include <cstdint>
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>

using namespace AmberScience::MathBase::Geometry;
using namespace AmberScience::MathBase::Trigonometry;
using namespace AmberScience::MathBase::Vectors;

namespace {
    using namespace AmberScience::MotionPlanning;
    using namespace AmberScience::MotionPlanning::Trajectories;

    std::shared_ptr<Straight> CalculateCrossTrajectoryBetweenTurningBases(const Circle& startTurningBase, const Circle& endTurningBase, const UnitCircle::RotationDirection initialRotationDirection) {
        auto turningBaseToTurningBase = endTurningBase.GetCenter() - startTurningBase.GetCenter();
        auto fromStartToMidpoint = 0.5F * turningBaseToTurningBase;
        auto fromEndToMidpoint = -0.5F * turningBaseToTurningBase;

        auto cosine = startTurningBase.GetRadious() / fromStartToMidpoint.Length();

        // Cosine should always be between -1 and 1. If it is not then return null to indicate that trajectory is not valid.
        if (cosine > 1.0F || cosine < -1.0F) {
            return nullptr;
        }

        auto alpha = std::acos(cosine);

        return std::make_shared<Straight>(
            startTurningBase.GetCenter() + startTurningBase.GetRadious() * VectorTransformations::RotateVector(fromStartToMidpoint.GetSafeNormal(), -1.0F * static_cast<std::int32_t>(initialRotationDirection) * alpha),
            endTurningBase.GetCenter() + endTurningBase.GetRadious() * VectorTransformations::RotateVector(fromEndToMidpoint.GetSafeNormal(), -1.0F * static_cast<std::int32_t>(initialRotationDirection) * alpha)
        );
    }

    std::shared_ptr<Straight> CalculateStraightTrajectoryBetweenTurningBases(const Circle& startTurningBase, const Circle& endTurningBase, const UnitCircle::RotationDirection initialRotationDirection) {
        auto turningBaseToTurningBase = endTurningBase.GetCenter() - startTurningBase.GetCenter();
        auto fromCenterToIntersection = startTurningBase.GetRadious() * -1.0F * static_cast<std::int32_t>(initialRotationDirection) * turningBaseToTurningBase.GetRotated(90.0F).GetSafeNormal();

        return std::make_shared<Straight>(
            startTurningBase.GetCenter() + fromCenterToIntersection,
            endTurningBase.GetCenter() + fromCenterToIntersection
        );
    }

    Journey CreateCSCJourney(const FVector2D& start, const FVector2D& end, const Circle& startTurningBase, const Circle& endTurningBase, const UnitCircle::RotationDirection startRotationDirection, const UnitCircle::RotationDirection endRotationDirection, std::shared_ptr<ITrajectory> fromTurningBaseToTurningBase) {
        auto startArc = std::make_shared<Arc>(
            startTurningBase,
            UnitCircle::VectorToAngle(start - startTurningBase.GetCenter()),
            UnitCircle::VectorToAngle(fromTurningBaseToTurningBase->GetStartPosition() - startTurningBase.GetCenter()),
            startRotationDirection
        );

        auto endArc = std::make_shared<Arc>(
            endTurningBase,
            UnitCircle::VectorToAngle(fromTurningBaseToTurningBase->GetEndPosition() - endTurningBase.GetCenter()),
            UnitCircle::VectorToAngle(end - endTurningBase.GetCenter()),
            endRotationDirection
        );

        auto simpleJournies = std::vector<SimpleJourney>{
            SimpleJourney{ startArc },
            SimpleJourney{ fromTurningBaseToTurningBase },
            SimpleJourney{ endArc },
        };

        return Journey{ simpleJournies };
    }

    std::optional<Journey> CalculateCrossPath(const FVector2D& start, const FVector2D& end, const Circle& startTurningBase, const Circle& endTurningBase, const UnitCircle::RotationDirection initialRotationDirection) {
        auto fromTurningBaseToTurningBase = CalculateCrossTrajectoryBetweenTurningBases(startTurningBase, endTurningBase, initialRotationDirection);

        if (!fromTurningBaseToTurningBase) {
            return std::nullopt;
        }

        // For cross path the target rotation is inverted direction of the initial rotation direction;
        auto targetRotationDirection = static_cast<UnitCircle::RotationDirection>(-1 * static_cast<std::int32_t>(initialRotationDirection));

        return CreateCSCJourney(start, end, startTurningBase, endTurningBase, initialRotationDirection, targetRotationDirection, fromTurningBaseToTurningBase);
    }

    Journey CalculateStraightPath(const FVector2D& start, const FVector2D& end, const Circle& startTurningBase, const Circle& endTurningBase, const UnitCircle::RotationDirection initialRotationDirection) {
        auto fromTurningBaseToTurningBase = CalculateStraightTrajectoryBetweenTurningBases(startTurningBase, endTurningBase, initialRotationDirection);
        return CreateCSCJourney(start, end, startTurningBase, endTurningBase, initialRotationDirection, initialRotationDirection, fromTurningBaseToTurningBase);
    }

    std::optional<Journey> CalculateCSCPath(const MovementConfiguration& start, const MovementConfiguration& end, const Circle& startTurningBase, const Circle& endTurningBase) {
        auto initialRotationDirection = GeometryQueries::GetRotationDirection(start.Heading, start.Position, startTurningBase.GetCenter());
        auto targetRotationDirection = GeometryQueries::GetRotationDirection(end.Heading, end.Position, endTurningBase.GetCenter());

        if (initialRotationDirection == UnitCircle::RotationDirection::Clockwise && targetRotationDirection == UnitCircle::RotationDirection::Clockwise) {
            return CalculateStraightPath(start.Position, end.Position, startTurningBase, endTurningBase, UnitCircle::RotationDirection::Clockwise);
        }

        if (initialRotationDirection == UnitCircle::RotationDirection::Clockwise && targetRotationDirection == UnitCircle::RotationDirection::Counterclockwise) {
            return CalculateCrossPath(start.Position, end.Position, startTurningBase, endTurningBase, UnitCircle::RotationDirection::Clockwise);
        }

        if (initialRotationDirection == UnitCircle::RotationDirection::Counterclockwise && targetRotationDirection == UnitCircle::RotationDirection::Clockwise) {
            return CalculateCrossPath(start.Position, end.Position, startTurningBase, endTurningBase, UnitCircle::RotationDirection::Counterclockwise);
        }

        if (initialRotationDirection == UnitCircle::RotationDirection::Counterclockwise && targetRotationDirection == UnitCircle::RotationDirection::Counterclockwise) {
            return CalculateStraightPath(start.Position, end.Position, startTurningBase, endTurningBase, UnitCircle::RotationDirection::Counterclockwise);
        }

        return std::nullopt;
    }

    std::optional<Journey> CalculateCCCPath(const MovementConfiguration& start, const MovementConfiguration& end, const Circle& startTurningBase, const Circle& endTurningBase) {
        auto fromStartToEnd = end.Position - start.Position;

        // If the distance between start and end is more than 4 x turning base radius then the CCC path can not be shortest and can skip.
        if (fromStartToEnd.Length() > 4.0F * startTurningBase.GetRadious()) {
            return std::nullopt;
        }

        // Check that the provided turning bases match either RLR or LRL since those are only options.
        // Meaning the turning direction has to be the same for start and end turning bases.
        auto startRotationDirection = GeometryQueries::GetRotationDirection(start.Heading, start.Position, startTurningBase.GetCenter());
        auto endRotationDirection = GeometryQueries::GetRotationDirection(end.Heading, end.Position, endTurningBase.GetCenter());

        if (startRotationDirection != endRotationDirection) {
            return std::nullopt;
        }

        // Calculate the center of the middle circle in the CCC path and create the middle circle.
        auto fromStartTurningBaseCenterToEndTurningBaseCenter = endTurningBase.GetCenter() - startTurningBase.GetCenter();

        auto angleBetweenStartToEndAndStartToMiddleCircle = std::acos((0.5F * fromStartTurningBaseCenterToEndTurningBaseCenter.Length()) / (2 * startTurningBase.GetRadious()));
        auto fromStartToCenterOfMiddleCircle = 2 * startTurningBase.GetRadious() * VectorTransformations::RotateVector(fromStartTurningBaseCenterToEndTurningBaseCenter.GetSafeNormal(), angleBetweenStartToEndAndStartToMiddleCircle);
        auto centerOfThirdCircle = startTurningBase.GetCenter() + fromStartToCenterOfMiddleCircle;

        auto middleCircle = Circle{ startTurningBase.GetRadious(), centerOfThirdCircle };

        // Calculate intersections between the three circles.
        auto startToMiddleCrossPoint = startTurningBase.GetCenter() + 0.5F * (middleCircle.GetCenter() - startTurningBase.GetCenter());
        auto middleToEndCrossPoint = endTurningBase.GetCenter() + 0.5F * (middleCircle.GetCenter() - endTurningBase.GetCenter());

        // Create arcs for the journey.
        auto startCircleArc = std::make_shared<Arc>(
            startTurningBase,
            UnitCircle::VectorToAngle(start.Position - startTurningBase.GetCenter()),
            UnitCircle::VectorToAngle(startToMiddleCrossPoint - startTurningBase.GetCenter()),
            startRotationDirection
        );

        auto middleCircleArc = std::make_shared<Arc>(
            middleCircle,
            UnitCircle::VectorToAngle(startToMiddleCrossPoint - middleCircle.GetCenter()),
            UnitCircle::VectorToAngle(middleToEndCrossPoint - middleCircle.GetCenter()),
            // The middle circles rotation direction is always opposite to the start circles rotation direction.
            static_cast<UnitCircle::RotationDirection>(-1 * static_cast<std::int32_t>(startRotationDirection))
        );

        auto endCircleArc = std::make_shared<Arc>(
            endTurningBase,
            UnitCircle::VectorToAngle(middleToEndCrossPoint - endTurningBase.GetCenter()),
            UnitCircle::VectorToAngle(end.Position - endTurningBase.GetCenter()),
            endRotationDirection
        );

        // Create the combined journey from start to end.
        return Journey{
            std::vector<SimpleJourney>{ SimpleJourney{ startCircleArc }, SimpleJourney{ middleCircleArc }, SimpleJourney{ endCircleArc } }
        };
    }

    Journey CalculateCSPath(const MovementConfiguration& start, const FVector2D& end, const Circle& startTurningBase) {
        // Calculate rotation direction at start.
        auto rotationDirection = GeometryQueries::GetRotationDirection(start.Heading, start.Position, startTurningBase.GetCenter());

        // Calculate vector from the center of turning base to the end point.
        auto fromTurningBaseToEnd = end - startTurningBase.GetCenter();

        // The vectrors from center to end, from center to tangent point and from tangent point to end form a right triangle.
        // The angle between the vector from center to end and from center to tangent point is 90 degrees.
        // The angle alpha angle between the vectors from center to end and center to tangent is arc cosine of the ratio of the length of the two vectors.
        auto alpha = std::acos(startTurningBase.GetRadious() / fromTurningBaseToEnd.Length());

        // Calculate unit circle angle for the tangent point by getting the angle of the vector from center to end and rotating it by alpha against the rotation direction.
        auto centerToEndAngle = UnitCircle::VectorToAngle(fromTurningBaseToEnd);
        auto tangentPointAngle = UnitCircle::NormalizeAngle(centerToEndAngle + alpha * -1.0F * static_cast<std::int32_t>(rotationDirection));

        // Create the arc for the CS path.
        auto arc = std::make_shared<Arc>(
            startTurningBase,
            UnitCircle::VectorToAngle(start.Position - startTurningBase.GetCenter()),
            tangentPointAngle,
            rotationDirection
        );

        // Calculate the tangent point.
        auto tangentPoint = UnitCircle::AngleToVector(tangentPointAngle) * startTurningBase.GetRadious() + startTurningBase.GetCenter();

        // Create straight from the tangent to the end point.
        auto straight = std::make_shared<Straight>(tangentPoint, end);

        // Create the journey.
        return Journey{ std::vector<SimpleJourney>{ SimpleJourney{ arc }, SimpleJourney{ straight } } };
    }
}

namespace AmberScience::MotionPlanning {
    Journey Plan(const MovementConfiguration& start, const FVector2D& end, const MovementConstraints& constraints) {
        // Get turning bases for both turn directions from the start configuration.
        auto [startLeftTurningBase, startRightTurningBase] = GeometryQueries::CircleFromCircumferencePointTangentAndRadious(start.Position, start.Heading, constraints.TurningRadious);

        // For both turning bases calculate the distance for the journey to the end point.
        auto leftTurningBaseJourney = CalculateCSPath(start, end, startLeftTurningBase);
        auto rightTurningBaseJourney = CalculateCSPath(start, end, startRightTurningBase);

        // Return the shortest of the two journeys.
        return leftTurningBaseJourney.GetLength() < rightTurningBaseJourney.GetLength() ? leftTurningBaseJourney : rightTurningBaseJourney;
    }

    Journey Plan(const MovementConfiguration& start, const MovementConfiguration& end, const MovementConstraints& constraints) {
        // Compute all turning base combinations.
        auto [startLeftTurningBase, startRightTurningBase] = GeometryQueries::CircleFromCircumferencePointTangentAndRadious(start.Position, start.Heading, constraints.TurningRadious);
        auto [endLeftTurningBase, endRightTurningBase] = GeometryQueries::CircleFromCircumferencePointTangentAndRadious(end.Position, end.Heading, constraints.TurningRadious);

        // Calculate correct path option based on travel direction of start and end configuration on their respective turning bases.
        auto dubinsCurves = std::vector<std::optional<Journey>>{
            CalculateCSCPath(start, end, startLeftTurningBase, endLeftTurningBase),
            CalculateCSCPath(start, end, startLeftTurningBase, endRightTurningBase),
            CalculateCSCPath(start, end, startRightTurningBase, endLeftTurningBase),
            CalculateCSCPath(start, end, startRightTurningBase, endRightTurningBase),
        };

        dubinsCurves.insert(dubinsCurves.end(), {
            CalculateCCCPath(start, end, startLeftTurningBase, endLeftTurningBase),
            CalculateCCCPath(start, end, startLeftTurningBase, endRightTurningBase),
            CalculateCCCPath(start, end, startRightTurningBase, endLeftTurningBase),
            CalculateCCCPath(start, end, startRightTurningBase, endRightTurningBase),
        });

        dubinsCurves.erase(
            std::remove_if(dubinsCurves.begin(), dubinsCurves.end(), [](const std::optional<Journey>& journey) { return !journey.has_value(); }),
            dubinsCurves.end()
        );

        // Choose the journey with smallest distance.
        return **std::min_element(dubinsCurves.begin(), dubinsCurves.end(), [](const std::optional<Journey>& a, const std::optional<Journey>& b) { return a->GetLength() < b->GetLength(); });
    }
}
