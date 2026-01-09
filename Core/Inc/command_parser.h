/*
 * fsm_command.h
 *
 *  Created on: Nov 7, 2025
 *      Author: lenovo
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_


#include "main.h"

extern uint8_t command_flag; // Biến trạng thái của FSM

// Khởi tạo parser
void command_parser_init(void);

// Xử lý lệnh nhận được trong buffer
void command_parser_fsm(uint8_t* buffer);


#endif /* INC_COMMAND_PARSER_H_ */
