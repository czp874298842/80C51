/*****************************************************************************
* Product: BSP for Blinky example, POSIX with cooperative QV kernel
* Last updated for version 5.4.0
* Last updated on  2015-05-24
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* Web:   www.state-machine.com
* Email: info@state-machine.com
*****************************************************************************/
#include "qpn.h"
#include "bsp.h"
#include "blinky.h"
#include "Timer.h"
#include "usart.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h> /* for memcpy() and memset() */

Q_DEFINE_THIS_FILE


/* Local-scope objects -----------------------------------------------------*/
//static struct termios l_tsav; [> structure with saved terminal attributes <]

/*..........................................................................*/
void BSP_init() {
    /*printf("Simple Blinky example\nQP-nano version: %s\n"*/
           /*"Press ESC to quit...\n",*/
           /*QP_VERSION_STR);*/
}
/*..........................................................................*/
void BSP_ledOff() {
    /*printf("OFF\n");*/
	//P1 = 0xff;
	SETB(P1, 7);
}
/*..........................................................................*/
void BSP_ledOn() {
    /*printf("ON\n");*/
	CLRB(P1, 7);
}
/*..........................................................................*/
void Q_onAssert(char_t const Q_ROM * const file, int_t line){
		(void *)file;
		(void *)line;
//    fprintf(stderr, "\nAssertion failed in %s, line %d\n", file, line);
//    exit(-1);
	P10 = 0;
	CLRB(P1, 7);
	SendString("Q_onAssert.\r\n");
	while(1);
}

/*--------------------------------------------------------------------------*/
void QF_onStartup(void) {
    //QF_setTickRate(BSP_TICKS_PER_SEC); 
	
//	CLRB(P1, 1);
//	SETB(P1, 1);
//	CLRB(P1, 0);
	//while(1);
}
/*..........................................................................*/
void QF_onCleanup(void) {
    /* restore the saved terminal attributes */
    //tcsetattr(0, TCSANOW, &l_tsav);
    /*printf("\nBye! Bye!\n");*/
}
/*..........................................................................*/
//void QF_onClockTickISR(void) {
    //struct timeval timeout = { 0U, 0U }; [> timeout for select() <]
    //fd_set con; [> FD set representing the console <]

    //QF_tickXISR(0U); [> perform the QF-nano clock tick processing <]

    //FD_ZERO(&con);
    //FD_SET(0, &con);
    //[> check if a console input is available, returns immediately <]
    //if (0 != select(1, &con, 0, 0, &timeout)) { [> any descriptor set? <]
        //char ch;
        //read(0, &ch, 1);
        //if (ch == '\33') { [> ESC pressed? <]
            //QF_stop();
        //}
    //}
//}

void QF_stop(void) 
{
//	P16 = 0;
    //l_isRunning = false;    [> cause exit from the event loop <]
}

void QV_onIdle(void)   /* CATION: called with interrupts DISABLED, NOTE01 */
{
#ifdef NDEBUG
    /* Put the CPU and peripherals to the low-power mode.
    * you might need to customize the clock management for your application,
    * see the datasheet for your particular Cortex-M MCU.
    */
    QV_CPU_SLEEP();  /* atomically go to sleep and enable interrupts */
#else
    QF_INT_ENABLE(); /* just enable interrupts */
#endif
}


