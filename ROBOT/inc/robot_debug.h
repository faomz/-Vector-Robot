# ifndef __ROBOT_DEBUG_H
# define __ROBOT_DEBUG_H

# include "sys.h"

# define ROBOT_DEBUG_USART		USART1
# define robot_debug		printf

void robot_DebugConfig(void);
void robot_DebugRanging(void);
void robot_DebugPho(void);
void robot_DebugGray(void);

# endif

