#ifndef __TIMER_H__
#define __TIMER_H__

#include <queue>
#include <utility>
#include <functional>

using namespace std;

namespace Starlia
{

class StarTimer
{
	private:
		typedef struct
		{
			bool operator()(pair<unsigned int, function<void (void)> >& l, pair<unsigned int, function<void (void)> >& r) 
			{
				return l.first > r.first;
			}
		}
		compare;

		static priority_queue<pair<unsigned int, function<void (void)> >, vector<pair<unsigned int, function<void (void)> > >, compare> timers;
		static void loopTimers(unsigned int last_update);

	public:
		static void registerTimer(unsigned short msecs, function<void (void)> fun);

	friend class StarCore;
};

}

#endif /* __TIMER_H__ */
