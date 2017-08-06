/**************************************************************************************************
*                                                                                                 *
* This file is part of HPIPM.                                                                     *
*                                                                                                 *
* HPIPM -- High Performance Interior Point Method.                                                *
* Copyright (C) 2017 by Gianluca Frison.                                                          *
* Developed at IMTEK (University of Freiburg) under the supervision of Moritz Diehl.              *
* All rights reserved.                                                                            *
*                                                                                                 *
* HPIPM is free software; you can redistribute it and/or                                          *
* modify it under the terms of the GNU Lesser General Public                                      *
* License as published by the Free Software Foundation; either                                    *
* version 2.1 of the License, or (at your option) any later version.                              *
*                                                                                                 *
* HPIPM is distributed in the hope that it will be useful,                                        *
* but WITHOUT ANY WARRANTY; without even the implied warranty of                                  *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                            *
* See the GNU Lesser General Public License for more details.                                     *
*                                                                                                 *
* You should have received a copy of the GNU Lesser General Public                                *
* License along with HPIPM; if not, write to the Free Software                                    *
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA                  *
*                                                                                                 *
* Author: Gianluca Frison, gianluca.frison (at) imtek.uni-freiburg.de                             *                          
*                                                                                                 *
**************************************************************************************************/

void COMPUTE_GAMMA(struct OCP_QP *ocp_qp, struct COND_QP_OCP2DENSE_WORKSPACE *cond_ws)
	{

	int N = ocp_qp->N;

	// early return
	if(N<0)
		return;

	// extract input members
	int *nx = ocp_qp->nx;
	int *nu = ocp_qp->nu;
	struct STRMAT *BAbt = ocp_qp->BAbt;

	// extract memory members
	struct STRMAT *Gamma = cond_ws->Gamma;
	struct STRVEC *Gammab = cond_ws->Gammab;

	int ii, jj;

	int nu_tmp;

	nu_tmp = 0;
	ii = 0;
	// B & A & b
	GECP_LIBSTR(nu[0]+nx[0]+1, nx[1], &BAbt[0], 0, 0, &Gamma[0], 0, 0);
	// b
	ROWEX_LIBSTR(nx[1], 1.0, &Gamma[0], nu[0]+nx[0], 0, &Gammab[0], 0);

	nu_tmp += nu[0];
	ii++;

	for(ii=1; ii<N; ii++)
		{
		// TODO check for equal pointers and avoid copy

		// Gamma * A^T
		GEMM_NN_LIBSTR(nu_tmp+nx[0]+1, nx[ii+1], nx[ii], 1.0, &Gamma[ii-1], 0, 0, &BAbt[ii], nu[ii], 0, 0.0, &Gamma[ii], nu[ii], 0, &Gamma[ii], nu[ii], 0); // Gamma * A^T

		GECP_LIBSTR(nu[ii], nx[ii+1], &BAbt[ii], 0, 0, &Gamma[ii], 0, 0);

		nu_tmp += nu[ii];

		GEAD_LIBSTR(1, nx[ii+1], 1.0, &BAbt[ii], nu[ii]+nx[ii], 0, &Gamma[ii], nu_tmp+nx[0], 0);

		ROWEX_LIBSTR(nx[ii+1], 1.0, &Gamma[ii], nu_tmp+nx[0], 0, &Gammab[ii], 0);
		}
	
	return;

	}



