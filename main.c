/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
* Hardware interrupt demo with Button 1 - 3 to control LED 1 - 3 
* with different Sense to toggle the LED 
* LED 4 will blink once every 500ms
* written by: Mohannad Rawashdeh
* rawashdeh.mohannad@gmail.com
* https://mb-raw.blogspot.com/
 *
 */

#include <stdbool.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "boards.h"
/*based on your file config*/
//#include "nrf_delay.h"
#include <delay/nrf_delay.h>

#define LED1_pin    17
#define LED2_pin    18
#define LED3_pin    19
#define LED4_pin    20
#define Button1_pin 13
#define Button2_pin 14
#define Button3_pin 15


void button1_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    nrf_drv_gpiote_out_toggle(LED1_pin);
}
void button2_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    nrf_drv_gpiote_out_toggle(LED2_pin);
}
void button3_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
    nrf_drv_gpiote_out_toggle(LED3_pin);
}
/**
 * 
 */
 static void irq_gpio_init(void)
 {
  /*set the led pins as an output using GPIOTE API*/
  nrf_drv_gpiote_init();

  nrf_drv_gpiote_out_config_t led1_config;
  led1_config.action = NRF_GPIOTE_POLARITY_LOTOHI;
  led1_config.task_pin=false;
  led1_config.init_state=false;
  nrf_drv_gpiote_out_init(LED1_pin,&led1_config);

  nrf_drv_gpiote_out_config_t led2_config;
  led2_config.action = NRF_GPIOTE_POLARITY_LOTOHI;
  led2_config.task_pin=false;
  led1_config.init_state=false;
  nrf_drv_gpiote_out_init(LED2_pin,&led2_config);

  nrf_drv_gpiote_out_config_t led3_config;
  led3_config.action = NRF_GPIOTE_POLARITY_LOTOHI;
  led3_config.task_pin=false;
  led3_config.init_state=false;
  nrf_drv_gpiote_out_init(LED3_pin,&led3_config);

  nrf_drv_gpiote_in_config_t button1_config;
  button1_config.pull = NRF_GPIO_PIN_PULLUP;
  button1_config.sense=NRF_GPIOTE_POLARITY_HITOLO;
  button1_config.is_watcher = false;
  button1_config.skip_gpio_setup = false;
  button1_config.hi_accuracy = true;
  nrf_drv_gpiote_in_init(Button1_pin, &button1_config, button1_pin_handler);

  nrf_drv_gpiote_in_config_t button2_config;
  button2_config.pull = NRF_GPIO_PIN_PULLUP;
  button2_config.sense=NRF_GPIOTE_POLARITY_LOTOHI;
  button2_config.is_watcher = false;
  button2_config.skip_gpio_setup = false;
  button2_config.hi_accuracy = true;
  nrf_drv_gpiote_in_init(Button2_pin, &button2_config, button2_pin_handler);

  nrf_drv_gpiote_in_config_t button3_config;
  button3_config.pull = NRF_GPIO_PIN_PULLUP;
  button3_config.sense=NRF_GPIOTE_POLARITY_TOGGLE;
  button3_config.is_watcher = false;
  button3_config.skip_gpio_setup = false;
  button3_config.hi_accuracy = true;
  nrf_drv_gpiote_in_init(Button3_pin, &button3_config, button3_pin_handler);


  nrf_drv_gpiote_in_event_enable(Button1_pin, true);
  nrf_drv_gpiote_in_event_enable(Button2_pin, true);
  nrf_drv_gpiote_in_event_enable(Button3_pin, true);
 }
/**
 * @brief Function for application main entry.
 */
int main(void)
{
    nrf_gpio_cfg_output(LED4_pin);
    irq_gpio_init();
    while (true)
    {
      nrf_delay_ms(500);
      nrf_gpio_pin_toggle(LED4_pin);
    }
}


/** @} */
