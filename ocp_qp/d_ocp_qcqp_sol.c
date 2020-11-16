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
#include "blasfeo/blasfeo_d_aux.h"

#include "hpipm/hpipm_d_ocp_qcqp_dim.h"
#include "hpipm/hpipm_d_ocp_qp.h"
#include "hpipm/hpipm_d_ocp_qcqp_sol.h"
#include "hpipm/hpipm_aux_string.h"
#include "hpipm/hpipm_aux_mem.h"



#define CREATE_STRVEC blasfeo_create_dvec
#define CVT_STRVEC2VEC blasfeo_unpack_dvec
#define CVT_VEC2STRVEC blasfeo_pack_dvec
#define OCP_QP d_ocp_qp
#define OCP_QCQP_DIM d_ocp_qcqp_dim
#define OCP_QCQP_SOL d_ocp_qcqp_sol
#define REAL double
#define STRVEC blasfeo_dvec
#define SIZE_STRVEC blasfeo_memsize_dvec
#define VECCP blasfeo_dveccp
#define VECSE blasfeo_dvecse

#define OCP_QCQP_SOL_STRSIZE d_ocp_qcqp_sol_strsize
#define OCP_QCQP_SOL_MEMSIZE d_ocp_qcqp_sol_memsize
#define OCP_QCQP_SOL_CREATE d_ocp_qcqp_sol_create
#define OCP_QCQP_SOL_COPY_ALL d_ocp_qcqp_sol_copy_all
#define OCP_QCQP_SOL_GET_ALL d_ocp_qcqp_sol_get_all
#define OCP_QCQP_SOL_SET_ALL d_ocp_qcqp_sol_set_all
#define OCP_QCQP_SOL_GET d_ocp_qcqp_sol_get
#define OCP_QCQP_SOL_GET_U d_ocp_qcqp_sol_get_u
#define OCP_QCQP_SOL_GET_X d_ocp_qcqp_sol_get_x
#define OCP_QCQP_SOL_GET_SL d_ocp_qcqp_sol_get_sl
#define OCP_QCQP_SOL_GET_SU d_ocp_qcqp_sol_get_su
#define OCP_QCQP_SOL_GET_PI d_ocp_qcqp_sol_get_pi
#define OCP_QCQP_SOL_GET_LAM_LB d_ocp_qcqp_sol_get_lam_lb
#define OCP_QCQP_SOL_GET_LAM_UB d_ocp_qcqp_sol_get_lam_ub
#define OCP_QCQP_SOL_GET_LAM_LG d_ocp_qcqp_sol_get_lam_lg
#define OCP_QCQP_SOL_GET_LAM_UG d_ocp_qcqp_sol_get_lam_ug
#define OCP_QCQP_SOL_SET d_ocp_qcqp_sol_set
#define OCP_QCQP_SOL_SET_U d_ocp_qcqp_sol_set_u
#define OCP_QCQP_SOL_SET_X d_ocp_qcqp_sol_set_x
#define OCP_QCQP_SOL_SET_SL d_ocp_qcqp_sol_set_sl
#define OCP_QCQP_SOL_SET_SU d_ocp_qcqp_sol_set_su


#include "x_ocp_qcqp_sol.c"

