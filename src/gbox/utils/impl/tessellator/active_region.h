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
 * Copyright (C) 2009 - 2015, ruki All rights reserved.
 *
 * @author      ruki
 * @file        active_region.h
 * @ingroup     utils
 */
#ifndef GB_UTILS_IMPL_TESSELLATOR_ACTIVE_REGION_H
#define GB_UTILS_IMPL_TESSELLATOR_ACTIVE_REGION_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/* make the active regions and all regions are sorted
 *
 * @param impl                      the tessellator impl
 * @param bounds                    the bounds of the polygon
 *
 * @return                          tb_true or tb_false
 */
tb_bool_t                           gb_tessellator_active_regions_make(gb_tessellator_impl_t* impl, gb_rect_ref_t bounds);

/* find the region containing the given edge from the regions
 *
 *         =>
 * .                .
 * .                .
 * .     region     .
 * .                .
 * .         .      .
 * .       .        .
 * .     . edge     .
 *
 * @param impl                      the tessellator impl
 * @param edge                      the edge
 *
 * @return                          the region
 */
gb_tessellator_active_region_ref_t  gb_tessellator_active_regions_find(gb_tessellator_impl_t* impl, gb_mesh_edge_ref_t edge);

/* get the left region of the given region
 *
 * @param impl                      the tessellator impl
 * @param region                    the region
 *
 * @return                          the left region
 */
gb_tessellator_active_region_ref_t  gb_tessellator_active_regions_left(gb_tessellator_impl_t* impl, gb_tessellator_active_region_ref_t region);

/* get the right region of the given region
 *
 * @param impl                      the tessellator impl
 * @param region                    the region
 *
 * @return                          the right region
 */
gb_tessellator_active_region_ref_t  gb_tessellator_active_regions_right(gb_tessellator_impl_t* impl, gb_tessellator_active_region_ref_t region);

/* the region1 is in the left of the region2
 *
 * @param impl                      the tessellator impl
 * @param region1                   the region1
 * @param region2                   the region2
 *
 * @return                          tb_true or tb_false
 */
tb_bool_t                           gb_tessellator_active_regions_in_left(gb_tessellator_impl_t* impl, gb_tessellator_active_region_ref_t region1, gb_tessellator_active_region_ref_t region2);

/* remove region from the regions
 *
 * @param impl                      the tessellator impl
 * @param region                    the removed region
 */
tb_void_t                           gb_tessellator_active_regions_remove(gb_tessellator_impl_t* impl, gb_tessellator_active_region_ref_t region);

/* insert a new active region in ascending order
 *
 * @code
    {
        // init region
        gb_tessellator_active_region_t region;
        region.edge         = ...; //< must be initialized
        region.inside       = 0;
        region.winding      = 0;
        ...

        // insert region
        gb_tessellator_active_regions_insert(active_regions, &region);
    }
 * @endcode
 *
 * @param impl                      the tessellator impl
 * @param region                    the initialized region, but be not real region
 *
 * @return                          the real new region
 */
gb_tessellator_active_region_ref_t  gb_tessellator_active_regions_insert(gb_tessellator_impl_t* impl, gb_tessellator_active_region_ref_t region);

/* insert a new active region after the previous region in ascending order
 *
 * r0 ----> r1 ------> r2 -------> r3 ---> ... ---->
 *                 region_prev
 *                     |----------------->
 *                           insert
 *
 * @param impl                      the tessellator impl
 * @param region_prev               the previous region
 * @param region                    the initialized region, but be not real region
 *
 * @return                          the real new region
 */
gb_tessellator_active_region_ref_t  gb_tessellator_active_regions_insert_after(gb_tessellator_impl_t* impl, gb_tessellator_active_region_ref_t region_prev, gb_tessellator_active_region_ref_t region);

#ifdef __gb_debug__
/* check the active regions
 *
 * @param impl                      the tessellator impl
 */
tb_void_t                           gb_tessellator_active_regions_check(gb_tessellator_impl_t* impl);
#endif

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_leave__

#endif


