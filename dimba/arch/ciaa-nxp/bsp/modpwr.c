/**
 *  \file       modpwr_sim900.c
 *  \brief      Implementation of modpwr abstraction for SIM900 on CIAA-NXP.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.06.05  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa  Dario Bali�a       db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "sapi.h"

#include "rkh.h"
#include "modpwr.h"

/* ----------------------------- Local macros ------------------------------ */
#define CFG_PWR_KEY_GPIO()  gpioConfig(GPIO0, GPIO_OUTPUT)
#define PWR_KEY(b)          gpioWrite(GPIO0, !b)

/* ------------------------------- Constants ------------------------------- */
#define SIM900_PWR_TIME     RKH_TIME_MS(1000)

/* ---------------------------- Local data types --------------------------- */
typedef enum ModPwrStates
{
    OnOff,
    Toggling
};

/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
static ruint state, counter;

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
modPwr_init(void)
{
    CFG_PWR_KEY_GPIO();
    PWR_KEY(1);
    state = OnOff;
}

void
modPwr_ctrl(void)
{
    switch(state)
    {
        case OnOff:
            PWR_KEY(1);
            break;

        case Toggling:
            PWR_KEY(0);
            if(counter && (--counter == 0))
            {
                state = OnOff;
            }

            break;
    }
}

void
modPwr_toggle(void)
{
    RKH_ENTER_CRITICAL();
    counter = SIM900_PWR_TIME;
    state = Toggling;
    RKH_EXIT_CRITICAL();
}

/* ------------------------------ End of file ------------------------------ */