char* serialTransmitData = 0;
uint8_t serialTransmitCompleted = 0;
char serialReceivedCharacter = 0;

void Serial_Init() {
  //Change the function of TX and RX pins for UART
  Serial_UART_TX_PIN |= 1;
  Serial_UART_RX_PIN |= 1;

  //Turn on UART0
  PCONP |= 1 << 3;

  //Enable FIFO for UART0
  Serial_UART->FCR |= (1 << 0);

  //In order to change the DLM, DLL and FDR values, write correct code for enabling the access to divisor latches
  Serial_UART->LCR |= (1 << 7);

  //Write correct DLM, DLL and FDR values for 9600 baudrate
  Serial_UART->DLM |= 0x01;
  Serial_UART->DLL |= 0x25;
  Serial_UART->FDR |= 0x01 << 0 | 0x03 << 4;

  //Write correct code for disabling access to divisor latches
  Serial_UART->LCR &= ~(1 << 7);

  //Change LCR register value for 8-bit character transfer, 1 stop bits and even parity
  Serial_UART->LCR |= (3 << 0) | (0 << 2) | (1 << 3) | (1 << 4);
}

void Serial_Write(char* data) {
	while(*data > 0) {
		Serial_WriteData(*data++);
	}
}

void Serial_WriteData(char data) {
  //Wait unil Transmit Holding Register become empty
  while (!(Serial_UART->LSR & (1 << 5)));

  //Write data to Transmit Holding Register
  Serial_UART->THR = data;
}

char Serial_ReadData() {
  char data;
  //Wait until Receiver Data ready
  while (!(Serial_UART->LSR & (1 << 0)));

  //Read data from Receiver Buffer register
  data = Serial_UART->RBR & 0xFF;

  return data;
}
