#ifndef __ezusb_H
#define __ezusb_H
/*
 * Copyright © 2001 Stephen Williams (steve@icarus.com)
 * Copyright © 2002 David Brownell (dbrownell@users.sourceforge.net)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
#if !defined(_MSC_VER)
#include <stdbool.h>
#else
#define __attribute__(x)
#if !defined(bool)
#define bool int
#endif
#if !defined(true)
#define true (1 == 1)
#endif
#if !defined(false)
#define false (!true)
#endif
#if defined(_PREFAST_)
#pragma warning(disable:28193)
#endif
#endif

/*
 * This function loads the firmware from the given file into RAM.
 * The file is assumed to be in Intel HEX format.  If fx2 is set, uses
 * appropriate reset commands.  Stage == 0 means this is a single stage
 * load (or the first of two stages).  Otherwise it's the second of
 * two stages; the caller preloaded the second stage loader.
 *
 * The target processor is reset at the end of this download.
 */
extern int ezusb_load_ram(libusb_device_handle *device,
	const char *path, int fx2, int stage);

/*
 * This function stores the firmware from the given file into EEPROM.
 * The file is assumed to be in Intel HEX format.  This uses the right
 * CPUCS address to terminate the EEPROM load with a reset command,
 * where FX parts behave differently than FX2 ones.  The configuration
 * byte is as provided here (zero for an21xx parts) and the EEPROM
 * type is set so that the microcontroller will boot from it.
 *
 * The caller must have preloaded a second stage loader that knows
 * how to respond to the EEPROM write request.
 */
extern int ezusb_load_eeprom(libusb_device_handle *device,
	const char *path, const char *type, int config);

/* boolean flag, says whether to write extra messages to stderr */
extern int verbose;
#endif