void COND_BABT(struct OCP_QP *ocp_qp, struct STRMAT *BAbt2, struct STRVEC *b2, struct COND_QP_OCP2DENSE_WORKSPACE *cond_ws)
	{

	int N = ocp_qp->N;

	// early return
	if(N<0)
		return;

	// extract input members
	int *nx = ocp_qp->nx;
	int *nu = ocp_qp->nu;
	struct STRMAT *BAbt = ocp_qp->BAbt;

	// extract memory members
	struct STRMAT *Gamma = cond_ws->Gamma;
	struct STRVEC *Gammab = cond_ws->Gammab;

	int ii, jj;

	int nu_tmp;

	nu_tmp = 0;
	ii = 0;
	// B & A & b
	GECP_LIBSTR(nu[0]+nx[0]+1, nx[1], &BAbt[0], 0, 0, &Gamma[0], 0, 0);
	// b
	ROWEX_LIBSTR(nx[1], 1.0, &Gamma[0], nu[0]+nx[0], 0, &Gammab[0], 0);

	nu_tmp += nu[0];
	ii++;

	for(ii=1; ii<N; ii++)
		{
		// TODO check for equal pointers and avoid copy

		// Gamma * A^T
		GEMM_NN_LIBSTR(nu_tmp+nx[0]+1, nx[ii+1], nx[ii], 1.0, &Gamma[ii-1], 0, 0, &BAbt[ii], nu[ii], 0, 0.0, &Gamma[ii], nu[ii], 0, &Gamma[ii], nu[ii], 0); // Gamma * A^T

		GECP_LIBSTR(nu[ii], nx[ii+1], &BAbt[ii], 0, 0, &Gamma[ii], 0, 0);

		nu_tmp += nu[ii];

		GEAD_LIBSTR(1, nx[ii+1], 1.0, &BAbt[ii], nu[ii]+nx[ii], 0, &Gamma[ii], nu_tmp+nx[0], 0);

		ROWEX_LIBSTR(nx[ii+1], 1.0, &Gamma[ii], nu_tmp+nx[0], 0, &Gammab[ii], 0);
		}
	
	// B & A & b
	GECP_LIBSTR(nu_tmp+nx[0]+1, nx[N], &Gamma[N-1], 0, 0, &BAbt2[0], 0, 0);
	// b
	ROWEX_LIBSTR(nx[N], 1.0, &BAbt2[0], nu_tmp+nx[0], 0, &b2[0], 0);

	return;

	}



