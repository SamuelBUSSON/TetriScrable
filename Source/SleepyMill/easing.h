// // ---------------------------------------------------------------------------
// // <copyright file="easin.h" company="Endroad">
// // Copyright(C) 2021 Endroad - All Rights Reserved
// // Unauthorized copying of this file, via any medium is strictly prohibited
// // Proprietary and confidential.
// // Created by /Endroad-25 on Brawler
// // 08/04/2024
// // </copyright>
// // ---------------------------------------------------------------------------

#pragma once

// Easing function based on this site : https://easings.net/

enum class EASING : uint8;

namespace easing_utils
{
    float ease(EASING ease_method, float x);
    float ease_in_sine(float x);
    float ease_out_sine(float x);
    float ease_in_out_sine(float x);
    float ease_in_quad(float x);
    float ease_out_quad(float x);
    float ease_in_out_quad(float x);
    float ease_in_cubic(float x);
    float ease_out_cubic(float x);
    float ease_in_out_cubic(float x);
    float ease_in_quart(float x);
    float ease_out_quart(float x);
    float ease_in_out_quart(float x);
    float ease_in_quint(float x);
    float ease_out_quint(float x);
    float ease_in_out_quint(float x);
    float ease_in_expo(float x);
    float ease_out_expo(float x);
    float ease_in_out_expo(float x);
    float ease_in_circ(float x);
    float ease_out_circ(float x);
    float ease_in_out_circ(float x);
    float ease_in_back(float x);
    float ease_out_back(float x);
    float ease_in_out_back(float x);
    float ease_in_elastic(float x);
    float ease_out_elastic(float x);
    float ease_in_out_elastic(float x);
    float ease_in_bounce(float x);
    float ease_out_bounce(float x);
    float ease_in_out_bounce(float x);
}