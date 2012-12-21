/*
 * bootheader.h
 *
 * Copyright 2012 Emilio López <turl@tuxfamily.org>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

#include <stdint.h>

#ifndef __BOOTHEADER__
#define __BOOTHEADER__

#define CMDLINE_SIZE   						(0x400)
#define PADDING1_SIZE						(0x1200-0x610)
#define BOOTSTUBSTACK_SIZE					(0x1000)

typedef struct __attribute__ ((packed)) {
	uint8_t something1[0x30]; /* FIXME figure out what it is */
	uint32_t sectors;         /* number of sectors after the boot sector, 1 sector = 512 bytes */
	uint8_t something2[0x4];  /* FIXME figure out what it is */
	uint8_t oxff[0x180];      /* lots of 0xFF */
	uint8_t zeros[0x46];      /* lots of zeros */
	uint16_t bootSignature;
} bootSector_t;

struct bootheader {
	bootSector_t bootSector;
	uint8_t cmdline[CMDLINE_SIZE];
	uint32_t bzImageSize;
	uint32_t initrdSize;
	uint32_t SPIUARTSuppression;
	uint32_t SPIType;
	uint8_t padding1[PADDING1_SIZE];
	uint8_t bootstubStack[BOOTSTUBSTACK_SIZE];
} __attribute__((packed));

/* Sanity check for struct size */
typedef char z[(sizeof(struct bootheader) == 0x2200) ? 1 : -1];

#endif
