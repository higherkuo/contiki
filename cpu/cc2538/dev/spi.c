
#include "contiki.h"
#include "reg.h"
#include "dev/ioc.h"
#include "dev/sys-ctrl.h"
#include "ssi.h"
#include "gpio.h"

/**
 * The following #defines select which gpio pins to use for the SPI lines.
#define CC2538_SPI_CLK_PORT_NUM  GPIO_C_NUM
#define CC2538_SPI_CLK_PIN_NUM   2
#define CC2538_SPI_MOSI_PORT_NUM GPIO_C_NUM
#define CC2538_SPI_MOSI_PIN_NUM  3
#define CC2538_SPI_MISO_PORT_NUM GPIO_C_NUM
#define CC2538_SPI_MISO_PIN_NUM  4
#define CC2538_SPI_SEL_PORT_NUM  GPIO_C_NUM
#define CC2538_SPI_SEL_PIN_NUM   5
 */

/*
 * Initialize SPI bus.
 */
void
spi_init(void)
{
  /* Enable the SSI peripheral */
  REG(SYS_CTRL_RCGCSSI) |= 1;

  /* Start by disabling the peripheral before configuring it */
  REG(SSI0_BASE + SSI_O_CR1) = 0;

  /* Set the IO clock as the SSI clock */
  REG(SSI0_BASE + SSI_O_CC) = 1;

  /* Set the mux correctly to connect the SSI pins to the correct GPIO pins */
  ioc_set_sel(CC2538_SPI_CLK_PORT_NUM, CC2538_SPI_CLK_PIN_NUM, IOC_PXX_SEL_SSI0_CLKOUT);
  ioc_set_sel(CC2538_SPI_MOSI_PORT_NUM, CC2538_SPI_MOSI_PIN_NUM, IOC_PXX_SEL_SSI0_TXD);
  REG(IOC_SSIRXD_SSI0) = (CC2538_SPI_MISO_PORT_NUM*8) + CC2538_SPI_MISO_PIN_NUM;
  ioc_set_sel(CC2538_SPI_SEL_PORT_NUM, CC2538_SPI_SEL_PIN_NUM, IOC_PXX_SEL_SSI0_FSSOUT);

  /* Put all the SSI gpios into peripheral mode */
  GPIO_PERIPHERAL_CONTROL(GPIO_PORT_TO_BASE(CC2538_SPI_CLK_PORT_NUM), GPIO_PIN_MASK(CC2538_SPI_CLK_PIN_NUM));
  GPIO_PERIPHERAL_CONTROL(GPIO_PORT_TO_BASE(CC2538_SPI_MOSI_PORT_NUM), GPIO_PIN_MASK(CC2538_SPI_MOSI_PIN_NUM));
  GPIO_PERIPHERAL_CONTROL(GPIO_PORT_TO_BASE(CC2538_SPI_MISO_PORT_NUM), GPIO_PIN_MASK(CC2538_SPI_MISO_PIN_NUM));
  GPIO_PERIPHERAL_CONTROL(GPIO_PORT_TO_BASE(CC2538_SPI_SEL_PORT_NUM), GPIO_PIN_MASK(CC2538_SPI_SEL_PIN_NUM));

  /* Disable any pull ups or the like */
  ioc_set_over(CC2538_SPI_CLK_PORT_NUM, CC2538_SPI_CLK_PIN_NUM, IOC_OVERRIDE_DIS);
  ioc_set_over(CC2538_SPI_MOSI_PORT_NUM, CC2538_SPI_MOSI_PIN_NUM, IOC_OVERRIDE_DIS);
  ioc_set_over(CC2538_SPI_MISO_PORT_NUM, CC2538_SPI_MISO_PIN_NUM, IOC_OVERRIDE_DIS);
  ioc_set_over(CC2538_SPI_SEL_PORT_NUM, CC2538_SPI_SEL_PIN_NUM, IOC_OVERRIDE_DIS);

  /* Configure the clock */
  REG(SSI0_BASE + SSI_O_CPSR) = 2;

  /* Put the ssi in motorola SPI mode with 8 bit data */
  REG(SSI0_BASE + SSI_O_CR0) = (1<<7) | (1<<6) | (7);

  /* Enable the SSI */
  REG(SSI0_BASE + SSI_O_CR1) |= SSI_CR1_SSE;

  /* Clear the RX FIFO */
  while (1) {
    if(REG(SSI0_BASE + SSI_O_SR) & SSI_SR_RNE) {
        REG(SSI0_BASE + SSI_O_DR);
    } else {
      break;
    }
  }
}
