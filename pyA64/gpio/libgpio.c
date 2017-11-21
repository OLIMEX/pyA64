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



#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "libgpio.h"

static void *sunxi_pio_addr = NULL;

int sunxi_gpio_init(void)
{
	int fd;

	if ((fd = open("/dev/mem", O_RDWR)) < 0) {
		printf("Failed to open memory: %s", strerror(errno));
		return fd;
	}

	/* Map 1k */
	sunxi_pio_addr = mmap(0, 0xC00, PROT_READ | PROT_WRITE, MAP_SHARED, fd, SUNXI_PIO_BASE & 0xFFFFF000);
	if (sunxi_pio_addr == MAP_FAILED) {
		printf("Failed to mmap memory: %s", strerror(errno));
		return 1;
	}

	sunxi_pio_addr += 0x0800;

	close(fd);
	return 0;
}

int sunxi_gpio_set_cfgpin(uint32_t pin, uint8_t val)
{
	uint8_t offset = GPIO_CFG_OFFSET(pin);
	uint8_t index = GPIO_CFG_INDEX(pin);
	uint8_t bank = GPIO_BANK(pin);
	uint64_t *addr;
	uint64_t reg;

	if (sunxi_pio_addr == NULL)
		return 1;

	addr = sunxi_pio_addr + bank * 0x24 + index * 0x04;
	offset += ((uint64_t)addr % 0x08) * 8;
	if ((uint64_t)addr % 0x08)
		addr = (uint64_t *)((uint8_t *)addr - 4);

	reg = *addr;
	reg &= ~(0x0FUL << offset);
	reg |= val << offset;
	*addr = reg;

	return 0;
}

int sunxi_gpio_get_cfgpin(uint32_t pin, uint8_t *cfg)
{
	uint8_t offset = GPIO_CFG_OFFSET(pin);
	uint8_t index = GPIO_CFG_INDEX(pin);
	uint8_t bank = GPIO_BANK(pin);
	uint64_t *addr;
	uint64_t reg;

	if (sunxi_pio_addr == NULL)
		return 1;

	addr = sunxi_pio_addr + bank * 0x24 + index * 0x04;
	offset += ((uint64_t)addr % 0x08) * 8;
	if ((uint64_t)addr % 0x08)
		addr = (uint64_t *)((uint8_t *)addr - 4);

	reg = *addr;
	*cfg = (uint8_t)((reg >> offset) & 0x0F);
	return 0;
}

int sunxi_gpio_output(uint32_t pin, uint8_t val)
{
	uint8_t offset = GPIO_NUM(pin);
	uint8_t bank = GPIO_BANK(pin);
	uint64_t *addr;
	uint64_t reg;

	if (sunxi_pio_addr == NULL)
		return 1;

	addr = sunxi_pio_addr + bank * 0x24 + 0x10;
	offset += ((uint64_t)addr % 8) * 8;
	if ((uint64_t)addr % 0x08)
		addr = (uint64_t *)((uint8_t *)addr - 4);

	reg = *addr;
	reg &= ~(0x01UL << offset);
	reg |= val << offset;
	*addr = reg;

	return 0;
}


int sunxi_gpio_pullup(uint32_t pin, uint8_t pull)
{
	uint8_t offset = GPIO_PUL_OFFSET(pin);
	uint8_t index = GPIO_PUL_INDEX(pin);
	uint8_t bank = GPIO_BANK(pin);
	uint64_t *addr;
	uint64_t reg;

	if (sunxi_pio_addr == NULL)
		return 1;

	addr = sunxi_pio_addr + bank * 0x24 + index * 0x04 + 0x1C ;
	offset += ((uint64_t)addr % 8) * 8;
	if ((uint64_t)addr % 0x08)
		addr = (uint64_t *)((uint8_t *)addr - 4);

	reg = *addr;
	reg &= ~(0x03 << offset);
	reg |= pull << offset;
	*addr = reg;

	return 0;
}

int sunxi_gpio_input(uint32_t pin, uint8_t *val)
{
	uint8_t offset = GPIO_NUM(pin);
	uint8_t bank = GPIO_BANK(pin);
	uint64_t *addr;
	uint64_t reg;

	if (sunxi_pio_addr == NULL)
		return 1;

	addr = sunxi_pio_addr + bank * 0x24 + 0x10;
	offset += ((uint64_t)addr % 8) * 8;
	if ((uint64_t)addr % 0x08)
		addr = (uint64_t *)((uint8_t *)addr - 4);

	reg = *addr;
	*val = (uint8_t)((reg >> offset) & 0x01);

	return 0;
}
