//------------------------------------------------------------------------------
/// Copyright (c) WAGO Kontakttechnik GmbH & Co. KG
///
/// PROPRIETARY RIGHTS are involved in the subject matter of this material.
/// All manufacturing, reproduction, use and sales rights pertaining to this
/// subject matter are governed by the license agreement. The recipient of this
/// software implicitly accepts the terms of the license.
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
///
///  \file     EventDispatcher.c
///
///  \version  $Revision: 4550 $
///
///  \brief
///
///  \author   <$Author$> : WAGO Kontakttechnik GmbH & Co. KG
//------------------------------------------------------------------------------

#ifndef _EVENTS_H
#define _EVENTS_H

#include <stdint.h>
#include <stddef.h>

typedef void *tEventSource;
typedef uint32_t tEventId;
typedef void *tEventArgs;

typedef void (*tEventHandler)(tEventSource source, tEventId id, tEventArgs arg, void* userData);

#endif
