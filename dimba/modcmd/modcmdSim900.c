/**
 *  \file       modcmdSim900.c
 *  \brief      Implementation of module command abstraction.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.05.07  LeFr  v1.0.00  Initial version
 *  2018.05.15  DaBa  v1.0.01  sync
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  LeFr  Leandro Francucci lf@vortexmakes.com
 *  DaBa  Darío Baliña      db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "rkh.h"
#include "rkhfwk_dynevt.h"
#include "modcmd.h"
#include "modmgr.h"
#include "conmgr.h"
#include "sim900parser.h"
#include "signals.h"
#include <string.h>
#include <stdio.h>

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
typedef struct CmdTbl CmdTbl;
struct CmdTbl
{
    ModCmd sync;
    ModCmd initStr;
    ModCmd getPinStatus;
    ModCmd setPin;
    ModCmd getRegStatus;
    ModCmd setAPN;
    ModCmd startGPRS;
    ModCmd requestIP;
    ModCmd getConnStatus;
    ModCmd connect;
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static SSP sim900Parser;
static RKH_SMA_T *sender;

static const CmdTbl cmdTbl =
{
    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT\r\n", 
     &conMgr, 
     RKH_TIME_MS(300), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "ATE1+CREG=1;+CIPSHUT\r\n", 
     &conMgr, 
     RKH_TIME_MS(300), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT+CPIN?\r\n", 
     &conMgr, 
     RKH_TIME_MS(1500), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT+CPIN=%d\r\n", 
     &conMgr, 
     RKH_TIME_MS(300), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT+CREG?\r\n", 
     &conMgr, 
     RKH_TIME_MS(300), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT+CSTT=\"%s\",\"%s\",\"%s\"\r\n", 
     &conMgr, 
     RKH_TIME_MS(300), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT+CIICR\r\n", 
     &conMgr, 
     RKH_TIME_MS(2000), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT+CIFSR\r\n", 
     &conMgr, 
     RKH_TIME_MS(1000), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT+CIPSTATUS\r\n", 
     &conMgr, 
     RKH_TIME_MS(1000), RKH_TIME_MS(100)},

    {RKH_INIT_STATIC_EVT(evCmd), 
     "AT+CIPSTART=\"%s\",\"%s\",\"%s\"\r\n", 
     &conMgr, 
     RKH_TIME_MS(300), RKH_TIME_MS(100)},
};

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
static void
doSearch(unsigned char c)
{
    ssp_doSearch(&sim900Parser, c);
}

static void
postFIFOEvtCmd(ModMgrEvt *pe, const ModCmd *pc)
{
    pe->args.fmt = pc->fmt;
    pe->args.aoDest = pc->aoDest;
    pe->args.waitResponseTime = pc->waitResponseTime;
    pe->args.interCmdTime = pc->interCmdTime;

    RKH_SMA_POST_FIFO(modMgr, RKH_UPCAST(RKH_EVT_T, pe), *pc->aoDest);
}

static void
sendModCmd_noArgs(const ModCmd *p)
{
    ModMgrEvt *evtCmd;

    sender = *p->aoDest;
    evtCmd = RKH_ALLOC_EVT(ModMgrEvt, evCmd, sender);

    strncpy(evtCmd->cmd, p->fmt, MODMGR_MAX_SIZEOF_CMDSTR);

    evtCmd->args.fmt = p->fmt;
    evtCmd->args.aoDest = p->aoDest;
    evtCmd->args.waitResponseTime = p->waitResponseTime;
    evtCmd->args.interCmdTime = p->interCmdTime;

    RKH_SMA_POST_FIFO(modMgr, RKH_UPCAST(RKH_EVT_T, evtCmd), sender);
}

static void
sendModCmd_rui16(const ModCmd *p, rui16_t arg)
{
    ModMgrEvt *evtCmd;

    sender = *p->aoDest;
    evtCmd = RKH_ALLOC_EVT(ModMgrEvt, evCmd, sender);

    snprintf(evtCmd->cmd, MODMGR_MAX_SIZEOF_CMDSTR, p->fmt, arg);

    evtCmd->args.fmt = p->fmt;
    evtCmd->args.aoDest = p->aoDest;
    evtCmd->args.waitResponseTime = p->waitResponseTime;
    evtCmd->args.interCmdTime = p->interCmdTime;

    RKH_SMA_POST_FIFO(modMgr, RKH_UPCAST(RKH_EVT_T, evtCmd), sender);
}

static void
sendModCmd_3StrArgs(const ModCmd *p, char *s1, char *s2, char *s3)
{
    ModMgrEvt *evtCmd;

    evtCmd = RKH_ALLOC_EVT(ModMgrEvt, evCmd, *p->aoDest);
    
    snprintf(evtCmd->cmd, MODMGR_MAX_SIZEOF_CMDSTR, p->fmt, s1, s2, s3);

    postFIFOEvtCmd(evtCmd, p);
}

/* ---------------------------- Global functions --------------------------- */
ModCmdRcvHandler
ModCmd_init(void)
{
  	ssp_init(&sim900Parser, &rootCmdParser);
  	parser_init();
    return &doSearch;
}

void 
ModCmd_sync(void)
{
    sendModCmd_noArgs(&cmdTbl.sync);
}

void 
ModCmd_initStr(void)
{
    sendModCmd_noArgs(&cmdTbl.initStr);
}

void 
ModCmd_getPinStatus(void)
{
    sendModCmd_noArgs(&cmdTbl.getPinStatus);
}

void 
ModCmd_setPin(rui16_t pin)
{
    sendModCmd_rui16(&cmdTbl.setPin, pin);
}

void 
ModCmd_getRegStatus(void)
{
    sendModCmd_noArgs(&cmdTbl.getRegStatus);
}

void 
ModCmd_setupAPN(char *apn, char *usr, char *nm)
{
    sendModCmd_3StrArgs(&cmdTbl.setAPN, apn, usr, nm);
}

void 
ModCmd_startGPRS(void)
{
    sendModCmd_noArgs(&cmdTbl.startGPRS);
}

void 
ModCmd_requestIP(void)
{
    sendModCmd_noArgs(&cmdTbl.requestIP);
}

void 
ModCmd_getConnStatus(void)
{
    sendModCmd_noArgs(&cmdTbl.getConnStatus);
}

void 
ModCmd_connect(char *prot, char *dmn, char *port)
{
    sendModCmd_3StrArgs(&cmdTbl.setAPN, prot, dmn, port);
}


/* ------------------------------ End of file ------------------------------ */
