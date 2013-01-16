inline void SLayer::dispatchSignals(shared_ptr<SObject> obj)
{
	obj->dispatchSignals();
}

inline bool& SLayer::getInvalidRef(shared_ptr<SObject> obj)
{
	return obj->invalid;
}

inline void SLayer::setLayer(shared_ptr<SObject> obj)
{
	obj->layer = this;
}

inline void SLayer::addKeyPress(SDLKey c, function<void (void)> fun)
{
	keypresses[c] = fun;
}

inline void SLayer::addKeyPress(char c, function<void (void)> fun)
{
	addKeyPress((SDLKey) c, fun);
}

inline void SLayer::addKeyRelease(SDLKey c, function<void (void)> fun)
{
	keyreleases[c] = fun;
}

inline void SLayer::addKeyRelease(char c, function<void (void)> fun)
{
	addKeyRelease((SDLKey) c, fun);
}

inline void SLayer::setBlock(unsigned blk) { block = blk; }

inline void SLayer::invalidate() { invalid = true; }

template <typename T>
inline void SListLayer<T>::draw()
{
	SLayer::draw();

	for (auto it = elements.begin(); it != elements.end(); ++it)
	{
		bool& invalid = SLayer::getInvalidRef(*it);
		if (invalid)
		{
			invalid = false;
			elements.erase(it--);
			continue;
		}
		(*it)->draw();
	}
}

template <typename T>
inline void SListLayer<T>::update()
{
	for (auto it = elements.begin(); it != elements.end(); ++it)
	{
		bool& invalid = SLayer::getInvalidRef(*it);
		if (invalid)
		{
			invalid = false;
			elements.erase(it--);
			continue;
		}
		(*it)->update();
	}
}

template <typename T>
inline void SListLayer<T>::add(T *elem)
{
	shared_ptr<T> selem(elem);
	SLayer::setLayer(selem);
	elements.push_back(selem);
}

template <typename T>
inline void SListLayer<T>::add(shared_ptr<T> elem)
{
	SLayer::setLayer(elem);
	elements.push_back(elem);
}
