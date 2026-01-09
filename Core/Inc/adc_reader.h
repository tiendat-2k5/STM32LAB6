/*
 * adc_reader.h
 *
 *  Created on: 9 thg 11, 2025
 *      Author: lenovo
 */

#ifndef INC_ADC_READER_H_
#define INC_ADC_READER_H_

#include "main.h"

// Đọc giá trị ADC
uint32_t adc_reader_get_value(ADC_HandleTypeDef *hadc);

#endif /* INC_ADC_READER_H_ */
