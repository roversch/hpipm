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



#include <stdio.h>
#include <stdlib.h>

#include "blasfeo/blasfeo_target.h"
#include "blasfeo/blasfeo_common.h"
#include "blasfeo/blasfeo_d_aux.h"

#include "hpipm/hpipm_d_ocp_qcqp_dim.h"
#include "hpipm/hpipm_d_ocp_qcqp.h"
#include "hpipm/hpipm_aux_string.h"
#include "hpipm/hpipm_aux_mem.h"



#define DOUBLE_PRECISION



#define CREATE_STRMAT blasfeo_create_dmat
#define CREATE_STRVEC blasfeo_create_dvec
#define CVT_MAT2STRMAT blasfeo_pack_dmat
#define CVT_STRMAT2MAT blasfeo_unpack_dmat
#define CVT_TRAN_MAT2STRMAT blasfeo_pack_tran_dmat
#define CVT_TRAN_STRMAT2MAT blasfeo_unpack_tran_dmat
#define CVT_VEC2STRVEC blasfeo_pack_dvec
#define CVT_STRVEC2VEC blasfeo_unpack_dvec
#define GECP blasfeo_dgecp
#define GESE blasfeo_dgese
#define OCP_QCQP d_ocp_qcqp
#define OCP_QCQP_DIM d_ocp_qcqp_dim
#define REAL double
#define STRMAT blasfeo_dmat
#define STRVEC blasfeo_dvec
#define SIZE_STRMAT blasfeo_memsize_dmat
#define SIZE_STRVEC blasfeo_memsize_dvec
#define VECCP blasfeo_dveccp
#define VECSC blasfeo_dvecsc
#define VECSE blasfeo_dvecse

