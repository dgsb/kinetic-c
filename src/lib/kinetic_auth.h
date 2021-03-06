/*
* kinetic-c
* Copyright (C) 2015 Seagate Technology.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*
*/

#ifndef _KINETIC_AUTH_H
#define _KINETIC_AUTH_H

#include "kinetic_types_internal.h"

KineticStatus KineticAuth_EnsureSslEnabled(KineticSessionConfig const * const config);
KineticStatus KineticAuth_PopulateHmac(KineticSessionConfig const * const config, KineticRequest * const request);
KineticStatus KineticAuth_PopulatePin(KineticSessionConfig const * const config, KineticRequest * const request, ByteArray pin);
KineticStatus KineticAuth_PopulateTag(ByteBuffer * const tag, KineticAlgorithm algorithm, ByteArray const * const key);

#endif // _KINETIC_AUTH_H
