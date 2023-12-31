// SPDX-License-Identifier: GPL-2.0+
/*
 *
 * Copyright (C) 2004-2007, 2012 Freescale Semiconductor, Inc.
 * TsiChung Liew (Tsi-Chung.Liew@freescale.com)
 */

/* CPU specific interrupt routine */
#include <irq_func.h>
#include <asm/immap.h>
#include <asm/io.h>

int interrupt_init(void)
{
	int0_t *intp = (int0_t *) (CFG_SYS_INTR_BASE);

	/* Make sure all interrupts are disabled */
	setbits_be32(&intp->imrh0, 0xffffffff);
	setbits_be32(&intp->imrl0, 0xffffffff);

	enable_interrupts();
	return 0;
}

#if CONFIG_IS_ENABLED(MCFTMR)
void dtimer_intr_setup(void)
{
	int0_t *intp = (int0_t *) (CFG_SYS_INTR_BASE);

	out_8(&intp->icr0[CFG_SYS_TMRINTR_NO], CFG_SYS_TMRINTR_PRI);
	clrbits_be32(&intp->imrh0, CFG_SYS_TMRINTR_MASK);
}
#endif
