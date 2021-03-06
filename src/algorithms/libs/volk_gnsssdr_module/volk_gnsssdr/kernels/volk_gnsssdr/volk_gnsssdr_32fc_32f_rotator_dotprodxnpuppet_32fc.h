/*!
 * \file volk_gnsssdr_32fc_32f_rotator_dotprodxnpuppet_32fc.h
 * \brief Volk puppet for the multiple 16-bit complex dot product kernel.
 * \authors <ul>
 *          <li> Carles Fernandez Prades 2016 cfernandez at cttc dot cat
 *          </ul>
 *
 * Volk puppet for integrating the resampler into volk's test system
 *
 * -----------------------------------------------------------------------------
 *
 * GNSS-SDR is a Global Navigation Satellite System software-defined receiver.
 * This file is part of GNSS-SDR.
 *
 * Copyright (C) 2010-2020  (see AUTHORS file for a list of contributors)
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -----------------------------------------------------------------------------
 */

#ifndef INCLUDED_volk_gnsssdr_32fc_32f_rotator_dotprodxnpuppet_32fc_H
#define INCLUDED_volk_gnsssdr_32fc_32f_rotator_dotprodxnpuppet_32fc_H

#include "volk_gnsssdr/volk_gnsssdr_32fc_32f_rotator_dot_prod_32fc_xn.h"
#include <volk_gnsssdr/volk_gnsssdr.h>
#include <volk_gnsssdr/volk_gnsssdr_malloc.h>
#include <string.h>

#ifdef LV_HAVE_GENERIC

static inline void volk_gnsssdr_32fc_32f_rotator_dotprodxnpuppet_32fc_generic(lv_32fc_t* result, const lv_32fc_t* local_code, const float* in, unsigned int num_points)
{
    // phases must be normalized. Phase rotator expects a complex exponential input!
    float rem_carrier_phase_in_rad = 0.25;
    float phase_step_rad = 0.1;
    lv_32fc_t phase[1];
    phase[0] = lv_cmake(cos(rem_carrier_phase_in_rad), sin(rem_carrier_phase_in_rad));
    lv_32fc_t phase_inc[1];
    phase_inc[0] = lv_cmake(cos(phase_step_rad), sin(phase_step_rad));
    int n;
    int num_a_vectors = 3;
    float** in_a = (float**)volk_gnsssdr_malloc(sizeof(float*) * num_a_vectors, volk_gnsssdr_get_alignment());
    for (n = 0; n < num_a_vectors; n++)
        {
            in_a[n] = (float*)volk_gnsssdr_malloc(sizeof(float) * num_points, volk_gnsssdr_get_alignment());
            memcpy((float*)in_a[n], (float*)in, sizeof(float) * num_points);
        }
    volk_gnsssdr_32fc_32f_rotator_dot_prod_32fc_xn_generic(result, local_code, phase_inc[0], phase, (const float**)in_a, num_a_vectors, num_points);

    for (n = 0; n < num_a_vectors; n++)
        {
            volk_gnsssdr_free(in_a[n]);
        }
    volk_gnsssdr_free(in_a);
}
#endif  // Generic


#ifdef LV_HAVE_GENERIC
static inline void volk_gnsssdr_32fc_32f_rotator_dotprodxnpuppet_32fc_generic_reload(lv_32fc_t* result, const lv_32fc_t* local_code, const float* in, unsigned int num_points)
{
    // phases must be normalized. Phase rotator expects a complex exponential input!
    float rem_carrier_phase_in_rad = 0.25;
    float phase_step_rad = 0.1;
    lv_32fc_t phase[1];
    phase[0] = lv_cmake(cos(rem_carrier_phase_in_rad), sin(rem_carrier_phase_in_rad));
    lv_32fc_t phase_inc[1];
    phase_inc[0] = lv_cmake(cos(phase_step_rad), sin(phase_step_rad));
    int n;
    int num_a_vectors = 3;
    float** in_a = (float**)volk_gnsssdr_malloc(sizeof(float*) * num_a_vectors, volk_gnsssdr_get_alignment());
    for (n = 0; n < num_a_vectors; n++)
        {
            in_a[n] = (float*)volk_gnsssdr_malloc(sizeof(float) * num_points, volk_gnsssdr_get_alignment());
            memcpy((float*)in_a[n], (float*)in, sizeof(float) * num_points);
        }
    volk_gnsssdr_32fc_32f_rotator_dot_prod_32fc_xn_generic_reload(result, local_code, phase_inc[0], phase, (const float**)in_a, num_a_vectors, num_points);

    for (n = 0; n < num_a_vectors; n++)
        {
            volk_gnsssdr_free(in_a[n]);
        }
    volk_gnsssdr_free(in_a);
}

