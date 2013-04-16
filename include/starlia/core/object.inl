inline void S2dObject::setPosition(const Coord2f& pos) { position = pos; }
inline const Coord2f& S2dObject::getPosition() const { return position; }

inline void S2dObject::setAngle(float ang) { angle = ang; }
inline float S2dObject::getAngle() const { return angle; }

inline void S2dObject::setRadius(const Coord2f& rad) { radius = rad; }
inline const Coord2f& S2dObject::getRadius() const { return radius; }


inline void S2dDynObject::setVelocity(const Coord2f& vel) { velocity = vel; }
inline const Coord2f& S2dDynObject::getVelocity() const { return velocity; }

inline void S2dDynObject::setAngVelocity(float angvel) { angvelocity = angvel; }
inline float S2dDynObject::getAngVelocity() const { return angvelocity; }


inline const Coord2f& SWidget::getCenter() const { return center; }
inline const Coord2f& SWidget::getHalfSize() const { return halfsize; }


inline void S3dObject::setPosition(const Coord3f& pos) { position = pos; }
inline const Coord3f& S3dObject::getPosition() const { return position; }

inline void S3dObject::setAngle(const Coord3f& ang) { angle = ang; }
inline const Coord3f& S3dObject::getAngle() const { return angle; }

inline void S3dObject::setRadius(const Coord3f& rad) { radius = rad; }
inline const Coord3f& S3dObject::getRadius() const { return radius; }


inline void S3dDynObject::setVelocity(const Coord3f& vel) { velocity = vel; }
inline const Coord3f& S3dDynObject::getVelocity() const { return velocity; }

inline void S3dDynObject::setAngVelocity(const Coord3f& angvel) { angvelocity = angvel; }
inline const Coord3f& S3dDynObject::getAngVelocity() const { return angvelocity; }

inline void S3dDynObject::setThrust(const Coord3f& thr) { thrust = thr; }
inline const Coord3f& S3dDynObject::getThrust() const { return thrust; }
