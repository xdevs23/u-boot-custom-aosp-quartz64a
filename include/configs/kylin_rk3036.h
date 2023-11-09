/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2015 Rockchip Electronics Co., Ltd
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>
#include <configs/rk3036_common.h>

#ifndef CONFIG_SPL_BUILD

/* Enable gpt partition table */
#define CONFIG_CMD_GPT
#define CONFIG_RANDOM_UUID
#define CONFIG_EFI_PARTITION
#define PARTS_DEFAULT \
	"uuid_disk=${uuid_gpt_disk};" \
	"name=loader,start=32K,size=4000K,uuid=${uuid_gpt_loader};" \
	"name=reserved,size=64K,uuid=${uuid_gpt_reserved};" \
	"name=misc,size=4M,uuid=${uuid_gpt_misc};" \
	"name=recovery,size=32M,uuid=${uuid_gpt_recovery};" \
	"name=boot_a,size=32M,uuid=${uuid_gpt_boot_a};" \
	"name=boot_b,size=32M,uuid=${uuid_gpt_boot_b};" \
	"name=system_a,size=818M,uuid=${uuid_gpt_system_a};" \
	"name=system_b,size=818M,uuid=${uuid_gpt_system_b};" \
	"name=vendor_a,size=50M,uuid=${uuid_gpt_vendor_a};" \
	"name=vendor_b,size=50M,uuid=${uuid_gpt_vendor_b};" \
	"name=cache,size=100M,uuid=${uuid_gpt_cache};" \
	"name=metadata,size=16M,uuid=${uuid_gpt_metadata};" \
	"name=persist,size=4M,uuid=${uuid_gpt_persist};" \
	"name=userdata,size=-,uuid=${uuid_gpt_userdata};\0" \

#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	"partitions=" PARTS_DEFAULT \
	"mmcdev=0\0" \
	"mmcpart=5\0" \
	"loadaddr=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \

#define CONFIG_ANDROID_BOOT_IMAGE
#define CONFIG_SYS_HUSH_PARSER

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev}; if mmc rescan; then " \
		"part start mmc ${mmcdev} ${mmcpart} boot_start;" \
		"part size mmc ${mmcdev} ${mmcpart} boot_size;" \
		"mmc read ${loadaddr} ${boot_start} ${boot_size};" \
		"bootm start ${loadaddr}; bootm ramdisk;" \
		"bootm prep; bootm go;" \
	"fi;" \

/* Enable atags */
#define CONFIG_SYS_BOOTPARAMS_LEN	(64*1024)
#define CONFIG_INITRD_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_CMDLINE_TAG

#endif

#endif
