#ifndef __TIMER_H__
#define __TIMER_H__

#include <queue>
#include <utility>

using namespace std;

namespace Starlia
{

class StarTimer
{
	private:
		typedef struct
		{
			bool operator()(pair<unsigned int, void (*)()>& l, pair<unsigned int, void (*)()>& r) 
			{
				return l > r;
			}
		}
		compare;

		static priority_queue<pair<unsigned int, void (*)()>, vector<pair<unsigned int, void (*)()> >, compare> timers;
		static void loopTimers(unsigned int last_recalc);

	public:
		static void registerTimer(unsigned short msecs, void (*fun)());

	friend class StarCore;
};

}

#endif /* __TIMER_H__ */
