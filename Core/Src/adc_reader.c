#include "adc_reader.h"

uint32_t adc_reader_get_value(ADC_HandleTypeDef *hadc) {
    // Đọc giá trị ADC
    return HAL_ADC_GetValue(hadc);
}
