/*
 * fsm_uart.h
 *
 *  Created on: Nov 7, 2025
 *      Author: lenovo
 */

#ifndef INC_FSM_UART_H_
#define INC_FSM_UART_H_

#include "main.h"

// Khởi tạo UART FSM
void uart_communication_init(void);

// Xử lý logic giao tiếp UART qua FSM
void uart_communication_fsm(UART_HandleTypeDef *huart, uint32_t ADC_value, uint8_t command_flag);


#endif /* INC_FSM_UART_H_ */
