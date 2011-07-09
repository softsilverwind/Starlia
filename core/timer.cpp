#include <iostream>
#include <cstdlib>
#include <queue>
#include <utility>
#include <SDL/SDL.h>

#include "timer.h"

using namespace std;

namespace Starlia
{

priority_queue<pair<unsigned int, void (*)()>, vector<pair<unsigned int, void (*)()> >, StarTimer::compare> StarTimer::timers;

void StarTimer::loopTimers(unsigned int last_recalc)
{
	while (!timers.empty() && timers.top().first <= last_recalc)
	{
		(*timers.top().second)();
		timers.pop();
	}
}

void StarTimer::registerTimer(unsigned short msecs, void (*fun)())
{
	unsigned int time_now = SDL_GetTicks();

	timers.push(pair<unsigned int, void (*)()>(time_now + msecs, fun));
}

}
