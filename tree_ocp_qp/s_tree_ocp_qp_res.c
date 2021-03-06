/**************************************************************************************************
*                                                                                                 *
* This file is part of HPIPM.                                                                     *
*                                                                                                 *
* HPIPM -- High-Performance Interior Point Method.                                                *
* Copyright (C) 2019 by Gianluca Frison.                                                          *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* The 2-Clause BSD License                                                                        *
*                                                                                                 *
* Redistribution and use in source and binary forms, with or without                              *
* modification, are permitted provided that the following conditions are met:                     *
*                                                                                                 *
* 1. Redistributions of source code must retain the above copyright notice, this                  *
*    list of conditions and the following disclaimer.                                             *
* 2. Redistributions in binary form must reproduce the above copyright notice,                    *
*    this list of conditions and the following disclaimer in the documentation                    *
*    and/or other materials provided with the distribution.                                       *
*                                                                                                 *
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND                 *
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED                   *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                          *
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR                 *
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES                  *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;                    *
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND                     *
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                      *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS                   *
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                                    *
*                                                                                                 *
* Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             *
*                                                                                                 *
**************************************************************************************************/



#include <stdlib.h>
#include <stdio.h>

#include "blasfeo/blasfeo_target.h"
#include "blasfeo/blasfeo_common.h"
#include "blasfeo/blasfeo_s_aux.h"

#include "hpipm/hpipm_s_tree_ocp_qp_dim.h"
#include "hpipm/hpipm_s_tree_ocp_qp_res.h"



#define CREATE_STRVEC blasfeo_create_svec
#define CVT_STRVEC2VEC blasfeo_unpack_svec
#define TREE_OCP_QP_DIM s_tree_ocp_qp_dim
#define TREE_OCP_QP_RES s_tree_ocp_qp_res
#define TREE_OCP_QP_RES_WORKSPACE s_tree_ocp_qp_res_workspace
#define REAL float
#define SIZE_STRVEC blasfeo_memsize_svec
#define STRVEC blasfeo_svec



#define MEMSIZE_TREE_OCP_QP_RES s_memsize_tree_ocp_qp_res
#define CREATE_TREE_OCP_QP_RES s_create_tree_ocp_qp_res
#define MEMSIZE_TREE_OCP_QP_RES_WORKSPACE s_memsize_tree_ocp_qp_res_workspace
#define CREATE_TREE_OCP_QP_RES_WORKSPACE s_create_tree_ocp_qp_res_workspace
#define CVT_TREE_OCP_QP_RES_TO_COLMAJ s_cvt_tree_ocp_qp_res_to_colmaj
#define CVT_TREE_OCP_QP_RES_TO_ROWMAJ s_cvt_tree_ocp_qp_res_to_rowmaj



#include "x_tree_ocp_qp_res.c"


