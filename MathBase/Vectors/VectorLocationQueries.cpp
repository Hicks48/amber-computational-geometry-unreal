#include "VectorLocationQueries.h"

#include "Math/Vector2D.h"
#include "Math/Vector.h"

namespace AmberScience::MathBase::Vectors::VectorLocationQueries {

    bool IsLeftOf(const FVector2D& a, const FVector2D& b) {
        return FVector::CrossProduct(FVector{a.X, 0.0F, a.Y}, FVector{a.X, 0.0F, b.Y}).Y < 0.0F;
    }

    bool IsRightOf(const FVector2D& a, const FVector2D& b) {
        return !IsLeftOf(a, b);
    }
}
