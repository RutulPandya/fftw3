/*
 * Copyright (c) 2002 Matteo Frigo
 * Copyright (c) 2002 Steven G. Johnson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* $Id: ct.h,v 1.5 2002-06-16 22:30:18 athena Exp $ */

/* Cooley-Tukey variants */
union kct {
     kdft_dit dit;
     kdft_dif dif;
     kdft_difsq difsq;
     kdft_dit_k7 dit_k7;
};

typedef struct {
     solver super;
     const char *nam;
     const ct_desc *desc;
     union kct k;
} solver_ct;

typedef struct {
     plan_dft super;
     union kct k;
     plan *cld;
     R *W;
     uint r, m, vl;
     int is, os, ivs, ovs, iios;
     stride ios, vs;
     const solver_ct *slv;
     twid *td;
} plan_ct;

/* data type describing a generic Cooley-Tukey solver */
typedef struct
{
     problem *(*mkcld)(const solver_ct *, const problem_dft *p);
     void (*finish)(plan_ct *ego);
     int (*applicable)(const solver_ct *ego, const problem *p);
     dftapply apply;
}
ctadt;

int X(dft_ct_applicable)(const solver_ct *ego, const problem *p_);

plan *X(mkplan_dft_ct)(const solver_ct *ego,
                       const problem *p_,
                       planner *plnr,
                       const ctadt *adt);

solver *X(mksolver_dft_ct)(union kct k, const ct_desc *desc,
                           const char *nam, const solver_adt *adt);