void COND_RSQRQ_N2NX3(struct OCP_QP *ocp_qp, struct STRMAT *RSQrq2, struct STRVEC *rq2, struct COND_QP_OCP2DENSE_WORKSPACE *cond_ws)
	{

	int N = ocp_qp->N;

	// early return
	if(N<0)
		return;

	// extract input members
	int *nx = ocp_qp->nx;
	int *nu = ocp_qp->nu;

	struct STRMAT *BAbt = ocp_qp->BAbt;
	struct STRMAT *RSQrq = ocp_qp->RSQrq;

	// extract memory members
	struct STRMAT *Gamma = cond_ws->Gamma;
	struct STRMAT *L = cond_ws->L;
	struct STRMAT *Lx = cond_ws->Lx;
	struct STRMAT *AL = cond_ws->AL;

	// declare workspace matrices XXX use cast on cond_ws matrices
//	struct STRMAT *Lx2;
//	struct STRMAT *AL2;

	// early return
	if(N==0)
		{
		GECP_LIBSTR(nu[0]+nx[0]+1, nu[0]+nx[0], &RSQrq[0], 0, 0, &RSQrq2[0], 0, 0);
		ROWEX_LIBSTR(nu[0]+nx[0], 1.0, &RSQrq[0], nu[0]+nx[0], 0, &rq2[0], 0);
		return;
		}

	int nn;

	int nu2 = 0; // sum of all nu
	for(nn=0; nn<=N; nn++)
		nu2 += nu[nn];
	
	int nub = nu2; // backward partial sum
	int nuf = 0; // forward partial sum

	// final stage 
	nub -= nu[N];

	// TODO g is not part of H !!!!!
	GECP_LIBSTR(nu[N]+nx[N]+1, nu[N]+nx[N], &RSQrq[N], 0, 0, &L[N], 0, 0);

	// D
	TRCP_L_LIBSTR(nu[N], &L[N], 0, 0, &RSQrq2[0], nuf, nuf);

	GEMM_NN_LIBSTR(nub+nx[0]+1, nu[N], nx[N], 1.0, &Gamma[N-1], 0, 0, &L[N], nu[N], 0, 0.0, &RSQrq2[0], nuf+nu[N], nuf, &RSQrq2[0], nuf+nu[N], nuf);

	// m
	GEAD_LIBSTR(1, nu[N], 1.0, &L[N], nu[N]+nx[N], 0, &RSQrq2[0], nu2+nx[0], nuf);

	nuf += nu[N];



	// middle stages 
	for(nn=0; nn<N-1; nn++)
		{	
		nub -= nu[N-nn-1];

//		d_create_strmat(nx[N-nn]+1, nx[N-nn], Lx, workspace+0);
//		d_create_strmat(nu[N-nn-1]+nx[N-nn-1]+1, nx[N-nn], AL, workspace+sizes[0]);

#if defined(LA_HIGH_PERFORMANCE)
		GECP_LIBSTR(nx[N-nn]+1, nx[N-nn], &L[N-nn], nu[N-nn], nu[N-nn], Lx, 0, 0);

		POTRF_L_MN_LIBSTR(nx[N-nn]+1, nx[N-nn], Lx, 0, 0, Lx, 0, 0);

		TRMM_RLNN_LIBSTR(nu[N-nn-1]+nx[N-nn-1]+1, nx[N-nn], 1.0, Lx, 0, 0, &BAbt[N-nn-1], 0, 0, AL, 0, 0);
#else
		POTRF_L_MN_LIBSTR(nx[N-nn]+1, nx[N-nn], &L[N-nn], nu[N-nn], nu[N-nn], Lx, 0, 0);

		TRMM_RLNN_LIBSTR(nu[N-nn-1]+nx[N-nn-1]+1, nx[N-nn], 1.0, Lx, 0, 0, &BAbt[N-nn-1], 0, 0, AL, 0, 0);
#endif
		GEAD_LIBSTR(1, nx[N-nn], 1.0, Lx, nx[N-nn], 0, AL, nu[N-nn-1]+nx[N-nn-1], 0);

		SYRK_LN_MN_LIBSTR(nu[N-nn-1]+nx[N-nn-1]+1, nu[N-nn-1]+nx[N-nn-1], nx[N-nn], 1.0, AL, 0, 0, AL, 0, 0, 1.0, &RSQrq[N-nn-1], 0, 0, &L[N-nn-1], 0, 0);

		// D
		TRCP_L_LIBSTR(nu[N-nn-1], &L[N-nn-1], 0, 0, &RSQrq2[0], nuf, nuf);

		GEMM_NN_LIBSTR(nub+nx[0]+1, nu[N-nn-1], nx[N-nn-1], 1.0, &Gamma[N-nn-2], 0, 0, &L[N-nn-1], nu[N-nn-1], 0, 0.0, &RSQrq2[0], nuf+nu[N-nn-1], nuf, &RSQrq2[0], nuf+nu[N-nn-1], nuf);

		// m
		GEAD_LIBSTR(1, nu[N-nn-1], 1.0, &L[N-nn-1], nu[N-nn-1]+nx[N-nn-1], 0, &RSQrq2[0], nu2+nx[0], nuf);

		nuf += nu[N-nn-1];

		}

	// first stage
	nn = N-1;

//	d_create_strmat(nx[N-nn]+1, nx[N-nn], Lx, workspace+0);
//	d_create_strmat(nu[N-nn-1]+nx[N-nn-1]+1, nx[N-nn], AL, workspace+sizes[0]);
	
#if defined(LA_HIGH_PERFORMANCE)
	GECP_LIBSTR(nx[N-nn]+1, nx[N-nn], &L[N-nn], nu[N-nn], nu[N-nn], Lx, 0, 0);

	POTRF_L_MN_LIBSTR(nx[N-nn]+1, nx[N-nn], Lx, 0, 0, Lx, 0, 0);

	TRMM_RLNN_LIBSTR(nu[N-nn-1]+nx[N-nn-1]+1, nx[N-nn], 1.0, Lx, 0, 0, &BAbt[N-nn-1], 0, 0, AL, 0, 0);
#else
	POTRF_L_MN_LIBSTR(nx[N-nn]+1, nx[N-nn], &L[N-nn], nu[N-nn], nu[N-nn], Lx, 0, 0);

	TRMM_RLNN_LIBSTR(nu[N-nn-1]+nx[N-nn-1]+1, nx[N-nn], 1.0, Lx, 0, 0, &BAbt[N-nn-1], 0, 0, AL, 0, 0);
#endif
	GEAD_LIBSTR(1, nx[N-nn], 1.0, Lx, nx[N-nn], 0, AL, nu[N-nn-1]+nx[N-nn-1], 0);

	SYRK_LN_MN_LIBSTR(nu[N-nn-1]+nx[N-nn-1]+1, nu[N-nn-1]+nx[N-nn-1], nx[N-nn], 1.0, AL, 0, 0, AL, 0, 0, 1.0, &RSQrq[N-nn-1], 0, 0, &L[N-nn-1], 0, 0);

	// D, M, m, P, p
//	GECP_LIBSTR(nu[0]+nx[0]+1, nu[0]+nx[0], &L[N-nn-1], 0, 0, &RSQrq2[0], nuf, nuf); // TODO dtrcp for 'rectangular' matrices
	TRCP_L_LIBSTR(nu[0]+nx[0], &L[N-nn-1], 0, 0, &RSQrq2[0], nuf, nuf); // TODO dtrcp for 'rectangular' matrices
	GECP_LIBSTR(1, nu[0]+nx[0], &L[N-nn-1], nu[0]+nx[0], 0, &RSQrq2[0], nuf+nu[0]+nx[0], nuf); // TODO dtrcp for 'rectangular' matrices
	// m p
	ROWEX_LIBSTR(nu2+nx[0], 1.0, &RSQrq2[0], nu2+nx[0], 0, &rq2[0], 0);

	return;

	}



