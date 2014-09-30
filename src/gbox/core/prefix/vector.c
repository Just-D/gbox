/*!The Graphic Box Library
 * 
 * GBox is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * GBox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with GBox; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2014 - 2015, ruki All rights reserved.
 *
 * @author      ruki
 * @file        vector.c
 * @ingroup     core
 *
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_MODULE_NAME            "vector"
#define TB_TRACE_MODULE_DEBUG           (0)

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "vector.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_void_t gb_vector_make(gb_vector_ref_t vector, gb_float_t x, gb_float_t y)
{
    // check
    tb_assert_abort(vector);

    // make it
    vector->x = x;
    vector->y = y;
}
tb_void_t gb_vector_imake(gb_vector_ref_t vector, tb_long_t x, tb_long_t y)
{
    gb_vector_make(vector, gb_long_to_float(x), gb_long_to_float(y));
}
tb_void_t gb_vector_make_from_point(gb_vector_ref_t vector, gb_point_ref_t point)
{
    // check
    tb_assert_abort(vector && point);

    // make it
    *vector = *((gb_vector_ref_t)point);
}
tb_void_t gb_vector_negate(gb_vector_ref_t vector)
{
    // check
    tb_assert_abort(vector);

    // negate it
    vector->x = -vector->x;
    vector->y = -vector->y;
}
tb_void_t gb_vector_rotate(gb_vector_ref_t vector, tb_size_t direction)
{
    // rotate it
    gb_vector_rotate2(vector, vector, direction);
}
tb_void_t gb_vector_rotate2(gb_vector_ref_t vector, gb_vector_ref_t rotated, tb_size_t direction)
{
    // check
    tb_assert_abort(vector && rotated);

    /* rotate it
     *
     * @note using t for avoiding the case of vector == rotated
     */
    if (direction == GB_ROTATE_DIRECTION_CW)
    {
        gb_float_t t = vector->x;
        rotated->x = -vector->y;
        rotated->y = t;
    }
    else
    {
        gb_float_t t = vector->x;
        rotated->x = vector->y;
        rotated->y = -t;
    }
}
tb_void_t gb_vector_scale(gb_vector_ref_t vector, gb_float_t scale)
{
    // scale it
    gb_vector_scale2(vector, vector, scale);
}
tb_void_t gb_vector_scale2(gb_vector_ref_t vector, gb_vector_ref_t scaled, gb_float_t scale)
{
    // check
    tb_assert_abort(vector && scaled);

    // scale it
    scaled->x = gb_mul(vector->x, scale);
    scaled->y = gb_mul(vector->y, scale);
}
gb_float_t gb_vector_length(gb_vector_ref_t vector)
{
    // check
    tb_assert_abort(vector);

    // the dx and dy
    gb_float_t dx = vector->x;
    gb_float_t dy = vector->y;

    // the length
    gb_float_t length = 0;

#ifdef GB_CONFIG_FLOAT_FIXED
    // attempt to compute the length directly
    tb_hong_t dd = ((tb_hong_t)dx * dx + (tb_hong_t)dy * dy) >> 16;
    if (!(dd >> 32) && (tb_fixed_t)dd > 0) length = gb_sqrt((tb_fixed_t)dd);
    else if (dd)
    {
#   ifdef TB_CONFIG_TYPE_FLOAT
        // compute the length using the double value
        tb_double_t xx = gb_float_to_tb(dx);
        tb_double_t yy = gb_float_to_tb(dy);
        tb_float_t  ll = (tb_float_t)tb_sqrt(xx * xx + yy * yy);
        length = tb_float_to_gb(ll);

        // trace
        tb_trace_w("compute double %{vector}.length, will be slower!", vector);
        
#   else
        // trace
        tb_trace_e("cannot compute %{vector}.length", vector);
        
        // the invalid length
        length = GB_NAN;
#   endif
    }
    else length = GB_NEAR0;
#else
    // attempt to compute the length directly
    tb_float_t dd = dx * dx + dy * dy;
    if (gb_isfinite(dd)) length = gb_sqrt(dd);
    else
    {
        // compute the length using the double value
        tb_double_t xx = dx;
        tb_double_t yy = dy;
        length = (tb_float_t)tb_sqrt(xx * xx + yy * yy);
    }
#endif

    // ok?
    return length;
}
tb_bool_t gb_vector_length_set(gb_vector_ref_t vector, gb_float_t length)
{
    // check
    tb_assert_abort(vector);

    // check length
    if (length <= GB_NEAR0 || !gb_isfinite(length))
    {
        // trace
        tb_trace_e("invalid length: %{float}", &length);

        // failed
        return tb_false;
    }

    // the self length
    gb_float_t length_self = gb_vector_length(vector);

    // check the self length
    if (length_self <= GB_NEAR0 || !gb_isfinite(length_self))
    {
        // trace
        tb_trace_e("invalid self length for vector: %{vector}", vector);

        // failed
        return tb_false;
    }

    // compute the scale
    gb_float_t scale = gb_div(length, length_self);

    // this scale is zero nearly? 
    if (scale <= GB_NEAR0)
    {
#ifdef TB_CONFIG_TYPE_FLOAT
        // compute the length using the double value
        tb_double_t     xx = gb_float_to_tb(vector->x);
        tb_double_t     yy = gb_float_to_tb(vector->y);
        tb_double_t     ll = tb_sqrt(xx * xx + yy * yy);
        tb_double_t     ss = gb_float_to_tb(length) / ll;

        // compute the new vector
        vector->x = tb_float_to_gb(xx * ss);
        vector->y = tb_float_to_gb(yy * ss);

        // warning 
        tb_trace_w("compute double scale: %{float} / %{float}, will be slower!", &length, &length_self);

        // ok
        return tb_true;
#else
        // trace
        tb_trace_e("invalid scale: %{float} / %{float}", &length, &length_self);
        
        // the invalid length
        return tb_false;
#endif
    }

    // compute the new vector
    vector->x = gb_mul(vector->x, scale);
    vector->y = gb_mul(vector->y, scale);

    // ok
    return tb_true;
}
tb_bool_t gb_vector_normalize(gb_vector_ref_t vector)
{
    return gb_vector_length_set(vector, GB_ONE);
}
gb_float_t gb_vector_dot(gb_vector_ref_t vector, gb_vector_ref_t other)
{
    // check
    tb_assert_abort(vector && other);

    // the factors
    gb_float_t ax = vector->x;
    gb_float_t ay = vector->y;
    gb_float_t bx = other->x;
    gb_float_t by = other->y;

    // done the dot product
    return gb_mul(ax, bx) + gb_mul(ay, by);
}
gb_float_t gb_vector_cross(gb_vector_ref_t vector, gb_vector_ref_t other)
{
    // check
    tb_assert_abort(vector && other);

    // the factors
    gb_float_t ax = vector->x;
    gb_float_t ay = vector->y;
    gb_float_t bx = other->x;
    gb_float_t by = other->y;

    // done the cross product
    return gb_mul(ax, by) - gb_mul(ay, bx);
}

