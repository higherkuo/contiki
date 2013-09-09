#include "contiki.h"
#include "adc.h"

/**
 * \brief Setup a single ADC reading.
 * \param resolution Number of bits to sample with. Use ADC_X_BIT.
 * \param reference_voltage Voltage to compare against. Use ADC_REF_X.
 * \return 0 on success
 *
 * Setup a single channel ADC reading.
 */
int
adc_configure_single(uint32_t resolution, uint32_t reference_voltage)
{
  uint32_t adc3reg;

  /* Stop the random generator
   * I have no idea why this is in an ADC register */
  REG(ADC_ADCCON1) = 0x3c;

  adc3reg = REG(ADC_ADCCON3) & ~(ADC_ADCCON3_EREF_M |
                                 ADC_ADCCON3_EDIV_M);
  REG(ADC_ADCCON3) = adc3reg | resolution | reference_voltage;

  return 0;
}

/**
 * \brief Get a single ADC sample.
 * \param channel The ADC channel to sample. Use ADC_CHANNEL_*.
 * \return The sample result.
 *
 * Sample a single channel of the ADC. Should call adc_configure_single once
 * before this function.
 */
uint16_t
adc_sample_single(uint32_t channel)
{
  uint32_t adc3reg;
  uint32_t val;
  uint32_t bits;

  /* Set the channel to start the conversion */
  adc3reg = REG(ADC_ADCCON3) & ~(ADC_ADCCON3_ECH_M);
  REG(ADC_ADCCON3) = adc3reg | channel;

  /* Determine the number of bits of the conversion */
  bits = REG(ADC_ADCCON3) & ADC_ADCCON3_EDIV_M;

  /* Wait until the reading has finished */
  while (!(REG(ADC_ADCCON1) & ADC_ADCCON1_EOC));

  /* Read the result by concatenating two registers */
  val =  (REG(ADC_ADCL) & ADC_ADCL_ADC_M) |
        ((REG(ADC_ADCH) & ADC_ADCH_ADC_M) << 8);

  /* Shift the result to align it to the LSB */
  switch (bits) {
    case ADC_7_BIT:  val = (val >> ADC_7_BIT_RSHIFT);  break;
    case ADC_9_BIT:  val = (val >> ADC_9_BIT_RSHIFT);  break;
    case ADC_10_BIT: val = (val >> ADC_10_BIT_RSHIFT); break;
    case ADC_12_BIT: val = (val >> ADC_12_BIT_RSHIFT); break;
    default: val = 0; break;
  }

  return val;
}
