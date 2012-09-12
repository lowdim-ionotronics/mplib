c     *  potentials_f.h  2010-07-28  Image forces unary and binary potentials 
c     *                              fortran header file
c     *
c     * Copyright (C) 2010 Svyatoslav Kondrat (Valiska)
c     *
c     * This program is free software; you can redistribute it and/or modify
c     * it under the terms of the GNU General Public License as published by
c     * the Free Software Foundation; either version 2 of the License, or (at
c     * your option) any later version.
c     *
c     * This program is distributed in the hope that it will be useful, but
c     * WITHOUT ANY WARRANTY; without even the implied warranty of
c     * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
c     * General Public License for more details.
c     *
c     * You should have received a copy of the GNU General Public License
c     * along with this program; if not, write to the Free Software
c     * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
c
c
#ifdef MPLIB_HAVE_UNARY
       double precision mplib_potential_unary
#endif
c
#ifdef MPLIB_HAVE_BINARY
       double precision mplib_potential_binary
#endif
c
#ifdef MPLIB_HAVE_UNARY
       double precision mplib_cylinder_u1
#endif
c
#ifdef MPLIB_HAVE_BINARY
       double precision mplib_cylinder_u2
#endif
c
