/*
 * fsm_uart.c
 *
 *  Created on: Nov 7, 2025
 *      Author: lenovo
 */

/*
 * fsm_uart.c
 */

#include "uart_comm.h"
#include <stdio.h>
#include <string.h>

static uint32_t timeout_counter = 0;
static uint8_t resend_flag = 0;      // Cờ gửi lại gói tin
static uint32_t saved_ADC_value = 0;

void uart_communication_init(void) {
    timeout_counter = 0;
    resend_flag = 0;
    saved_ADC_value = 0;
}

void uart_communication_fsm(UART_HandleTypeDef *huart, uint32_t ADC_value, uint8_t command_flag) {
	static uint8_t resend_flag = 0;
	static uint32_t timeout_counter = 0;
    if (command_flag == 1 && !resend_flag) { // Nhận lệnh !RST# lần đầu tiên
        //saved_ADC_value = ADC_value; // Lưu giá trị hiện tại của ADC
        resend_flag = 1;             // Bật cờ gửi lại
        timeout_counter = HAL_GetTick(); // Bắt đầu đếm thời gian timeout

        // Gửi giá trị ADC đã lưu về UART
        char response[30];
        sprintf(response, "\r!ADC=%lu#", ADC_value);
        HAL_UART_Transmit(huart, (uint8_t*)response, strlen(response), 1000);
    }

    // Gửi lại giá trị ADC mỗi 3 giây nếu chưa nhận được !OK#
    if (resend_flag && HAL_GetTick() - timeout_counter >= 2000) {
        timeout_counter = HAL_GetTick(); // Cập nhật lại bộ đếm thời gian timeout

        // Gửi lại giá trị ADC đã lưu
        char response[30];
        sprintf(response, "\r!ADC=%lu#", ADC_value);
        HAL_UART_Transmit(huart, (uint8_t*)response, strlen(response), 1000);
    }

    // Khi nhận được lệnh !OK#, dừng gửi lại giá trị ADC
    if (command_flag == 0) {
        resend_flag = 0; // Tắt cờ resend
    }
}
