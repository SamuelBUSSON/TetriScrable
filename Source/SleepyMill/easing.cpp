#include "easing.h"

#include "easing_enum.h"
#include "math.h"
#include "math.h"

float easing_utils::ease(EASING ease_method, float x)
{
    x = FMath::Clamp(x, 0, 1);
    switch (ease_method)
    {
    case EASING::EASING_LINEAR:
        return x;
    case EASING::EASING_EASE_IN_SINE:
        return ease_in_sine(x);
    case EASING::EASING_EASE_OUT_SINE:
        return ease_out_sine(x);
    case EASING::EASING_EASE_IN_OUT_SINE:
        return ease_in_out_sine(x);
    case EASING::EASING_EASE_IN_QUAD:
        return ease_in_quad(x);
    case EASING::EASING_EASE_OUT_QUAD:
        return ease_out_quad(x);
    case EASING::EASING_EASE_IN_OUT_QUAD:
        return ease_in_out_quad(x);
    case EASING::EASING_EASE_IN_CUBIC:
        return ease_in_cubic(x);
    case EASING::EASING_EASE_OUT_CUBIC:
        return ease_out_cubic(x);
    case EASING::EASING_EASE_IN_OUT_CUBIC:
        return ease_in_out_cubic(x);
    case EASING::EASING_EASE_IN_QUART:
        return ease_in_quart(x);
    case EASING::EASING_EASE_OUT_QUART:
        return ease_out_quart(x);
    case EASING::EASING_EASE_IN_OUT_QUART:
        return ease_in_out_quart(x);
    case EASING::EASING_EASE_IN_QUINT:
        return ease_in_quint(x);
    case EASING::EASING_EASE_OUT_QUINT:
        return ease_out_quint(x);
    case EASING::EASING_EASE_IN_OUT_QUINT:
        return ease_in_out_quint(x);
    case EASING::EASING_EASE_IN_EXPO:
        return ease_in_expo(x);
    case EASING::EASING_EASE_OUT_EXPO:
        return ease_out_expo(x);
    case EASING::EASING_EASE_IN_OUT_EXPO:
        return ease_in_out_expo(x);
    case EASING::EASING_EASE_IN_CIRC:
        return ease_in_circ(x);
    case EASING::EASING_EASE_OUT_CIRC:
        return ease_out_circ(x);
    case EASING::EASING_EASE_IN_OUT_CIRC:
        return ease_in_out_circ(x);
    case EASING::EASING_EASE_IN_BACK:
        return ease_in_back(x);
    case EASING::EASING_EASE_OUT_BACK:
        return ease_out_back(x);
    case EASING::EASING_EASE_IN_OUT_BACK:
        return ease_in_out_back(x);
    case EASING::EASING_EASE_IN_ELASTIC:
        return ease_in_elastic(x);
    case EASING::EASING_EASE_OUT_ELASTIC:
        return ease_out_elastic(x);
    case EASING::EASING_EASE_IN_OUT_ELASTIC:
        return ease_in_out_elastic(x);
    case EASING::EASING_EASE_IN_BOUNCE:
        return ease_in_bounce(x);
    case EASING::EASING_EASE_OUT_BOUNCE:
        return ease_out_bounce(x);
    case EASING::EASING_EASE_IN_OUT_BOUNCE:
        return ease_in_out_bounce(x);
    default:
        return x;
    }
}

