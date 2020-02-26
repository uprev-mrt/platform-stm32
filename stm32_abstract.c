/**
  *@file stm32_hal_abstract.c
  *@brief Abstraction header for STM32 MCUs using the HAL framework
  *@author Jason Berger
  *@date 4/6/2018
  */

 #include "stm32_hal_abstract.h"


/**
 * @brief Non-blocking uart receive function for stm32
 * @param handle handle to uart periph 
 * @param data ptr to store received bytes
 * @param len number of bytes ro receive
 * @param timeout timeout in ms to wait for data
 * @return number of bytes read. 
 */
int mrt_stm32_uart_read(UART_HandleTypeDef* handle, uint8_t* data, int len, int timeout)
{
  HAL_StatusTypeDef status;
  /* attempt a uart read, if read times out, check how many bytes were received */
  status = HAL_UART_Receive(handle, data, len, timeout);

  if(HAL_UART_Receive(handle, data, len, timeout) == HAL_TIMEOUT  )
  {
      len -= handle->RxXferCount; /* when the read is started, RxXferCount gets set to len, and decrements for each byte received*/
  }
  else if(status != HAL_OK) /* If response is not TIMEOUT or OK, something went wrong */
  {
    len = 0;
  }

  return len; /* return number of bytes read */
}