#define OCP_QCQP_STRSIZE d_ocp_qcqp_strsize
#define OCP_QCQP_MEMSIZE d_ocp_qcqp_memsize
#define OCP_QCQP_CREATE d_ocp_qcqp_create
#define OCP_QCQP_COPY_ALL d_ocp_qcqp_copy_all
#define OCP_QCQP_SET_ALL_ZERO d_ocp_qcqp_set_all_zero
#define OCP_QCQP_SET_RHS_ZERO d_ocp_qcqp_set_rhs_zero
#define OCP_QCQP_SET d_ocp_qcqp_set
#define OCP_QCQP_SET_EL d_ocp_qcqp_set_el
#define OCP_QCQP_SET_A d_ocp_qcqp_set_A
#define OCP_QCQP_SET_B d_ocp_qcqp_set_B
#define OCP_QCQP_SET_BVEC d_ocp_qcqp_set_b
#define OCP_QCQP_SET_Q d_ocp_qcqp_set_Q
#define OCP_QCQP_SET_S d_ocp_qcqp_set_S
#define OCP_QCQP_SET_R d_ocp_qcqp_set_R
#define OCP_QCQP_SET_QVEC d_ocp_qcqp_set_q
#define OCP_QCQP_SET_RVEC d_ocp_qcqp_set_r
#define OCP_QCQP_SET_LB d_ocp_qcqp_set_lb
#define OCP_QCQP_SET_LB_MASK d_ocp_qcqp_set_lb_mask
#define OCP_QCQP_SET_UB d_ocp_qcqp_set_ub
#define OCP_QCQP_SET_UB_MASK d_ocp_qcqp_set_ub_mask
#define OCP_QCQP_SET_LBX d_ocp_qcqp_set_lbx
#define OCP_QCQP_SET_LBX_MASK d_ocp_qcqp_set_lbx_mask
#define OCP_QCQP_SET_EL_LBX d_ocp_qcqp_set_el_lbx
#define OCP_QCQP_SET_UBX d_ocp_qcqp_set_ubx
#define OCP_QCQP_SET_UBX_MASK d_ocp_qcqp_set_ubx_mask
#define OCP_QCQP_SET_EL_UBX d_ocp_qcqp_set_el_ubx
#define OCP_QCQP_SET_LBU d_ocp_qcqp_set_lbu
#define OCP_QCQP_SET_LBU_MASK d_ocp_qcqp_set_lbu_mask
#define OCP_QCQP_SET_UBU d_ocp_qcqp_set_ubu
#define OCP_QCQP_SET_UBU_MASK d_ocp_qcqp_set_ubu_mask
#define OCP_QCQP_SET_IDXB d_ocp_qcqp_set_idxb
#define OCP_QCQP_SET_IDXBX d_ocp_qcqp_set_idxbx
#define OCP_QCQP_SET_JBX d_ocp_qcqp_set_Jbx
#define OCP_QCQP_SET_IDXBU d_ocp_qcqp_set_idxbu
#define OCP_QCQP_SET_JBU d_ocp_qcqp_set_Jbu
#define OCP_QCQP_SET_C d_ocp_qcqp_set_C
#define OCP_QCQP_SET_D d_ocp_qcqp_set_D
#define OCP_QCQP_SET_LG d_ocp_qcqp_set_lg
#define OCP_QCQP_SET_LG_MASK d_ocp_qcqp_set_lg_mask
#define OCP_QCQP_SET_UG d_ocp_qcqp_set_ug
#define OCP_QCQP_SET_UG_MASK d_ocp_qcqp_set_ug_mask
#define OCP_QCQP_SET_QQ d_ocp_qcqp_set_Qq
#define OCP_QCQP_SET_SQ d_ocp_qcqp_set_Sq
#define OCP_QCQP_SET_RQ d_ocp_qcqp_set_Rq
#define OCP_QCQP_SET_QQVEC d_ocp_qcqp_set_qq
#define OCP_QCQP_SET_RQVEC d_ocp_qcqp_set_rq
#define OCP_QCQP_SET_UQ d_ocp_qcqp_set_uq
#define OCP_QCQP_SET_UQ_MASK d_ocp_qcqp_set_uq_mask
#define OCP_QCQP_SET_ZL d_ocp_qcqp_set_Zl
#define OCP_QCQP_SET_ZU d_ocp_qcqp_set_Zu
#define OCP_QCQP_SET_ZLVEC d_ocp_qcqp_set_zl
#define OCP_QCQP_SET_ZUVEC d_ocp_qcqp_set_zu
#define OCP_QCQP_SET_IDXS d_ocp_qcqp_set_idxs
#define OCP_QCQP_SET_JSBU d_ocp_qcqp_set_Jsbu
#define OCP_QCQP_SET_JSBX d_ocp_qcqp_set_Jsbx
#define OCP_QCQP_SET_JSG d_ocp_qcqp_set_Jsg
#define OCP_QCQP_SET_JSQ d_ocp_qcqp_set_Jsq
#define OCP_QCQP_SET_LLS d_ocp_qcqp_set_lls
#define OCP_QCQP_SET_LLS_MASK d_ocp_qcqp_set_lls_mask
#define OCP_QCQP_SET_LUS d_ocp_qcqp_set_lus
#define OCP_QCQP_SET_LUS_MASK d_ocp_qcqp_set_lus_mask
// getters
#define OCP_QCQP_GET d_ocp_qcqp_get
#define OCP_QCQP_GET_A d_ocp_qcqp_get_A
#define OCP_QCQP_GET_B d_cvt_ocp_qcqp_B
#define OCP_QCQP_GET_BVEC d_cvt_ocp_qcqp_b
#define OCP_QCQP_GET_Q d_cvt_ocp_qcqp_Q
#define OCP_QCQP_GET_S d_cvt_ocp_qcqp_S
#define OCP_QCQP_GET_R d_cvt_ocp_qcqp_R
#define OCP_QCQP_GET_QVEC d_cvt_ocp_qcqp_q
#define OCP_QCQP_GET_RVEC d_cvt_ocp_qcqp_r
#define OCP_QCQP_GET_LBX d_ocp_qcqp_get_lbx
#define OCP_QCQP_GET_UBX d_ocp_qcqp_get_ubx
#define OCP_QCQP_GET_LBU d_cvt_ocp_qcqp_lbu
#define OCP_QCQP_GET_UBU d_cvt_ocp_qcqp_ubu
#define OCP_QCQP_GET_IDXB d_cvt_ocp_qcqp_idxb
#define OCP_QCQP_GET_IDXBX d_cvt_ocp_qcqp_idxbx
#define OCP_QCQP_GET_JBX d_ocp_qcqp_get_Jbx
#define OCP_QCQP_GET_IDXBU d_cvt_ocp_qcqp_idxbu
#define OCP_QCQP_GET_JBU d_ocp_qcqp_get_Jbu
#define OCP_QCQP_GET_LB d_cvt_ocp_qcqp_lb
#define OCP_QCQP_GET_UB d_cvt_ocp_qcqp_ub
#define OCP_QCQP_GET_C d_cvt_ocp_qcqp_C
#define OCP_QCQP_GET_D d_cvt_ocp_qcqp_D
#define OCP_QCQP_GET_LG d_cvt_ocp_qcqp_lg
#define OCP_QCQP_GET_UG d_cvt_ocp_qcqp_ug
#define OCP_QCQP_GET_ZL d_cvt_ocp_qcqp_Zl
#define OCP_QCQP_GET_ZU d_cvt_ocp_qcqp_Zu
#define OCP_QCQP_GET_ZLVEC d_cvt_ocp_qcqp_zl
#define OCP_QCQP_GET_ZUVEC d_cvt_ocp_qcqp_zu
#define OCP_QCQP_GET_IDXS d_cvt_ocp_qcqp_idxs
#define OCP_QCQP_GET_JSBU d_ocp_qcqp_get_Jsbu
#define OCP_QCQP_GET_JSBX d_ocp_qcqp_get_Jsbx
#define OCP_QCQP_GET_JSG d_ocp_qcqp_get_Jsg
#define OCP_QCQP_GET_LLS d_cvt_ocp_qcqp_lls
#define OCP_QCQP_GET_LUS d_cvt_ocp_qcqp_lus



#include "x_ocp_qcqp.c"

