# ifndef __KEY_H
# define __KEY_H

# include "sys.h"

# define KEY_UP		PAin(8)
# define KEY_OK		PCin(9)
# define KEY_DOWN	PCin(8)

void KEY_Config(void);
uint8_t KEY_Scan(void);

# endif

