#include "bullet.h"

Bullet::Bullet()

{
    this->setPixmap(QPixmap(":/image/bullet.png"));
    this->setTransformOriginPoint(95,55);
    this->setOffset(85,45);
}
