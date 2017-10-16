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

# if ROBOT_DEBUG > 0u
	# if DEBUG_SENSOR_REPORT > 0u
		# include "ano.h"
	# endif
# endif


# define ROBOT_MODE		

extern Robot_Dev Robot;	

void robot_Config(void);

# endif


