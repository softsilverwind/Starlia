inline void SLayer::addKeyPress(SDLKey c, function<void (void)> fun)
{
	keypresses[c] = fun;
}

inline void addKeyPress(char c, function<void (void)> fun)
{
	addKeyPress((SDLKey) c, fun);
}

inline void SLayer::addKeyRelease(SDLKey c, function<void (void)> fun)
{
	keypresses[c] = fun;
}

inline void addKeyRelease(char c, function<void (void)> fun)
{
	addKeyRelease((SDLKey) c, fun);
}

inline void SLayer::setBlock(unsigned blk) { block = blk; }

inline void SLayer::invalidate() { invalid = true; }
