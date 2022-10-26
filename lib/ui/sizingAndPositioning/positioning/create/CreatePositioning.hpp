#pragma once

#include "../../positioning/positioning.hpp"
#include "../../positioning/internal/parent/internalPositioning.hpp"
#include "../../positioning/internal/target/internalTargetPositioning.hpp"
#include "../../positioning/match/parent/matchPositioning.hpp"
#include "../../positioning/match/sides/matchSidesPositioning.hpp"
#include "../../positioning/match/target/matchTargetPositioning.hpp"
#include "../../positioning/lambda/lambdaPositioning.hpp"

namespace ui {

		Positioning* createPosition(float coefficient, float offset, bool relativeTarget = false);

		Positioning* createPosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget = false);

		Positioning* createPosition(Location parentSide, Location objectSide, float offset);
} // ui