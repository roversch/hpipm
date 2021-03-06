###################################################################################################
#                                                                                                 #
# This file is part of HPIPM.                                                                     #
#                                                                                                 #
# HPIPM -- High-Performance Interior Point Method.                                                #
# Copyright (C) 2017-2018 by Gianluca Frison.                                                     #
# Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              #
# All rights reserved.                                                                            #
#                                                                                                 #
# This program is free software: you can redistribute it and/or modify                            #
# it under the terms of the GNU General Public License as published by                            #
# the Free Software Foundation, either version 3 of the License, or                               #
# (at your option) any later version                                                              #.
#                                                                                                 #
# This program is distributed in the hope that it will be useful,                                 #
# but WITHOUT ANY WARRANTY; without even the implied warranty of                                  #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                   #
# GNU General Public License for more details.                                                    #
#                                                                                                 #
# You should have received a copy of the GNU General Public License                               #
# along with this program.  If not, see <https://www.gnu.org/licenses/>.                          #
#                                                                                                 #
# The authors designate this particular file as subject to the "Classpath" exception              #
# as provided by the authors in the LICENSE file that accompained this code.                      #
#                                                                                                 #
# Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             #
#                                                                                                 #
###################################################################################################

cmake_minimum_required(VERSION 2.8.11)

cmake_policy(SET CMP0048 NEW)
project(hpipm C)

# Options

# BLAS and LAPACK version (for LA=BLAS in BLASFEO)
set(REF_BLAS 0 CACHE STRING "Set CPU architecture target")
# set(REF_BLAS OPENBLAS CACHE STRING "Set CPU architecture target")
# set(REF_BLAS NETLIB   CACHE STRING "Set CPU architecture target")
# set(REF_BLAS MKL      CACHE STRING "Set CPU architecture target")
# set(REF_BLAS BLIS     CACHE STRING "Set CPU architecture target")
# set(REF_BLAS ATLAS    CACHE STRING "Set CPU architecture target")


set(HPIPM_TESTING OFF CACHE BOOL "Tests disabled")

# Target architecture
# set(TARGET AVX CACHE STRING "Set CPU architecture target")
set(TARGET GENERIC CACHE STRING "Set CPU architecture target")




# enable runtine checks
set(RUNTIME_CHECKS 0)
#set(RUNTIME_CHECKS 1)

