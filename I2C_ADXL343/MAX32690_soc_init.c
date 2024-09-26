/**
 * Configuration for MAX32690-TQFN
 *
 * This file was automatically generated using Analog Devices Pinconfig
 * https://github.com/adi-ctx/cfs-cfsutil
 *
 * Generated at: 2024-09-26T22:43:05.053Z
 * Generated with: C:\analog\cfs\1.0.0\Utils\cfsutil\bin\node.exe C:\analog\cfs\1.0.0\Utils\cfsutil\bin\run generate --engine msdk --input c:\workspace\cfs\EWNA_REPO\I2C_ADXL343\max32690-tqfn.cfsconfig --preview --format json
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2024 Analog Devices, Inc.
 */

#include <mxc_device.h>
#include <mxc_sys.h>
#include <icc.h>

/* Prototypes for functions in this file. */
int PinInit(void);
int ClockInit(void);

int PinInit(void) {
  int result;

  /* Initialize all the used GPIO Ports. */
  result = MXC_GPIO_Init(MXC_GPIO_PORT_0 | MXC_GPIO_PORT_1 | MXC_GPIO_PORT_2);
  if (result != E_NO_ERROR) {
    return result;
  }

  MXC_GPIO_SetConfigLock(MXC_GPIO_CONFIG_UNLOCKED);
  /* P2.7 (1): assigned to I2C0_SDA */
  const mxc_gpio_cfg_t cfg_p2_7 = {
    MXC_GPIO2,
    MXC_GPIO_PIN_7,
    MXC_GPIO_FUNC_ALT1,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIOH,
    MXC_GPIO_DRVSTR_0
  };
  result = MXC_GPIO_Config(&cfg_p2_7);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P2.8 (2): assigned to I2C0_SCL */
  const mxc_gpio_cfg_t cfg_p2_8 = {
    MXC_GPIO2,
    MXC_GPIO_PIN_8,
    MXC_GPIO_FUNC_ALT1,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIOH,
    MXC_GPIO_DRVSTR_0
  };
  result = MXC_GPIO_Config(&cfg_p2_8);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P0.14 (14): assigned to GPIO0_P0.14 */
  const mxc_gpio_cfg_t cfg_p0_14 = {
    MXC_GPIO0,
    MXC_GPIO_PIN_14,
    MXC_GPIO_FUNC_OUT,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIO,
    MXC_GPIO_DRVSTR_0
  };
  result = MXC_GPIO_Config(&cfg_p0_14);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P1.9 (15): assigned to UART2_RX */
  const mxc_gpio_cfg_t cfg_p1_9 = {
    MXC_GPIO1,
    MXC_GPIO_PIN_9,
    MXC_GPIO_FUNC_ALT1,
    MXC_GPIO_PAD_WEAK_PULL_UP,
    MXC_GPIO_VSSEL_VDDIO,
    MXC_GPIO_DRVSTR_0
  };
  result = MXC_GPIO_Config(&cfg_p1_9);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P1.10 (16): assigned to UART2_TX */
  const mxc_gpio_cfg_t cfg_p1_10 = {
    MXC_GPIO1,
    MXC_GPIO_PIN_10,
    MXC_GPIO_FUNC_ALT1,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIO,
    MXC_GPIO_DRVSTR_0
  };
  result = MXC_GPIO_Config(&cfg_p1_10);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P2.11 (66): assigned to GPIO2_P2.11 */
  const mxc_gpio_cfg_t cfg_p2_11 = {
    MXC_GPIO2,
    MXC_GPIO_PIN_11,
    MXC_GPIO_FUNC_IN,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIOH,
    MXC_GPIO_DRVSTR_0
  };
  result = MXC_GPIO_Config(&cfg_p2_11);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P2.12 (67): assigned to GPIO2_P2.12 */
  const mxc_gpio_cfg_t cfg_p2_12 = {
    MXC_GPIO2,
    MXC_GPIO_PIN_12,
    MXC_GPIO_FUNC_OUT,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIO,
    MXC_GPIO_DRVSTR_0
  };
  result = MXC_GPIO_Config(&cfg_p2_12);
  if (result != E_NO_ERROR) {
    return result;
  }

  MXC_GPIO_SetConfigLock(MXC_GPIO_CONFIG_LOCKED);

  return E_NO_ERROR;
}

int ClockInit(void) {
  int result;

  /* SYS_OSC Mux: Clock Source is set to IPO (Internal Primary Osc.). */
  result = MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* DMA: Enable the Component Clock. */
  MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_DMA);

  /* I2C0/1/2: Enable the I2C0 Clock. */
  MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_I2C0);

  /* ICC: Enable the Component Clock. */
  MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_SYSCACHE);
  MXC_ICC_Enable(MXC_ICC0);
  MXC_ICC_Enable(MXC_ICC1);

  /* TMR0/1/2/3: Enable the TMR0 Clock. */
  MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_TMR0);

  /* TMR0/1/2/3: Enable the TMR1 Clock. */
  MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_TMR1);

  /* TMR0/1/2/3: Enable the TMR2 Clock. */
  MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_TMR2);

  /* TMR0/1/2/3: Enable the TMR3 Clock. */
  MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_TMR3);

  /* UART0/1/2: Enable the UART2 Clock. */
  MXC_SYS_ClockEnable(MXC_SYS_PERIPH_CLOCK_UART2);

  return E_NO_ERROR;
}
