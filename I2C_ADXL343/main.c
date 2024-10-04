/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. All Rights Reserved.
 * (now owned by Analog Devices, Inc.),
 * Copyright (C) 2023 Analog Devices, Inc. All Rights Reserved. This software
 * is proprietary to Analog Devices, Inc. and its licensors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

/*
  main.c

  MAX32690 EV Kit I2C example for ADXL343.

  This example continuously prints ADXL343 data.

  The ADXL343 INT2 output is connected to P2.11 of the MAX32690.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "mxc.h"
#include "adxl343.h"
#include "board.h"
#include "led.h"

#define MAX32690FTHR
// #define MAX32690EVKIT

// The GPIO pin used for ADXL343 interrupt.
#ifdef MAX32690FTHR
#define ADXL343_IRQ_PORT    MXC_GPIO1
#define ADXL343_IRQ_PIN     MXC_GPIO_PIN_7
#endif

#ifdef MAX32690EVKIT
#define ADXL343_IRQ_PORT    MXC_GPIO2
#define ADXL343_IRQ_PIN     MXC_GPIO_PIN_11
#endif

#undef WAIT_FOR_KEYPRESS

// The I2C peripheral the ADXL343 is connected to and the bus speed.
#define I2C_INST MXC_I2C0
#define I2C_FREQ 100000


void GPIO2_IRQHandler(void)
{
    MXC_GPIO_Handler(2);
}

static mxc_gpio_cfg_t adxl343_irq_cfg = { .port = ADXL343_IRQ_PORT,
                                          .mask = ADXL343_IRQ_PIN,
                                          .pad = MXC_GPIO_PAD_NONE,
                                          .func = MXC_GPIO_FUNC_IN,
                                          .vssel = MXC_GPIO_VSSEL_VDDIOH };

// Flag shared between interrupt handler and differed work service loop
static volatile bool axis_data_ready = false;

/*
  Print message and blink LEDs until reset.
*/
void blink_halt(char *msg)
{
    puts(msg);
    puts("Reset to restart application.");

    for (;;) {
        // Toggle LED every 250ms
        MXC_Delay(MXC_DELAY_MSEC(250));

        /** NOTE: Change this when configuring with the Config Tool! */
        LED_Toggle(LED_RED);        // P0.14 (default)
        // LED_Toggle(LED_GREEN);   // P2.24
        // LED_Toggle(LED_BLUE);    // P2.25
        /*************************************************************/
    }
}

/*
  ADXL343 interrupt handler.

  Set global data ready flag.
*/
void adxl343_handler(void *cbdata)
{
    (void)cbdata;

    axis_data_ready = true;
}

/*
  ADXL343 configuration.

  Configures GPIO pin as external interrupt and ADXL343 for continuous operation.
*/
int adxl343_config(void)
{
    int result;
    int16_t tmp[3];
    int8_t axis_offsets[3] = { -2, -2, 7 }; // Device specific offset calibration values

    result = 0;
    result |= adxl343_set_power_control(ADXL343_PWRCTL_STANDBY);
    result |= adxl343_set_int_enable(0);
    result |= adxl343_get_axis_data(tmp); // Unload any unread data
    result |= adxl343_set_data_rate(ADXL343_DR_25HZ);
    result |= adxl343_set_range(ADXL343_RANGE_2G);
    result |= adxl343_set_power_mode(ADXL343_PWRMOD_NORMAL);
    result |= adxl343_set_offsets(axis_offsets);
    result |= adxl343_set_fifo_mode(ADXL343_FIFO_BYPASS);
    result |= adxl343_set_int_map(ADXL343_INT_DATA_READY);
    result |= adxl343_set_int_enable(ADXL343_INT_DATA_READY);
    result |= adxl343_set_power_control(ADXL343_PWRCTL_MEASURE);

    MXC_GPIO_Config(&adxl343_irq_cfg);
    MXC_GPIO_RegisterCallback(&adxl343_irq_cfg, adxl343_handler, NULL);
    MXC_GPIO_IntConfig(&adxl343_irq_cfg, MXC_GPIO_INT_RISING);
    MXC_GPIO_EnableInt(adxl343_irq_cfg.port, adxl343_irq_cfg.mask);
    NVIC_EnableIRQ(MXC_GPIO_GET_IRQ(MXC_GPIO_GET_IDX(ADXL343_IRQ_PORT)));

    return result;
}

/*
  Print message and wait for keypress
*/
void wait_for_keypress(void)
{
    const char msg[] = "Press Enter or Return to continue ...";

    printf("%s", msg);
    getchar();
    printf("%*s", sizeof(msg) - 1, "");
}

int main(void)
{
    int16_t axis_data[3];

    MXC_ICC_Enable(MXC_ICC0);
    MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO);
    SystemCoreClockUpdate();

    // Disable stdout buffering
    setbuf(stdout, NULL);
    printf("\nMAX32690 I2C ADXL343 demo.\n");

    if (MXC_I2C_Init(I2C_INST, 1, 0) != E_NO_ERROR) {
        blink_halt("Trouble initializing I2C instance.");
    }

    mxc_gpio_cfg_t i2c0_3v3_cfg = { MXC_GPIO2, (MXC_GPIO_PIN_7 | MXC_GPIO_PIN_8), MXC_GPIO_FUNC_ALT1,
                                       MXC_GPIO_PAD_NONE, MXC_GPIO_VSSEL_VDDIOH, MXC_GPIO_DRVSTR_0 };
    MXC_GPIO_Config(&i2c0_3v3_cfg);

    MXC_I2C_SetFrequency(I2C_INST, I2C_FREQ);

    if (adxl343_init(I2C_INST) != E_NO_ERROR) {
        blink_halt("Trouble initializing ADXL343.");
    }

    if (adxl343_config() != E_NO_ERROR) {
        blink_halt("Trouble configuring ADXL343.");
    }


    // Use delay or wait for keypress to allow debugger to attach before entering low power mode
#if !defined(WAIT_FOR_KEYPRESS)
    MXC_Delay(MXC_DELAY_SEC(3));
#else
    wait_for_keypress();
#endif

    for (;;) {

        if (axis_data_ready) {
            axis_data_ready = false;

            if (adxl343_get_axis_data(axis_data) != E_NO_ERROR) {
                blink_halt("Trouble reading ADXL343.");
            }

            printf("\rx:% -2.2f  y:% -2.2f  z:% -2.2f", axis_data[0] * ADXL343_SF_2G,
                   axis_data[1] * ADXL343_SF_2G, axis_data[2] * ADXL343_SF_2G);
            MXC_Delay(200000);
            LED_Toggle(0);
        }

//        MXC_LP_EnterSleepMode();
    }
}
