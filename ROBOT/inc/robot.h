# ifndef __ROBOT_H
# define __ROBOT_H

# include "robot_motor.h"
# include "robot_detect.h"
# include "robot_action.h"
# include "robot_servo.h"
# include "robot_debug.h"

# include "delay.h"
# include "led.h"
# include "usart.h"

# define ROBOT_DEBUG 1u

# define ROBOT_MODE		

extern Robot_Dev Robot;	

void robot_Config(void);

# endif


