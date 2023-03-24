#pragma once

#include "../iPositioning.hpp"
#include "../../positioning/internal/parent/internalPositioning.hpp"
#include "../../positioning/internal/target/internalTargetPositioning.hpp"
#include "../../positioning/match/parent/matchPositioning.hpp"
#include "../../positioning/match/sides/matchSidesPositioning.hpp"
#include "../../positioning/match/target/matchTargetPositioning.hpp"
#include "../../positioning/lambda/lambdaPositioning.hpp"

namespace ui {
	IPositioning* makePosition(float coefficient, float offset, bool relativeTarget = false);
	
	IPositioning* makePosition(float coefficient, float objectCoefficient, float offset, bool relativeTarget = false);
	
	IPositioning* makePosition(Location parentSide, Location objectSide, float offset);
	
	IPositioning* makePosition(LambdaPositioning::FindPositionFunc findPosition);
}