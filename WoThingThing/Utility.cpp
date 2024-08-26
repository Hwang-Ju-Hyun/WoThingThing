#include "Utility.h"

Utility::Utility()
{

}

Utility::~Utility()
{

}

float Utility::lerp(float _start, float _end, float _alpha)
{
    return _start + _alpha * (_end - _start);
}