float easing_utils::ease_in_sine(float x)
{
    return 1.0f - FMath::Cos((x * math::pi) / 2.0f);
}
float easing_utils::ease_out_sine(float x)
{
    return FMath::Sin((x * math::pi) / 2);
}
float easing_utils::ease_in_out_sine(float x)
{
    return -(FMath::Cos(math::pi * x) - 1) / 2;
}
float easing_utils::ease_in_quad(float x)
{
    return x * x;
}
float easing_utils::ease_out_quad(float x)
{
    return 1 - (1 - x) * (1 - x);
}
float easing_utils::ease_in_out_quad(float x)
{
    return x < 0.5 ? 2 * x * x : 1 - FMath::Pow(-2 * x + 2, 2) / 2;
}
float easing_utils::ease_in_cubic(float x)
{
    return x * x * x;
}
float easing_utils::ease_out_cubic(float x)
{
    return 1 - FMath::Pow(1 - x, 3);
}
float easing_utils::ease_in_out_cubic(float x)
{
    return x < 0.5 ? 4 * x * x * x : 1 - FMath::Pow(-2 * x + 2, 3) / 2;
}
float easing_utils::ease_in_quart(float x)
{
    return x * x * x * x;
}
float easing_utils::ease_out_quart(float x)
{
    return 1 - FMath::Pow(1 - x, 4);
}
float easing_utils::ease_in_out_quart(float x)
{
    return x < 0.5f ? 8 * x * x * x * x : 1 - FMath::Pow(-2 * x + 2, 4) / 2.0f;
}
float easing_utils::ease_in_quint(float x)
{
    return x * x * x * x * x;
}
float easing_utils::ease_out_quint(float x)
{
    return 1 - FMath::Pow(1 - x, 5);
}
float easing_utils::ease_in_out_quint(float x)
{
    return x < 0.5f ? 16.0f * x * x * x * x * x : 1 - FMath::Pow(-2.0f * x + 2, 5) / 2.0f;
}
float easing_utils::ease_in_expo(float x)
{
    return x == 0 ? 0 : FMath::Pow(2, 10 * x - 10);
}
float easing_utils::ease_out_expo(float x)
{
    return x == 1 ? 1 : 1 - FMath::Pow(2, -10 * x);
}
float easing_utils::ease_in_out_expo(float x)
{
    return x == 0
               ? 0
           : x == 1
               ? 1
           : x < 0.5 ? FMath::Pow(2, 20 * x - 10) / 2
                     : (2 - FMath::Pow(2, -20 * x + 10)) / 2;
}
float easing_utils::ease_in_circ(float x)
{
    return 1 - FMath::Sqrt(1 - FMath::Pow(x, 2));
}
float easing_utils::ease_out_circ(float x)
{
    return FMath::Sqrt(1 - FMath::Pow(x - 1, 2));
}
float easing_utils::ease_in_out_circ(float x)
{
    return x < 0.5
               ? (1 - FMath::Sqrt(1 - FMath::Pow(2 * x, 2))) / 2
               : (FMath::Sqrt(1 - FMath::Pow(-2 * x + 2, 2)) + 1) / 2;
}
float easing_utils::ease_in_back(float x)
{
    float c1 = 1.70158f;
    float c3 = c1 + 1;

    return c3 * x * x * x - c1 * x * x;
}
float easing_utils::ease_out_back(float x)
{
    float c1 = 1.70158f;
    float c3 = c1 + 1;

    return 1 + c3 * FMath::Pow(x - 1, 3) + c1 * FMath::Pow(x - 1, 2);
}
float easing_utils::ease_in_out_back(float x)
{
    float c1 = 1.70158f;
    float c2 = c1 * 1.525f;

    return x < 0.5
               ? (FMath::Pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2.0f
               : (FMath::Pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2.0f;
}
float easing_utils::ease_in_elastic(float x)
{
    float c4 = (2 * math::pi) / 3;

    return x == 0
               ? 0
           : x == 1
               ? 1
               : -FMath::Pow(2, 10 * x - 10) * FMath::Sin((x * 10 - 10.75f) * c4);
}
float easing_utils::ease_out_elastic(float x)
{
    float c4 = (2 * math::pi) / 3;

    return x == 0
               ? 0
           : x == 1
               ? 1
               : FMath::Pow(2, -10 * x) * FMath::Sin((x * 10 - 0.75f) * c4) + 1;
}
float easing_utils::ease_in_out_elastic(float x)
{
    float c5 = (2 * math::pi) / 4.5f;

    return x == 0
               ? 0
           : x == 1
               ? 1
           : x < 0.5
               ? -(FMath::Pow(2, 20 * x - 10) * FMath::Sin((20 * x - 11.125f) * c5)) / 2
               : (FMath::Pow(2, -20 * x + 10) * FMath::Sin((20 * x - 11.125f) * c5)) / 2 + 1;
}
float easing_utils::ease_in_bounce(float x)
{

    return 1 - ease_out_bounce(1 - x);
}
float easing_utils::ease_out_bounce(float x)
{
    float n1 = 7.5625f;
    float d1 = 2.75f;

    if (x < 1 / d1)
        return n1 * x * x;
    if (x < 2 / d1)
        return n1 * (x -= 1.5f / d1) * x + 0.75f;
    if (x < 2.5 / d1)
        return n1 * (x -= 2.25f / d1) * x + 0.9375f;
    return n1 * (x -= 2.625f / d1) * x + 0.984375f;
}
float easing_utils::ease_in_out_bounce(float x)
{
    return x < 0.5f
               ? (1 - ease_out_bounce(1 - 2 * x)) * 0.5f
               : (1 + ease_out_bounce(2 * x - 1)) * 0.5f;
}