#ifndef __JY61_H
#define __JY61_H

struct STime
{
	unsigned char T[6];
	short dT;
};
struct SAcc
{
	short a[3];
	short T;
};
struct SGyro
{
	short w[3];
	short T;
};
struct SAngle
{
	short Angle[3];
	short T;
};


extern struct SAcc 		stcAcc;
extern struct SGyro 		stcGyro;
extern struct SAngle 	    stcAngle;
extern struct STime         stcTime;
 
extern char YAWCMD[3];
extern char ACCCMD[3] ;
extern char SLEEPCMD[3] ;
extern char UARTMODECMD[3] ;
extern char IICMODECMD[3] ;

extern void JY61_main(void);
    
#endif