## compiler flags
#set(CMAKE_C_FLAGS "")
#
## optimization flags
# common flags
if(CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif()
# target-specific flags
if(${TARGET} MATCHES AVX)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DTARGET_AVX")
	if(CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64 -mavx")
	endif()
else()
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DTARGET_GENERIC")
endif()

#
if(${REF_BLAS} MATCHES 0)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
endif(${REF_BLAS} MATCHES 0)
if(${REF_BLAS} MATCHES OPENBLAS)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DREF_BLAS_OPENBLAS -I/opt/openblas/include")
endif(${REF_BLAS} MATCHES OPENBLAS)
if(${REF_BLAS} MATCHES BLIS)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DREF_BLAS_BLIS -std=c99")
endif(${REF_BLAS} MATCHES BLIS)
if(${REF_BLAS} MATCHES NETLIB)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DREF_BLAS_NETLIB")
endif(${REF_BLAS} MATCHES NETLIB)
if(${REF_BLAS} MATCHES MKL)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DREF_BLAS_MKL -m64 -I/opt/intel/mkl/include")
endif(${REF_BLAS} MATCHES MKL)
if(${REF_BLAS} MATCHES ATLAS)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DREF_BLAS_ATLAS")
endif(${REF_BLAS} MATCHES ATLAS)

#
if(${RUNTIME_CHECKS} MATCHES 1)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DRUNTIME_CHECKS")
endif(${RUNTIME_CHECKS} MATCHES 1)


# source files
# cond
file(GLOB COND_SRC
	${PROJECT_SOURCE_DIR}/cond/d_cond.c
	${PROJECT_SOURCE_DIR}/cond/d_cond_aux.c
	${PROJECT_SOURCE_DIR}/cond/d_part_cond.c
	${PROJECT_SOURCE_DIR}/cond/s_cond.c
	${PROJECT_SOURCE_DIR}/cond/s_cond_aux.c
	${PROJECT_SOURCE_DIR}/cond/s_part_cond.c
	)
# dense qp
file(GLOB DENSE_QP_SRC
	# double
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qp.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qp_dim.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qp_sol.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qp_kkt.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qp_ipm.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qp_res.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qp_utils.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qcqp_dim.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qcqp.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qcqp_sol.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qcqp_res.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qcqp_ipm.c
	${PROJECT_SOURCE_DIR}/dense_qp/d_dense_qcqp_utils.c
	# single
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qp.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qp_dim.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qp_sol.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qp_kkt.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qp_ipm.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qp_res.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qp_utils.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qcqp_dim.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qcqp.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qcqp_sol.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qcqp_res.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qcqp_ipm.c
	${PROJECT_SOURCE_DIR}/dense_qp/s_dense_qcqp_utils.c
	)
# core ipm
if(${TARGET} MATCHES AVX)
	file(GLOB IPM_CORE_SRC
		${PROJECT_SOURCE_DIR}/ipm_core/d_core_qp_ipm_aux_avx.c
		${PROJECT_SOURCE_DIR}/ipm_core/d_core_qp_ipm.c
		${PROJECT_SOURCE_DIR}/ipm_core/s_core_qp_ipm_aux_avx.c
		${PROJECT_SOURCE_DIR}/ipm_core/s_core_qp_ipm.c
		)
else(${TARGET} MATCHES AVX)
	file(GLOB IPM_CORE_SRC
		${PROJECT_SOURCE_DIR}/ipm_core/d_core_qp_ipm_aux.c
		${PROJECT_SOURCE_DIR}/ipm_core/d_core_qp_ipm.c
		${PROJECT_SOURCE_DIR}/ipm_core/s_core_qp_ipm_aux.c
		${PROJECT_SOURCE_DIR}/ipm_core/s_core_qp_ipm.c
		)
endif(${TARGET} MATCHES AVX)
# ocp qp
file(GLOB OCP_QP_SRC
	# double
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qp.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qp_dim.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qp_sol.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qp_kkt.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qp_ipm.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qp_res.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qp_utils.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qcqp.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qcqp_dim.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qcqp_sol.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qcqp_ipm.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qcqp_res.c
	${PROJECT_SOURCE_DIR}/ocp_qp/d_ocp_qcqp_utils.c
	# single
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qp.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qp_dim.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qp_sol.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qp_kkt.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qp_ipm.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qp_res.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qp_utils.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qcqp.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qcqp_dim.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qcqp_sol.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qcqp_ipm.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qcqp_res.c
	${PROJECT_SOURCE_DIR}/ocp_qp/s_ocp_qcqp_utils.c
#	${PROJECT_SOURCE_DIR}/ocp_qp/m_ocp_qp.c
#	${PROJECT_SOURCE_DIR}/ocp_qp/m_ocp_qp_kkt.c
#	${PROJECT_SOURCE_DIR}/ocp_qp/m_ocp_qp_ipm_hard.c
	)
# tree qp
file(GLOB TREE_OCP_QP_SRC
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/scenario_tree.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/d_tree_ocp_qp.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/d_tree_ocp_qp_dim.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/d_tree_ocp_qp_sol.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/d_tree_ocp_qp_kkt.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/d_tree_ocp_qp_ipm.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/d_tree_ocp_qp_res.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/s_tree_ocp_qp.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/s_tree_ocp_qp_dim.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/s_tree_ocp_qp_sol.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/s_tree_ocp_qp_kkt.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/s_tree_ocp_qp_ipm.c
	${PROJECT_SOURCE_DIR}/tree_ocp_qp/s_tree_ocp_qp_res.c
	)
# auxiliary
file(GLOB AUXILIARY_SRC
	${PROJECT_SOURCE_DIR}/auxiliary/aux_string.c
	${PROJECT_SOURCE_DIR}/auxiliary/aux_mem.c
	${PROJECT_SOURCE_DIR}/auxiliary/timing.c
	)

set(HPIPM_SRC ${COND_SRC} ${DENSE_QP_SRC} ${IPM_CORE_SRC} ${OCP_QP_SRC} ${TREE_OCP_QP_SRC} ${AUXILIARY_SRC})

add_library(hpipm ${HPIPM_SRC})
target_include_directories(hpipm
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${HPIPM_HEADERS_INSTALLATION_DIRECTORY}/hpipm>)
target_link_libraries(hpipm blasfeo)

install(TARGETS hpipm EXPORT hpipmConfig
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin)

install(EXPORT hpipmConfig DESTINATION share/hpipm/cmake)

file(GLOB_RECURSE HPIPM_HEADERS "include/*.h")
install(FILES ${HPIPM_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/hpipm)

# test problems
if(HPIPM_TESTING MATCHES ON)
	add_subdirectory(test_problems)
endif()
