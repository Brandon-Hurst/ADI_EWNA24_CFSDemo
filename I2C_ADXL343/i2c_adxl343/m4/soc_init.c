/**
 * Configuration for MAX32690-TQFN.
 *
 * This file was generated using Analog Devices CodeFusion Studio.
 * https://github.com/analogdevicesinc/codefusion-studio
 *
 * Generated at: 2025-05-29T15:35:25.189Z 
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2025 Analog Devices, Inc.
 */

#include <i2c.h>
#include <mxc_device.h>
#include <mxc_sys.h>
#include <stddef.h>
#include <uart.h>

/* Prototypes for functions in this file.
*/
int PinInit(void);
int PeripheralInit(void);

int PinInit(void) {
  int result;

  /* Initialize all the used GPIO Ports.
  */
  result = MXC_GPIO_Init(MXC_GPIO_PORT_0 | MXC_GPIO_PORT_1 | MXC_GPIO_PORT_2);
  if (result != E_NO_ERROR) {
    return result;
  }

  MXC_GPIO_SetConfigLock(MXC_GPIO_CONFIG_UNLOCKED);

  /* P2.7 (1): assigned to I2C0_SDA.
  */
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

  /* P2.8 (2): assigned to I2C0_SCL.
  */
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

  /* P2.25 (6): assigned to GPIO2_P2.25.
  */
  const mxc_gpio_cfg_t cfg_p2_25 = {
    MXC_GPIO2,
    MXC_GPIO_PIN_25,
    MXC_GPIO_FUNC_OUT,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIOH,
    MXC_GPIO_DRVSTR_0 
  };
  result = MXC_GPIO_Config(&cfg_p2_25);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P0.14 (14): assigned to GPIO0_P0.14.
  */
  const mxc_gpio_cfg_t cfg_p0_14 = {
    MXC_GPIO0,
    MXC_GPIO_PIN_14,
    MXC_GPIO_FUNC_OUT,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIOH,
    MXC_GPIO_DRVSTR_0 
  };
  result = MXC_GPIO_Config(&cfg_p0_14);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P1.15 (24): assigned to GPIO1_P1.15.
  */
  const mxc_gpio_cfg_t cfg_p1_15 = {
    MXC_GPIO1,
    MXC_GPIO_PIN_15,
    MXC_GPIO_FUNC_IN,
    MXC_GPIO_PAD_PULL_UP,
    MXC_GPIO_VSSEL_VDDIO,
    MXC_GPIO_DRVSTR_0 
  };
  result = MXC_GPIO_Config(&cfg_p1_15);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P1.14 (32): assigned to GPIO1_P1.14.
  */
  const mxc_gpio_cfg_t cfg_p1_14 = {
    MXC_GPIO1,
    MXC_GPIO_PIN_14,
    MXC_GPIO_FUNC_IN,
    MXC_GPIO_PAD_PULL_UP,
    MXC_GPIO_VSSEL_VDDIO,
    MXC_GPIO_DRVSTR_0 
  };
  result = MXC_GPIO_Config(&cfg_p1_14);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P2.24 (64): assigned to GPIO2_P2.24.
  */
  const mxc_gpio_cfg_t cfg_p2_24 = {
    MXC_GPIO2,
    MXC_GPIO_PIN_24,
    MXC_GPIO_FUNC_OUT,
    MXC_GPIO_PAD_NONE,
    MXC_GPIO_VSSEL_VDDIOH,
    MXC_GPIO_DRVSTR_0 
  };
  result = MXC_GPIO_Config(&cfg_p2_24);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P2.11 (66): assigned to UART0_RX.
  */
  const mxc_gpio_cfg_t cfg_p2_11 = {
    MXC_GPIO2,
    MXC_GPIO_PIN_11,
    MXC_GPIO_FUNC_ALT1,
    MXC_GPIO_PAD_WEAK_PULL_UP,
    MXC_GPIO_VSSEL_VDDIO,
    MXC_GPIO_DRVSTR_0 
  };
  result = MXC_GPIO_Config(&cfg_p2_11);
  if (result != E_NO_ERROR) {
    return result;
  }

  /* P2.12 (67): assigned to UART0_TX.
  */
  const mxc_gpio_cfg_t cfg_p2_12 = {
    MXC_GPIO2,
    MXC_GPIO_PIN_12,
    MXC_GPIO_FUNC_ALT1,
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

int PeripheralInit(void) {
  int result = E_NO_ERROR;

  { /* Configure UART0.
     */

    /* Initialize the peripheral. */
    result = MXC_UART_Init(MXC_UART0,
                           115200U,
                           MXC_UART_IBRO_CLK);
    if (result != E_NO_ERROR) {
      return result;
    }

    /* Set Data Size. */
    result = MXC_UART_SetDataSize(MXC_UART0, 8);
    if (result != E_NO_ERROR) {
      return result;
    }

    /* Set Stop Bits. */
    result = MXC_UART_SetStopBits(MXC_UART0, MXC_UART_STOP_1);
    if (result != E_NO_ERROR) {
      return result;
    }

    /* Set Flow Control. */
    result = MXC_UART_SetFlowCtrl(MXC_UART0, MXC_UART_FLOW_DIS, 1);
    if (result != E_NO_ERROR) {
      return result;
    }

    /* Set Parity. */
    result = MXC_UART_SetParity(MXC_UART0, MXC_UART_PARITY_DISABLE);
    if (result != E_NO_ERROR) {
      return result;
    }

  }

  { /* Configure I2C0.
     */

    /* Initialize the peripheral. */
    result = MXC_I2C_Init(MXC_I2C0,
                          0,
                          0U);
    if (result != E_NO_ERROR) {
      return result;
    }

    /* Set the frequency. */
    result = MXC_I2C_SetFrequency(MXC_I2C0, 100000U);
    if (result < 0) {
      return result;
    }

    /* Enable or disable clock stretching. */
    result = MXC_I2C_SetClockStretching(MXC_I2C0, 1);
    if (result != E_NO_ERROR) {
      return result;
    }

    /* Set the timeout. */
    MXC_I2C_SetTimeout(MXC_I2C0, 0U);

    /* Disable preload mode. */
    MXC_I2C_DisablePreload(MXC_I2C0);

    /* Disable general call acknowledgement. */
    MXC_I2C_DisableGeneralCall(MXC_I2C0);

  }


  return result;
}
