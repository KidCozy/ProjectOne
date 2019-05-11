#pragma once
#include"ProjectOne.h"

struct DissolveValue {
	float* DissolveAmount = nullptr;
	float* DissolveTransitionTime = nullptr;
	float* DissolveFringe = nullptr;
	float* DissolveEmissive = nullptr;
	FVector* DissolveColor = nullptr;
	UTexture2D* DissolveBaseTexture = nullptr;
	UTexture2D* DissolveMaskTexture = nullptr;

	float CalcOffset() const { return *DissolveTransitionTime + 0.5f; }


};