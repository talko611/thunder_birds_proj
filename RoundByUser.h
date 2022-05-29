#pragma once
#include "Round.h"

class RoundByUser : public Round
{

public:
	RoundByUser(Bord& bord, Renderer& renderer, FileInputOutput& recorderint, GameMode mode, size_t sleepTime = 300) :
		Round(bord, renderer, recorderint, mode, sleepTime = 300) {};
	RoundByUser(const RoundByUser& r) = delete;
	void operator=(const RoundByUser& r) = delete;
	int run() override;
};

