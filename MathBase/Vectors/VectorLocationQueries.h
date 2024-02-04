#pragma once

#include "Math/Vector2D.h"

namespace AmberScience::MathBase::Vectors::VectorLocationQueries {

    bool IsLeftOf(const FVector2D& a, const FVector2D& b);

    bool IsRightOf(const FVector2D& a, const FVector2D& b);
}
