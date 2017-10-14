# include "robot.h"

void robot_DebugConfig(void)
{
	uart_init(115200);
}

void robot_DebugRanging(void)
{
	robot_debug("\r\n");
	robot_debug("======== Robot Raging Debug Infomation ========\t\r\n");
	robot_debug("==            A:%d      B:%d      C:%d      ==\t\r\n ",ADC1ConvValue[ROBOT_RANG_A] >> 4, ADC1ConvValue[ROBOT_RANG_B] >> 4,ADC1ConvValue[ROBOT_RANG_C] >> 4);
	robot_debug("==                                           ==\r\n");
	robot_debug("==          H:%d                      D:%d     ==\r\n ",ADC1ConvValue[ROBOT_RANG_H] >> 4, ADC1ConvValue[ROBOT_RANG_D] >> 4);
	robot_debug("==                                           ==\r\n");
	robot_debug("==            I:%d      J:%d      K:%d      ==\r\n ",ADC1ConvValue[ROBOT_RANG_I] >> 4, ADC1ConvValue[ROBOT_RANG_J] >> 4,ADC1ConvValue[ROBOT_RANG_K] >> 4);
	robot_debug("\r\n");
	robot_debug("\r\n");
}

void robot_DebugGray(void)
{
	robot_debug("\r\n");
	robot_debug("======== Robot Gray Debug Infomation ========\t\r\n");
//	robot_debug("===    Robot Gray:%d                      ===\r\n",ADC1ConvValue[ROBOT_GRAY]>>4);
	robot_debug("\r\n");
	robot_debug("\r\n");
}

void robot_DebugPho(void)
{
	robot_debug("\r\n");
	robot_debug("======== Robot Pho Debug Infomation ========\t\r\n");
	robot_debug("==       B:%d                  C:%d       ==\r\n", IsPhoDetected(ROBOT_PHO_B),IsPhoDetected(ROBOT_PHO_C));
	robot_debug("==                                        ==\r\n");
	robot_debug("==  A:%d                            D:%d  ==\r\n", IsPhoDetected(ROBOT_PHO_A),IsPhoDetected(ROBOT_PHO_D));
	robot_debug("==                                        ==\r\n");
	robot_debug("==  H:%d                            K:%d  ==\r\n", IsPhoDetected(ROBOT_PHO_H),IsPhoDetected(ROBOT_PHO_K));
	robot_debug("==                                        ==\r\n");
	robot_debug("==       I:%d                  J:%d       ==\r\n", IsPhoDetected(ROBOT_PHO_I),IsPhoDetected(ROBOT_PHO_J));
}
