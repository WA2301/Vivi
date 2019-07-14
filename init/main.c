/*
 * vivi/main.c: main routine
 *
 * Copyright (C) 2001,2002 MIZI Research, Inc.
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *
 * Author: Janghoon Lyu <nandy@mizi.com>
 * Date  : $Date: 2002/08/28 06:00:11 $
 *
 * $Revision: 1.7 $
 * $Id: main.c,v 1.7 2002/08/28 06:00:11 nandy Exp $
 *
 *
 * History
 *
 * 2001-10-xx: Janghoon Lyu <nandy@mizi.com>
 *    - Initial code
 *
 * 2001-01-26: Janghoon Lyu <nandy@mizi.com>
 *    - Release VIVI Bootloader
 *
 * 2002-07-02: Janghoon Lyu <nandy@mizi.com>
 *    - bootldr�� ���縦 û���ϸ鼭 ���Ӱ� �ۼ�
 */

#include "config.h"
#include "machine.h"
#include "mmu.h"
#include "heap.h"
#include "serial.h"
#include "printk.h"
#include "command.h"
#include "priv_data.h"
#include "getcmd.h"
#include "vivi_string.h"
#include "mtd/mtd.h"
#include "processor.h"
#include <reset_handle.h>
#include <types.h>
	
extern char *vivi_banner;

void 
vivi_shell(void)
{
#ifdef CONFIG_SERIAL_TERM
	serial_term();
#else
#error there is no terminal.
#endif
}

void run_autoboot(void)
{
	while (1) {
		exec_string("boot");
		printk("Failed 'boot' command. reentering vivi shell\n");
		/* if default boot fails, drop into the shell */
		vivi_shell();
	}
}

static void 
error(void)
{
	putstr("Sorry. We can not run vivi\n");
	for (;;) /* nothing */;		/* infinite loop */
}

#define DEFAULT_BOOT_DELAY	0x30000000
void boot_or_vivi(void)
{
	char c;
	int ret;
	ulong boot_delay;

	boot_delay = get_param_value("boot_delay", &ret);
	if (ret) boot_delay = DEFAULT_BOOT_DELAY;			//获取默认启动延时
	/* If a value of boot_delay is zero, 
	 * unconditionally call vivi shell */
	if (boot_delay == 0) vivi_shell();//如果延时为0则放弃自起


	/*
	 * wait for a keystroke (or a button press if you want.)
	 */
	printk("Press Return to start the LINUX now, any other key for vivi\n");
	c = awaitkey(boot_delay, NULL);
	if (((c != '\r') && (c != '\n') && (c != '\0'))) {//任意有效按键
		printk("type \"help\" for help.\n");
		vivi_shell();
	}
	run_autoboot();//猜测：如果不按键则c=0,即会自动启动

	return;
}

int main(int argc, char *argv[])
{
	int ret;

	/* NB: ���������� MMU�� ���� ����. */
	/*
	 * Step 1:
	 *  �ϴ� ������ ����ϳ� �Ѹ���..
	 */
	putstr("\r\n");
	putstr(vivi_banner);

	reset_handler();

	/*
	 * Step 2:
	 *   Board�� �ʱ�ȭ �մϴ�.
	 */
	ret = board_init();
	if (ret) {
		putstr("Failed a board_init() procedure\r\n");
		error();
	}

	/*
	 * Step 3:
	 *   4G�� ���Ͼ�(linear)�ϰ� �����ϰ�, �÷��� �޸𸮸�
	 *   ���ϴ� ��� �����ϰ�,
	 *   MMU�� �Ѽ���.
	 */
	mem_map_init();
	mmu_init();
	putstr("Succeed memory mapping.\r\n");

	/* NB: ���ݺ��ʹ� MMU�� ������ ���� ���� */
	/*
	 * Now, vivi is running on the ram. MMU is enabled.
	 */

	/* 
	 * Step 4:
	 *   ��Ʈ�δ����� ���� �޸� �Ҵ��� ����� �� �ֵ���
	 */
	/* initialize the heap area*/
	ret = heap_init();
	if (ret) {
		putstr("Failed initailizing heap region\r\n");
		error();
	}

	/* Step 5:
	 *    ��, ������ �޸� ������ ����� �ƴٸ�,
	 *    MTD���� ��� ���ô�.
	 *    ���ÿ�, MTD�� ��Ƽ��partition ������ �ִٸ�
	 *    ��Ƴ�����.
	 */
	ret = mtd_dev_init();

	/* Step 6:
	 *   ��Ʈ�δ��� ���� �Ķ���� ������ ��Ƴ��߰���.
	 */
	init_priv_data();

	/* Step 7:
	 *   ���� ����(����ϰ� �̻���)�� ������� ���ؼ�
	 */
	misc();

	init_builtin_cmds();

	/* Step 8:
	 *   ���� ���?
	 */
	boot_or_vivi();

	/* ������� ���� �̻�������. �׷��� �ʳ���? */
	return 0;
}
