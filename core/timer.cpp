#include <iostream>
#include <functional>
#include <cstdlib>
#include <queue>
#include <utility>
#include <SDL/SDL.h>

#include "timer.h"

using namespace std;

namespace Starlia
{

priority_queue<pair<unsigned int, function<void (void)> >, vector<pair<unsigned int, function<void (void)> > >, StarTimer::compare> StarTimer::timers;

void StarTimer::loopTimers(unsigned int last_recalc)
{
	while (!timers.empty() && timers.top().first <= last_recalc)
	{
		timers.top().second();
		timers.pop();
	}
}

// Known issue: Overflow occurs at 49.71 days, so timers might fire when should
// not. On the other hand, this bug might help the poor soul get a life :)
void StarTimer::registerTimer(unsigned short msecs, function<void (void)> fun)
{
	unsigned int time_now = SDL_GetTicks();

	timers.push(pair<unsigned int, function<void (void)> >(time_now + msecs, fun));
}

}
