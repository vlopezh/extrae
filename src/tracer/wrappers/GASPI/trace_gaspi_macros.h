/*****************************************************************************\
 *                        ANALYSIS PERFORMANCE TOOLS                         *
 *                                   Extrae                                  *
 *              Instrumentation package for parallel applications            *
 *****************************************************************************
 *     ___     This library is free software; you can redistribute it and/or *
 *    /  __         modify it under the terms of the GNU LGPL as published   *
 *   /  /  _____    by the Free Software Foundation; either version 2.1      *
 *  /  /  /     \   of the License, or (at your option) any later version.   *
 * (  (  ( B S C )                                                           *
 *  \  \  \_____/   This library is distributed in hope that it will be      *
 *   \  \__         useful but WITHOUT ANY WARRANTY; without even the        *
 *    \___          implied warranty of MERCHANTABILITY or FITNESS FOR A     *
 *                  PARTICULAR PURPOSE. See the GNU LGPL for more details.   *
 *                                                                           *
 * You should have received a copy of the GNU Lesser General Public License  *
 * along with this library; if not, write to the Free Software Foundation,   *
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA          *
 * The GNU LEsser General Public License is contained in the file COPYING.   *
 *                                 ---------                                 *
 *   Barcelona Supercomputing Center - Centro Nacional de Supercomputacion   *
\*****************************************************************************/

#ifndef __GASPI_TRACE_MACROS_H__
#define __GASPI_TRACE_MACROS_H__

#include "trace_macros.h"

#define TRACE_GASPI_CALLERS(evttime, evtvalue)                                 \
{                                                                              \
	if (evtvalue == EVT_BEGIN)                                                 \
	{                                                                          \
		Extrae_trace_callers(evttime, FOUR_CALLS_AGO, CALLER_MPI);             \
	}                                                                          \
}

#define TRACE_GASPI_EVENT(evttime,evttype,evtvalue,hwc_filter)                 \
{                                                                              \
	int thread_id = THREADID;                                                  \
	event_t evt;                                                               \
	if (tracejant)                                                             \
	{                                                                          \
		evt.time = (evttime);                                                  \
		evt.event = (evttype);                                                 \
		evt.value = (evtvalue);                                                \
		HARDWARE_COUNTERS_READ(thread_id, evt, hwc_filter);                    \
		BUFFER_INSERT(thread_id, TRACING_BUFFER(thread_id), evt);              \
		TRACE_GASPI_CALLERS(evttime, evtvalue);                                \
	}                                                                          \
}

#if USE_HARDWARE_COUNTERS

#define TRACE_GASPI_EVENTANDCOUNTERS(evttime,evttype,evtvalue,hwc_filter)      \
{                                                                              \
	TRACE_GASPI_EVENT(evttime,evttype,evtvalue,hwc_filter);                    \
}

#else

#define TRACE_GASPI_EVENTANDCOUNTERS(evttime,evttype,evtvalue,hwc_filter)      \
{                                                                              \
	TRACE_GASPI_EVENT(evttime,evttype,evtvalue,0);                             \
}

#endif

#endif /* __GASPI_TRACE_MACROS_H__ */

