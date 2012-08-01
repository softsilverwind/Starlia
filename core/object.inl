inline void Star2dObject::setPosition(const Coord2d& pos) { position = pos; }
inline const Coord2d& Star2dObject::getPosition() const { return position; }
inline void Star2dObject::setAngle(const double& ang) { angle = ang; }
inline double Star2dObject::getAngle() const { return angle; }
inline void Star2dObject::setRadius(const Coord2d& rad) { radius = rad; }
inline const Coord2d& Star2dObject::getRadius() const { return radius; }
inline void Star2dDynObject::setVelocity(const Coord2d& vel) { velocity = vel; }
inline const Coord2d& Star2dDynObject::getVelocity() const { return velocity; }
inline void Star2dDynObject::setAngVelocity(const double& angvel) { angvelocity = angvel; }
inline double Star2dDynObject::getAngVelocity() const { return angvelocity; }
inline const Coord2d& StarWidget::getTopLeft() const { return topLeft; }
inline const Coord2d& StarWidget::getBotRight() const { return botRight; }
inline void Star3dObject::setPosition(const Coord3d& pos) { position = pos; }
inline const Coord3d& Star3dObject::getPosition() const { return position; }
inline void Star3dObject::setAngle(const Coord3d& ang) { angle = ang; }
inline const Coord3d& Star3dObject::getAngle() const { return angle; }
inline void Star3dObject::setRadius(const Coord3d& rad) { radius = rad; }
inline const Coord3d& Star3dObject::getRadius() const { return radius; }
inline void Star3dDynObject::setVelocity(const Coord3d& vel) { velocity = vel; }
inline const Coord3d& Star3dDynObject::getVelocity() const { return velocity; }
inline void Star3dDynObject::setAngVelocity(const Coord3d& angvel) { angvelocity = angvel; }
inline const Coord3d& Star3dDynObject::getAngVelocity() const { return angvelocity; }
inline void Star3dDynObject::setThrust(const Coord3d& thr) { thrust = thr; }
inline const Coord3d& Star3dDynObject::getThrust() const { return thrust; }
