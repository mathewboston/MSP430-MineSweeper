/* from sr.s - routines to access status register */
extern void set_sr(unsigned short val);
extern void and_sr(unsigned short val);
extern void or_sr(unsigned short val);
extern unsigned short get_sr();

