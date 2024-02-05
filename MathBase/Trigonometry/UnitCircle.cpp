#include "UnitCircle.h"

#include "Math/Vector2D.h"

#include <cmath>

namespace AmberScience::MathBase::Trigonometry::UnitCircle {
    
    FVector2D AngleToVector(const float angleRad) {
        return FVector2D{ std::cos(angleRad), std::sin(angleRad) };
    }

    float VectorToAngle(const FVector2D& vector) {
        return std::atan2(vector.Y, vector.X);
    }

    float AngleBetweenTwoAgles(const float startAngleRad, const float endAngleRad, const RotationDirection directionOfRotation) {
        auto needsToCrossZero = directionOfRotation == RotationDirection::Counterclockwise
            ? endAngleRad < startAngleRad
            : endAngleRad > startAngleRad;
        
        if (needsToCrossZero) {
            return directionOfRotation == RotationDirection::Counterclockwise
                ? endAngleRad + FullCircle - startAngleRad
                : -1.0 * (startAngleRad + FullCircle - endAngleRad);
        }

        return std::abs(endAngleRad - startAngleRad);
    }

    bool IsBetweenAngles(const float startAngleRad, const float endAngleRad, const float angleRad, const RotationDirection directionOfRotation) {
        return AngleBetweenTwoAgles(startAngleRad, angleRad, directionOfRotation) < AngleBetweenTwoAgles(startAngleRad, endAngleRad, directionOfRotation);
    }

    float MinAngleBetweenTwoAngles(const float aRad, const float bRad) {
        return std::min(
            std::abs(AngleBetweenTwoAgles(aRad, bRad, RotationDirection::Counterclockwise)),
            std::abs(AngleBetweenTwoAgles(aRad, bRad, RotationDirection::Clockwise))
        );
    }

    RotationDirection MinRotationDirectionBetweenAngles(const float aRad, const float bRad) {
        return std::abs(AngleBetweenTwoAgles(aRad, bRad, RotationDirection::Counterclockwise)) <= std::abs(AngleBetweenTwoAgles(aRad, bRad, RotationDirection::Clockwise))
            ? RotationDirection::Counterclockwise
            : RotationDirection::Clockwise;
    }

    float NormalizeAngle(const float angleRad) {
        auto singleRound = std::fmod(angleRad, FullCircle);
        return singleRound > 0.0f
            ? singleRound
            : FullCircle - std::abs(singleRound);
    }
}
