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
 * @file        mesh_vertex.h
 * @ingroup     core
 *
 */
#ifndef GB_CORE_IMPL_MESH_VERTEX_H
#define GB_CORE_IMPL_MESH_VERTEX_H

/* //////////////////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../mesh.h"

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_enter__

/* //////////////////////////////////////////////////////////////////////////////////////
 * macros
 */

/* //////////////////////////////////////////////////////////////////////////////////////
 * types
 */

// the mesh vertex list type
typedef struct{}*           gb_mesh_vertex_list_ref_t;

/* //////////////////////////////////////////////////////////////////////////////////////
 * interfaces
 */

/* init the mesh vertex list 
 *
 * @param func              the item func
 *
 * @returned                the vertex list
 */
gb_mesh_vertex_list_ref_t   gb_mesh_vertex_list_init(tb_item_func_t func);

/* exit the mesh vertex list
 *
 * @param list              the vertex list
 */
tb_void_t                   gb_mesh_vertex_list_exit(gb_mesh_vertex_list_ref_t list);

/* clear the mesh vertex list
 *
 * @param list              the vertex list
 */
tb_void_t                   gb_mesh_vertex_list_clear(gb_mesh_vertex_list_ref_t list);

/*! the mesh vertex iterator
 *
 * @param list              the list
 *
 * @return                  the mesh vertex iterator
 */
tb_iterator_ref_t           gb_mesh_vertex_list_itor(gb_mesh_vertex_list_ref_t list);

/*! the mesh vertex count
 *
 * @param list              the list
 *
 * @return                  the item count
 */
tb_size_t                   gb_mesh_vertex_list_size(gb_mesh_vertex_list_ref_t list);

/*! the mesh vertex maximum count
 *
 * @param list              the list
 *
 * @return                  the item max count
 */
tb_size_t                   gb_mesh_vertex_list_maxn(gb_mesh_vertex_list_ref_t list);

/*! make a bare vertex without edges
 *
 * @param list              the list
 *
 * @return                  the new vertex
 */
gb_mesh_vertex_ref_t        gb_mesh_vertex_list_make(gb_mesh_vertex_list_ref_t list);

/*! kill the vertex, release the storage
 *
 * @param list              the list
 * @param vertex            the vertex
 */
tb_void_t                   gb_mesh_vertex_list_kill(gb_mesh_vertex_list_ref_t list, gb_mesh_vertex_ref_t vertex);

/* //////////////////////////////////////////////////////////////////////////////////////
 * extern
 */
__tb_extern_c_leave__

#endif


