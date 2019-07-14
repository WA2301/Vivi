/*
 * Automatically generated C config: don't edit
 */
#define AUTOCONF_INCLUDED

/*
 * System Type
 */
#undef  CONFIG_ARCH_SA1100
#undef  CONFIG_ARCH_PXA250
#undef  CONFIG_ARCH_S3C2400
#define CONFIG_ARCH_S3C2410 1

/*
 * Implementations
 */
#define CONFIG_S3C2410_SMDK 1
#undef  CONFIG_S3C2410_MPORT3
#undef  CONFIG_S3C2410_MPORT1
#define CONFIG_S3C2410_NAND_BOOT 1
#undef  CONFIG_S3C2410_AMD_BOOT

/*
 * Low Level Hardware Debugging
 */
#undef  CONFIG_BOOTUP_MEMTEST

/*
 * General setup
 */
#undef  CONFIG_VIVI_ADDR
#define CONFIG_VIVI_TEXTADDR 0x0
#undef  CONFIG_RESET_HANDLING

/*
 * CACHE Enable
 */
#undef  CONFIG_CPU_D_CACHE_ON
#undef  CONFIG_CPU_I_CACHE_ON

/*
 * Power Mangement
 */
#define CONFIG_PM 1

/*
 * Others
 */
#undef  CONFIG_MSG_PROGRESS
#undef  CONFIG_MD5

/*
 * Private Data
 */
#define CONFIG_PRIV 1
#define CONFIG_PARSE_PRIV_DATA 1
#define CONFIG_USE_PARAM_BLK 1
#undef  CONFIG_DEBUG_VIVI_PRIV

/*
 * Serial Port
 */
#define CONFIG_SERIAL 1
#define CONFIG_SERIAL_TERM 1
#undef  CONFIG_SERIAL_GETCMD_STD
#define CONFIG_SERIAL_GETCMD_EXT 1
#define CONFIG_SERIAL_TERM_PROMPT "vivi"

/*
 * Ports
 */
#define CONFIG_SERIAL_UART0 1
#undef  CONFIG_SERIAL_UART1
#undef  CONFIG_SERIAL_UART2
#undef  CONFIG_SERIAL_UART3

/*
 * Transfer Protocol
 */
#define CONFIG_SERIAL_XMODEM 1
#undef  CONFIG_SERIAL_YMODEM
#undef  CONFIG_SERIAL_ZMODEM

/*
 * Memory Technology Devices (MTD)
 */
#define CONFIG_MTD 1
#undef  CONFIG_MTD_DEBUG

/*
 * NOR Flash chip drivers
 */
#undef  CONFIG_MTD_NOR
#undef  CONFIG_MTD_CFI
#undef  CONFIG_MTD_GEN_PROBE
#undef  CONFIG_MTD_CFI_INTELEXT
#undef  CONFIG_MTD_OBSOLETE_CHIPS
#undef  CONFIG_MTD_AMDSTD

/*
 * Mapping drivers for chip access
 */
#undef  CONFIG_MTD_SA1100
#undef  CONFIG_MTD_S3C2400
#define CONFIG_MTD_S3C2410 1
#undef  CONFIG_MTD_PXA250

/*
 * NAND Flash Device Drivers
 */
#define CONFIG_MTD_NAND 1
#define CONFIG_MTD_NAND_ECC 1
#undef  CONFIG_MTD_NAND_VERIFY_WRITE
#define CONFIG_MTD_SMC 1
#define CONFIG_MTD_BONFS 1
#define CONFIG_MTD_NANDY 1

/*
 * Add Built-in Commands
 */
#define CONFIG_CMD_MEM 1
#undef  CONFIG_MEMORY_RAM_TEST
#define CONFIG_CMD_PARAM 1
#define CONFIG_CMD_PART 1
#define CONFIG_CMD_BONFS 1
#undef  CONFIG_CMD_SLEEP
#undef  CONFIG_CMD_PROMPT
#undef  CONFIG_TEST
#undef  CONFIG_CMD_AMD_FLASH

/*
 * System hacking
 */
#undef  CONFIG_TEST_MODE
#undef  CONFIG_DEBUG

/*
 * Debugging messages
 */
#undef  CONFIG_DEBUG_LL
#undef  CONFIG_DEBUG_CFI