#endif  // Generic

#ifdef LV_HAVE_AVX
static inline void volk_gnsssdr_32fc_32f_rotator_dotprodxnpuppet_32fc_u_avx(lv_32fc_t* result, const lv_32fc_t* local_code, const float* in, unsigned int num_points)
{
    // phases must be normalized. Phase rotator expects a complex exponential input!
    float rem_carrier_phase_in_rad = 0.25;
    float phase_step_rad = 0.1;
    lv_32fc_t phase[1];
    phase[0] = lv_cmake(cos(rem_carrier_phase_in_rad), sin(rem_carrier_phase_in_rad));
    lv_32fc_t phase_inc[1];
    phase_inc[0] = lv_cmake(cos(phase_step_rad), sin(phase_step_rad));
    int n;
    int num_a_vectors = 3;
    float** in_a = (float**)volk_gnsssdr_malloc(sizeof(float*) * num_a_vectors, volk_gnsssdr_get_alignment());
    for (n = 0; n < num_a_vectors; n++)
        {
            in_a[n] = (float*)volk_gnsssdr_malloc(sizeof(float) * num_points, volk_gnsssdr_get_alignment());
            memcpy((float*)in_a[n], (float*)in, sizeof(float) * num_points);
        }
#ifndef WIN32
    volk_gnsssdr_32fc_32f_rotator_dot_prod_32fc_xn_u_avx(result, local_code, phase_inc[0], phase, (const float**)in_a, num_a_vectors, num_points);
#else
    volk_gnsssdr_32fc_32f_rotator_dot_prod_32fc_xn_generic_reload(result, local_code, phase_inc[0], phase, (const float**)in_a, num_a_vectors, num_points);
#endif
    for (n = 0; n < num_a_vectors; n++)
        {
            volk_gnsssdr_free(in_a[n]);
        }
    volk_gnsssdr_free(in_a);
}

#endif  // AVX


#ifdef LV_HAVE_AVX
static inline void volk_gnsssdr_32fc_32f_rotator_dotprodxnpuppet_32fc_a_avx(lv_32fc_t* result, const lv_32fc_t* local_code, const float* in, unsigned int num_points)
{
    // phases must be normalized. Phase rotator expects a complex exponential input!
    float rem_carrier_phase_in_rad = 0.25;
    float phase_step_rad = 0.1;
    lv_32fc_t phase[1];
    phase[0] = lv_cmake(cos(rem_carrier_phase_in_rad), sin(rem_carrier_phase_in_rad));
    lv_32fc_t phase_inc[1];
    phase_inc[0] = lv_cmake(cos(phase_step_rad), sin(phase_step_rad));
    int n;
    int num_a_vectors = 3;
    float** in_a = (float**)volk_gnsssdr_malloc(sizeof(float*) * num_a_vectors, volk_gnsssdr_get_alignment());
    for (n = 0; n < num_a_vectors; n++)
        {
            in_a[n] = (float*)volk_gnsssdr_malloc(sizeof(float) * num_points, volk_gnsssdr_get_alignment());
            memcpy((float*)in_a[n], (float*)in, sizeof(float) * num_points);
        }
#ifndef WIN32
    volk_gnsssdr_32fc_32f_rotator_dot_prod_32fc_xn_a_avx(result, local_code, phase_inc[0], phase, (const float**)in_a, num_a_vectors, num_points);
#else
    volk_gnsssdr_32fc_32f_rotator_dot_prod_32fc_xn_generic_reload(result, local_code, phase_inc[0], phase, (const float**)in_a, num_a_vectors, num_points);
#endif
    for (n = 0; n < num_a_vectors; n++)
        {
            volk_gnsssdr_free(in_a[n]);
        }
    volk_gnsssdr_free(in_a);
}

#endif  // AVX

#endif  // INCLUDED_volk_gnsssdr_32fc_32f_rotator_dotprodxnpuppet_32fc_H
