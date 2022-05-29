#pragma once
#include "Round.h"
#include <chrono>

class RoundByFile : public Round
{
public:
	RoundByFile(Bord& bord, Renderer& renderer, FileInputOutput& recorderint, GameMode mode, size_t sleepTime = 300) :
		Round(bord, renderer, recorderint, mode, sleepTime = 300) {};
	RoundByFile(const RoundByFile& r) = delete;
	void operator=(const RoundByFile& r) = delete;
	int run() override;
};

