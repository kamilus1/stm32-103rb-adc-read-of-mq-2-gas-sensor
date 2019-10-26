#include "adcmq2.h"
ADC_HandleTypeDef adc; //configuring adc
void MQ2_Init(){

	__HAL_RCC_ADC1_CLK_ENABLE();//enable adc
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_InitTypeDef gpio;
		gpio.Mode = GPIO_MODE_ANALOG;
		gpio.Pin = GPIO_PIN_0;
		HAL_GPIO_Init(GPIOA, &gpio);
		RCC_PeriphCLKInitTypeDef adc_clk;//setting adc clock for 4 mhz, cause smallest divider is 2
		adc_clk.PeriphClockSelection = RCC_PERIPHCLK_ADC;
		adc_clk.AdcClockSelection = RCC_ADCPCLK2_DIV2;
		HAL_RCCEx_PeriphCLKConfig(&adc_clk);

		 adc.Instance = ADC1;
		 adc.Init.ContinuousConvMode = ENABLE;
		 adc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		 adc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		 adc.Init.ScanConvMode = ADC_SCAN_DISABLE;
		 adc.Init.NbrOfConversion = 1;
		 adc.Init.DiscontinuousConvMode = DISABLE;
		 adc.Init.NbrOfDiscConversion = 1;
		 HAL_ADC_Init(&adc);
		 HAL_ADCEx_Calibration_Start(&adc);

		ADC_ChannelConfTypeDef adc_ch; //setting channel to read from
		adc_ch.Channel = ADC_CHANNEL_0;
		adc_ch.Rank = ADC_REGULAR_RANK_1;
		adc_ch.SamplingTime = ADC_SAMPLETIME_13CYCLES_5;
		HAL_ADC_ConfigChannel(&adc, &adc_ch);
		HAL_ADC_Start(&adc);
}
uint32_t MQ2_Read(){
	uint32_t vadc;
	vadc = HAL_ADC_GetValue(&adc);
			vadc *= (100.0f/4096.0f);
	return vadc;
}
