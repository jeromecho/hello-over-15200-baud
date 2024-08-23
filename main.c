#include <msp430.h> 

int delay(int max) {
    int i;
    for (i=0; i < max; i++) {
        // doing nothing lol
    }
}


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	UCA1CTLW0 |= UCSWRST;
	UCA1CTLW0 |= UCSSEL__SMCLK;
	// Q: Why is there w"0" above, while below, there is
	//    no "0" part?
	UCA1BRW = 8;
	UCA1MCTLW = 0xD600;

	// Port is now communicating over UART!!! instead of
	// being a normal, healthy, functioning port
	P4SEL1 &= ~BIT3;
	P4SEL0 |= BIT3;

	// Q: Why is setting the PM5CTL0 register to low power mode
	// important for UART? Is the answer here that there is
	// something COMMON between UART and how ports fundamentally work?
	PM5CTL0 &= ~LOCKLPM5;

	// Q: From first principles, what would be the difference between
	//    low frequency baud rate generation mode and oversampling mode?
	UCA1CTLW0 &= ~UCSWRST;

	char str[] = "  HELLO OVER 115200 BAUD  ";

	while(1) {
        int j;
        int k;
        for (j=0; j<sizeof(str); j++) {
            UCA1TXBUF = str[j];
            for (k=0; k<10000; k++) {}
        }
        // string delay
        int m;
        for (m=0; m<30000; m++) {
            // do nothing lol
        }
	}

	return 0;
}
