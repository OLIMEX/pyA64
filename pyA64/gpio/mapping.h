// Copyright (c) 2017 Stefan Mavrodiev
//
// GNU GENERAL PUBLIC LICENSE
//    Version 3, 29 June 2007
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __MAPPING_H
#define __MAPPING_H

#include "libgpio.h"

/**
 * Structure that describe all gpio
 */
typedef struct {
	char name[10];       // The processor pin
	int offset;         // Memory offset for the pin
	int pin_number;     // Number on the connector
}pin_t;

typedef struct {
	char connector_name[10];
	pin_t pins[41];
}gpio_t;


gpio_t gpio[] = {
	{ "GPIO1",
		{
			{ "PE0",	SUNXI_GPE(0),		5	},
			{ "PE1",	SUNXI_GPE(1),		7	},
			{ "PE2",	SUNXI_GPE(2),		9	},
			{ "PE3",	SUNXI_GPE(3),		11	},
			{ "PE4",	SUNXI_GPE(4),		13	},
			{ "PE5",	SUNXI_GPE(5),		15	},
			{ "PE6",	SUNXI_GPE(6),		17	},
			{ "PE7",	SUNXI_GPE(7),		19	},
			{ "PC4",	SUNXI_GPC(4),		20	},
			{ "PE8",	SUNXI_GPE(8),		21	},
			{ "PC7",	SUNXI_GPC(7),		22	},
			{ "PE9",	SUNXI_GPE(9),		23	},
			{ "PE10",	SUNXI_GPE(10),		25	},
			{ "PE11",	SUNXI_GPE(11),		27	},
			{ "PE12",	SUNXI_GPE(12),		29	},
			{ "PE13",	SUNXI_GPE(13),		31	},
			{ "PE14",	SUNXI_GPE(14),		33	},
			{ "PE15",	SUNXI_GPE(15),		35	},
			{ "PE16",	SUNXI_GPE(16),		37	},
			{ "PE17",	SUNXI_GPE(17),		39	},
			{ "",		0,					0	},
		}
	},
};
#endif