#if 0
int d_cond_DCtd_workspace_size(int N, struct OCP_QP *qp_in, int idx_in)
	{

	// early return
	if(N<0)
		return 0;

	// extract input members
	int *nx = qp_in->nx + idx_in;
	int *ng = qp_in->ng + idx_in;

	int ii;
	int tmp;

	int size = 0;

	for(ii=0; ii<=N; ii++)
		{
		tmp = d_size_strmat(ng[ii], nx[ii]);
		tmp += d_size_strvec(nx[ii]);
		tmp += d_size_strvec(ng[ii]);
		size = tmp > size ? tmp : size;
		}

	return size;

	}
#endif



void COND_DCTD(struct OCP_QP *ocp_qp, int *idxb2, struct STRVEC *d_lb2, struct STRVEC *d_ub2, struct STRMAT *DCt2, struct STRVEC *d_lg2, struct STRVEC *d_ug2, struct COND_QP_OCP2DENSE_WORKSPACE *cond_ws)
	{

	int N = ocp_qp->N;

	// early return
	if(N<0)
		return;

	// extract input members
	int *nx = ocp_qp->nx;
	int *nu = ocp_qp->nu;
	int *nb = ocp_qp->nb;
	int *ng = ocp_qp->ng;

	int **idxb = ocp_qp->idxb;
	struct STRVEC *d_lb = ocp_qp->d_lb;
	struct STRVEC *d_ub = ocp_qp->d_ub;
	struct STRMAT *DCt = ocp_qp->DCt;
	struct STRVEC *d_lg = ocp_qp->d_lg;
	struct STRVEC *d_ug = ocp_qp->d_ug;

	// extract memory members
	struct STRMAT *Gamma = cond_ws->Gamma;
	struct STRVEC *Gammab = cond_ws->Gammab;
	struct STRVEC *tmp_ngM = cond_ws->tmp_ngM;


	REAL *d_lb3 = d_lb2->pa;
	REAL *d_ub3 = d_ub2->pa;
	REAL *d_lg3 = d_lg2->pa;
	REAL *d_ug3 = d_ug2->pa;

	REAL *ptr_d_lb;
	REAL *ptr_d_ub;
	
	int nu_tmp, ng_tmp;

	int ii, jj;

	int nu0, nx0, nb0, ng0;

	// problem size

	int nbb = nb[0]; // box that remain box constraints
	int nbg = 0; // box that becomes general constraints
	for(ii=1; ii<=N; ii++)
		for(jj=0; jj<nb[ii]; jj++)
			if(idxb[ii][jj]<nu[ii])
				nbb++;
			else
				nbg++;
	
	int nx2 = nx[0];
	int nu2 = nu[0];
	int ngg = ng[0];
	for(ii=1; ii<=N; ii++)
		{
		nu2 += nu[ii];
		ngg += ng[ii];
		}
	int ng2 = nbg + ngg;
	int nb2 = nbb;
	int nt2 = nb2 + ng2;

	// set constraint matrix to zero (it's 2 lower triangular matrices atm)
	GESE_LIBSTR(nu2+nx2, ng2, 0.0, &DCt2[0], 0, 0);

	// box constraints

	int idx_gammab = nx[0];
	for(ii=0; ii<N; ii++)
		idx_gammab += nu[ii];

	int ib = 0;
	int ig = 0;

	REAL tmp;
	int idx_g;

	// middle stages
	nu_tmp = 0;
	for(ii=0; ii<N; ii++)
		{
		nu0 = nu[N-ii];
		nb0 = nb[N-ii];
		ng0 = ng[N-ii];
		nu_tmp += nu0;
		ptr_d_lb = d_lb[N-ii].pa;
		ptr_d_ub = d_ub[N-ii].pa;
		for(jj=0; jj<nb0; jj++)
			{
			if(idxb[N-ii][jj]<nu0) // input: box constraint
				{
				d_lb3[ib] = ptr_d_lb[jj];
				d_ub3[ib] = ptr_d_ub[jj];
				idxb2[ib] = nu_tmp - nu0 + idxb[N-ii][jj];
				ib++;
				}
			else // state: general constraint
				{
				idx_g = idxb[N-ii][jj]-nu0;
				tmp = GEEX1_LIBSTR(&Gamma[N-1-ii], idx_gammab, idx_g);
				d_lg3[ig] = ptr_d_lb[jj] - tmp;
				d_ug3[ig] = ptr_d_ub[jj] - tmp;
				GECP_LIBSTR(idx_gammab, 1, &Gamma[N-ii-1], 0, idx_g, &DCt2[0], nu_tmp, ig);
				ig++;
				}
			}
		idx_gammab -= nu[N-1-ii];
		}

	// initial stage: both inputs and states as box constraints
	nu0 = nu[0];
	nb0 = nb[0];
	ng0 = ng[0];
	nu_tmp += nu0;
	ptr_d_lb = d_lb[0].pa;
	ptr_d_ub = d_ub[0].pa;
	for(jj=0; jj<nb0; jj++)
		{
		d_lb3[ib] = ptr_d_lb[jj];
		d_ub3[ib] = ptr_d_ub[jj];
		idxb2[ib] = nu_tmp - nu0 + idxb[0][jj];
		ib++;
		}

	// XXX for now, just shift after box-to-general constraints
	// better interleave them, to keep the block lower trianlgular structure !!!

	// general constraints

	char *c_ptr;

	nu_tmp = 0;
	ng_tmp = 0;
	for(ii=0; ii<N; ii++)
		{

		nx0 = nx[N-ii];
		nu0 = nu[N-ii];
		ng0 = ng[N-ii];

		if(ng0>0)
			{

			GECP_LIBSTR(nu0, ng0, &DCt[N-ii], 0, 0, DCt2, nu_tmp, nbg+ng_tmp);

			nu_tmp += nu0;

			GEMM_NN_LIBSTR(nu2+nx[0]-nu_tmp, ng0, nx0, 1.0, &Gamma[N-1-ii], 0, 0, &DCt[N-ii], nu0, 0, 0.0, DCt2, nu_tmp, nbg+ng_tmp, DCt2, nu_tmp, nbg+ng_tmp);

			VECCP_LIBSTR(ng0, &d_lg[N-ii], 0, d_lg2, nbg+ng_tmp);
			VECCP_LIBSTR(ng0, &d_ug[N-ii], 0, d_ug2, nbg+ng_tmp);

			GEMV_T_LIBSTR(nx0, ng0, 1.0, &DCt[N-ii], nu0, 0, &Gammab[N-ii-1], 0, 0.0, tmp_ngM, 0, tmp_ngM, 0);

			AXPY_LIBSTR(ng0, -1.0, tmp_ngM, 0, d_lg2, nbg+ng_tmp, d_lg2, nbg+ng_tmp);
			AXPY_LIBSTR(ng0, -1.0, tmp_ngM, 0, d_ug2, nbg+ng_tmp, d_ug2, nbg+ng_tmp);

			ng_tmp += ng0;
			
			}
		else
			{

			nu_tmp += nu0;

			}

		}

	ii = N;

	nx0 = nx[0];
	nu0 = nu[0];
	ng0 = ng[0];

	if(ng0>0)
		{

		GECP_LIBSTR(nu0+nx0, ng0, &DCt[0], 0, 0, DCt2, nu_tmp, nbg+ng_tmp);

		VECCP_LIBSTR(ng0, &d_lg[0], 0, d_lg2, nbg+ng_tmp);
		VECCP_LIBSTR(ng0, &d_ug[0], 0, d_ug2, nbg+ng_tmp);

//		ng_tmp += ng[N-ii];

		}

	return;

	}



