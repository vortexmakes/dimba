/**
 *  \file       bsp.h
 *  \brief      BSP for 80x86 OS win32
 *
 *  \ingroup    bsp
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.05.23  DaBa  v0.0.01  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci  lf@vortexmakes.com
 *  DaBa  Dario Bali�a       dariosb@gmail.com
 */

/* --------------------------------- Module -------------------------------- */
#ifndef __BSP_H__
#define __BSP_H__

/* ----------------------------- Include files ----------------------------- */
/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/*
 * Serial Ports channels identifiers
 */
enum
{
	GSM_PORT, 

  	NUM_CHANNELS
};

/*
 * User trace events id�s
 */
enum
{
    MODCMD_USR_TRACE = RKH_TE_USER,
};

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void bsp_init(int argc, char *argv[]);
void bsp_publishActor(void);

void bsp_keyParser(int c);
void bsp_timeTick(void);

void bsp_serial_open(int ch);
void bsp_serial_close(int ch);
void bsp_serial_puts(int ch, char *p);
void bsp_serial_putnchar(int ch, unsigned char *p, ruint ndata);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ File footer ------------------------------ */
