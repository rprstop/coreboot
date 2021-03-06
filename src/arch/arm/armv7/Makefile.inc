################################################################################
##
## This file is part of the coreboot project.
##
## Copyright (C) 2013 The ChromiumOS Authors
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; version 2 of the License.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
##
################################################################################

armv7_flags = -march=armv7-a -mthumb -mthumb-interwork \
	-I$(src)/arch/arm/include/armv7/ -D__COREBOOT_ARM_ARCH__=7

################################################################################
## Bootblock
################################################################################
ifeq ($(CONFIG_ARM_BOOTBLOCK_ARMV7),y)

ifneq ($(CONFIG_ARM_BOOTBLOCK_CUSTOM),y)
bootblock-y += bootblock.S
endif
bootblock-$(CONFIG_ARM_BOOTBLOCK_SIMPLE) += bootblock_simple.c
bootblock-$(CONFIG_ARM_BOOTBLOCK_NORMAL) += bootblock_normal.c
bootblock-y += cache.c
bootblock-y += mmu.c

bootblock-c-ccopts += $(armv7_flags)
bootblock-S-ccopts += $(armv7_flags)

endif
################################################################################
## ROM stage
################################################################################
ifeq ($(CONFIG_ARM_ROMSTAGE_ARMV7),y)

romstage-y += cache.c
romstage-y += exception.c
romstage-y += exception_asm.S
romstage-y += mmu.c

romstage-c-ccopts += $(armv7_flags)
romstage-S-ccopts += $(armv7_flags)

endif
################################################################################
## RAM stage
################################################################################
ifeq ($(CONFIG_ARM_RAMSTAGE_ARMV7),y)

ramstage-y += cache.c
ramstage-y += exception.c
ramstage-y += exception_asm.S
ramstage-y += mmu.c

ramstage-c-ccopts += $(armv7_flags)
ramstage-S-ccopts += $(armv7_flags)

endif
