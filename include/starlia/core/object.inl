inline void S2dObject::setPosition(const Coord2d& pos) { position = pos; }
inline const Coord2d& S2dObject::getPosition() const { return position; }

inline void S2dObject::setAngle(const double& ang) { angle = ang; }
inline double S2dObject::getAngle() const { return angle; }

inline void S2dObject::setRadius(const Coord2d& rad) { radius = rad; }
inline const Coord2d& S2dObject::getRadius() const { return radius; }


inline void S2dDynObject::setVelocity(const Coord2d& vel) { velocity = vel; }
inline const Coord2d& S2dDynObject::getVelocity() const { return velocity; }

inline void S2dDynObject::setAngVelocity(const double& angvel) { angvelocity = angvel; }
inline double S2dDynObject::getAngVelocity() const { return angvelocity; }


inline const Coord2d& SWidget::getTopLeft() const { return topLeft; }
inline const Coord2d& SWidget::getBotRight() const { return botRight; }


inline void S3dObject::setPosition(const Coord3d& pos) { position = pos; }
inline const Coord3d& S3dObject::getPosition() const { return position; }

inline void S3dObject::setAngle(const Coord3d& ang) { angle = ang; }
inline const Coord3d& S3dObject::getAngle() const { return angle; }

inline void S3dObject::setRadius(const Coord3d& rad) { radius = rad; }
inline const Coord3d& S3dObject::getRadius() const { return radius; }


inline void S3dDynObject::setVelocity(const Coord3d& vel) { velocity = vel; }
inline const Coord3d& S3dDynObject::getVelocity() const { return velocity; }

inline void S3dDynObject::setAngVelocity(const Coord3d& angvel) { angvelocity = angvel; }
inline const Coord3d& S3dDynObject::getAngVelocity() const { return angvelocity; }

inline void S3dDynObject::setThrust(const Coord3d& thr) { thrust = thr; }
inline const Coord3d& S3dDynObject::getThrust() const { return thrust; }