void EXPAND_SOL(struct OCP_QP *ocp_qp, struct DENSE_QP_SOL *dense_qp_sol, struct STRVEC *ux, struct STRVEC *pi, struct STRVEC *lam_lb, struct STRVEC *lam_ub, struct STRVEC *lam_lg, struct STRVEC *lam_ug, struct STRVEC *t_lb, struct STRVEC *t_ub, struct STRVEC *t_lg, struct STRVEC *t_ug, struct STRVEC *tmp_nuxM, struct STRVEC *tmp_ngM)
	{

	int N = ocp_qp->N;
	int *nu = ocp_qp->nu;
	int *nx = ocp_qp->nx;
	int *nb = ocp_qp->nb;
	int *ng = ocp_qp->ng;

	struct STRMAT *BAbt = ocp_qp->BAbt;
	struct STRVEC *b = ocp_qp->b;
	int **idxb = ocp_qp->idxb;
	struct STRMAT *RSQrq = ocp_qp->RSQrq;
	struct STRVEC *rq = ocp_qp->rq;
	struct STRMAT *DCt = ocp_qp->DCt;

	struct STRVEC *vc = dense_qp_sol->v;
	struct STRVEC *pic = dense_qp_sol->pi;
	struct STRVEC *lam_lbc = dense_qp_sol->lam_lb;
	struct STRVEC *lam_ubc = dense_qp_sol->lam_ub;
	struct STRVEC *lam_lgc = dense_qp_sol->lam_lg;
	struct STRVEC *lam_ugc = dense_qp_sol->lam_ug;
	struct STRVEC *t_lbc = dense_qp_sol->t_lb;
	struct STRVEC *t_ubc = dense_qp_sol->t_ub;
	struct STRVEC *t_lgc = dense_qp_sol->t_lg;
	struct STRVEC *t_ugc = dense_qp_sol->t_ug;

	int ii, jj;

	// inputs & initial states
	int nu_tmp = 0;
	// final stages: copy only input
	for(ii=0; ii<N; ii++)
		{
		VECCP_LIBSTR(nu[N-ii], vc, nu_tmp, ux+(N-ii), 0);
		nu_tmp += nu[N-ii];
		}
	// first stage: copy input and state
	VECCP_LIBSTR(nu[0]+nx[0], vc, nu_tmp, ux+0, 0);

	// compute missing states by simulation within each block
	for(ii=0; ii<N; ii++)
		{
		GEMV_T_LIBSTR(nu[ii]+nx[ii], nx[ii+1], 1.0, BAbt+ii, 0, 0, ux+ii, 0, 1.0, b+ii, 0, ux+(ii+1), nu[ii+1]);
		}

	// slack variables and ineq lagrange multipliers
	int nbb = 0;
	int nbg = 0;
	int ngg = 0;
	REAL *ptr_lam_lb;
	REAL *ptr_lam_ub;
	REAL *ptr_lam_lg;
	REAL *ptr_lam_ug;
	REAL *ptr_t_lb;
	REAL *ptr_t_ub;
	REAL *ptr_t_lg;
	REAL *ptr_t_ug;
	REAL *ptr_lam_lbc = lam_lbc->pa;
	REAL *ptr_lam_ubc = lam_ubc->pa;
	REAL *ptr_lam_lgc = lam_lgc->pa;
	REAL *ptr_lam_ugc = lam_ugc->pa;
	REAL *ptr_t_lbc = t_lbc->pa;
	REAL *ptr_t_ubc = t_ubc->pa;
	REAL *ptr_t_lgc = t_lgc->pa;
	REAL *ptr_t_ugc = t_ugc->pa;
	// final stages
	for(ii=0; ii<N; ii++)
		{
		ptr_lam_lb = (lam_lb+(N-ii))->pa;
		ptr_lam_ub = (lam_ub+(N-ii))->pa;
		ptr_t_lb = (t_lb+(N-ii))->pa;
		ptr_t_ub = (t_ub+(N-ii))->pa;
		for(jj=0; jj<nb[N-ii]; jj++)
			{
			if(idxb[N-ii][jj]<nu[N-ii])
				{
				// box as box
				ptr_lam_lb[jj] = ptr_lam_lbc[nbb];
				ptr_lam_ub[jj] = ptr_lam_ubc[nbb];
				ptr_t_lb[jj] = ptr_t_lbc[nbb];
				ptr_t_ub[jj] = ptr_t_ubc[nbb];
				nbb++;
				}
			else
				{
				// box as general XXX change when decide where nbg are placed wrt ng
				ptr_lam_lb[jj] = ptr_lam_lgc[nbg];
				ptr_lam_ub[jj] = ptr_lam_ugc[nbg];
				ptr_t_lb[jj] = ptr_t_lgc[nbg];
				ptr_t_ub[jj] = ptr_t_ugc[nbg];
				nbg++;
				}
			}
		}
	// process as vectors ???
	for(ii=0; ii<N; ii++)
		{
		ptr_lam_lg = (lam_lg+(N-ii))->pa;
		ptr_lam_ug = (lam_ug+(N-ii))->pa;
		ptr_t_lg = (t_lg+(N-ii))->pa;
		ptr_t_ug = (t_ug+(N-ii))->pa;
		for(jj=0; jj<ng[N-ii]; jj++)
			{
			// gnenral as general
			ptr_lam_lg[jj] = ptr_lam_lgc[nbg+ngg];
			ptr_lam_ug[jj] = ptr_lam_ugc[nbg+ngg];
			ptr_t_lg[jj] = ptr_t_lgc[nbg+ngg];
			ptr_t_ug[jj] = ptr_t_ugc[nbg+ngg];
			ngg++;
			}
		}
	// first stage
	// all box as box
	VECCP_LIBSTR(nb[0], lam_lbc, nbb, lam_lb+0, 0);
	VECCP_LIBSTR(nb[0], lam_ubc, nbb, lam_ub+0, 0);
	VECCP_LIBSTR(nb[0], t_lbc, nbb, t_lb+0, 0);
	VECCP_LIBSTR(nb[0], t_ubc, nbb, t_ub+0, 0);
	// all general as general
	VECCP_LIBSTR(ng[0], lam_lgc, ngg, lam_lg+0, 0);
	VECCP_LIBSTR(ng[0], lam_ugc, ngg, lam_ug+0, 0);
	VECCP_LIBSTR(ng[0], t_lgc, ngg, t_lg+0, 0);
	VECCP_LIBSTR(ng[0], t_ugc, ngg, t_ug+0, 0);

	// lagrange multipliers of equality constraints
	REAL *ptr_nuxM = tmp_nuxM->pa;
	REAL *ptr_ngM = tmp_ngM->pa;
	// last stage
	SYMV_L_LIBSTR(nx[N], nx[N], 1.0, RSQrq+N, nu[N], nu[N], ux+N, nu[N], 1.0, rq+N, nu[N], pi+(N-1), 0);
	// TODO avoid to multiply by R and B (i.e. the u part)
	for(ii=0; ii<N-1; ii++)
		{
		ptr_lam_lb = (lam_lb+N-1-ii)->pa;
		ptr_lam_ub = (lam_ub+N-1-ii)->pa;
		ptr_lam_lg = (lam_lg+N-1-ii)->pa;
		ptr_lam_ug = (lam_ug+N-1-ii)->pa;
		VECCP_LIBSTR(nu[N-1-ii]+nx[N-1-ii], rq+(N-1-ii), 0, tmp_nuxM, 0);
		for(jj=0; jj<nb[N-1-ii]; jj++)
			ptr_nuxM[idxb[N-1-ii][jj]] += ptr_lam_ub[jj] - ptr_lam_lb[jj];
		SYMV_L_LIBSTR(nu[N-1-ii]+nx[N-1-ii], nu[N-1-ii]+nx[N-1-ii], 1.0, RSQrq+(N-1-ii), 0, 0, ux+(N-1-ii), 0, 1.0, tmp_nuxM, 0, tmp_nuxM, 0);
		GEMV_N_LIBSTR(nu[N-1-ii]+nx[N-1-ii], nx[N-ii], 1.0, BAbt+(N-1-ii), 0, 0, pi+(N-1-ii), 0, 1.0, tmp_nuxM, 0, tmp_nuxM, 0);
		for(jj=0; jj<ng[N-1-ii]; jj++)
			ptr_ngM[jj] = ptr_lam_ug[jj] - ptr_lam_lg[jj];
		GEMV_N_LIBSTR(nu[N-1-ii]+nx[N-1-ii], ng[N-1-ii], 1.0, DCt+(N-1-ii), 0, 0, tmp_ngM, 0, 1.0, tmp_nuxM, 0, tmp_nuxM, 0);

		VECCP_LIBSTR(nx[N-1-ii], tmp_nuxM, nu[N-1-ii], pi+(N-2-ii), 0);
		}
	

	return;

	}