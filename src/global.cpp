#include "global.h"

float deltaTime = 0;

Vector2 f2v(const sf::Vector2f& vec) {
    return Vector2(vec.x, vec.y);
}
sf::Vector2f v2f(const Vector2& vec) {
    return sf::Vector2f(vec.x, vec.y);
}
Vector2 i2v(const sf::Vector2i& vec) {
    return Vector2(vec.x, vec.y);
}
sf::Vector2i v2i(const Vector2& vec) {
    return sf::Vector2i(vec.x, vec.y);
}

HitboxRect::HitboxRect(Vector2* pos, Vector2* size) {
    this->pos = pos;
    this->size = size;
}
float GetAng(Vector2 a, Vector2 b) {
    return atan2(a.x - b.x, a.y - b.y) / M_PI * 180;
}
Vector2 HitboxRect::GetPushOutVector(const HitboxRect& other) const {
    Vector2 rs;
    float oright = other.pos->x + other.size->x / 2;
    float oleft = other.pos->x - other.size->x / 2;
    float otop = other.pos->y - other.size->y / 2;
    float obottom = other.pos->y + other.size->y / 2;
    float right = pos->x + size->x / 2;
    float left = pos->x - size->x / 2;
    float top = pos->y - size->y / 2;
    float bottom = pos->y + size->y / 2;

    float ang = GetAng(*pos, *other.pos);
    if (
        ang >= GetAng(*pos, Vector2(right, top)) && ang <= GetAng(*pos, Vector2(left, top))
        || ang >= GetAng(*pos, Vector2(left, bottom)) || ang <= GetAng(*pos, Vector2(right, bottom))
    ) {
        if (oright > left && oleft < right) {
            bool caughtMid = obottom > top && otop < bottom;
            if (obottom > top && obottom <= pos->y)
                rs.y = obottom - top;
            else if (otop < bottom && otop >= pos->y)
                rs.y = otop - bottom;
            else if (caughtMid)
                rs.y = obottom - top;

            if (fabs(rs.y) > size->y / 2 && !caughtMid)
                rs.y = 0;
        }
    }
    else if (obottom > top && otop < bottom) {
        bool caughtMid = oleft > left && oright < right;
        if (oright > left && oright <= pos->x) {
            rs.x = oright - left;
            // printf("%f\n", GetAng(*pos, *other.pos));
        }
        else if (oleft < right && oleft > pos->x) {
            rs.x = oleft - right;
            // printf("%f\n", GetAng(*pos, *other.pos));
        }
        else if (caughtMid)
            rs.x = oright - left;

        if (fabs(rs.x) > size->x / 2 && !caughtMid)
            rs.x = 0;
    }

    return rs;
}