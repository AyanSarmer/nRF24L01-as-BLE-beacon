#include "nRF24.h"

unsigned char packet[PACKET_SIZE];

void transceiverCommand(unsigned char command)
{
  nRF_CSN_LOW;
  spiByte(command);
  nRF_CSN_HIGH;
}

void transceiverWriteRegister(unsigned char reg, unsigned char* buf, unsigned char length)
{
  reg |= W_REGISTER;
  nRF_CSN_LOW;
  spiByte(reg);
  while (length--)
  {
    spiByte(*buf++);
  }
  nRF_CSN_HIGH;
}

void transceiverInit()
{
  unsigned char mask;
  unsigned char address[5] = {0x71, 0x91, 0x7D, 0x6B, 0};
  
  spiInit();
  nRF_CSN_DDR |= (1 << nRF_CSN);
  nRF_CE_DDR |= (1 << nRF_CE);
  nRF_CSN_HIGH;
  nRF_CE_LOW;
  _delay_ms(100);

  mask = EN_RXADDR_MASK;
  transceiverWriteRegister(EN_RXADDR, &mask, sizeof(mask));  
  mask = EN_AA_MASK;
  transceiverWriteRegister(EN_AA, &mask, sizeof(mask));
  mask = RF_SETUP_MASK;
  transceiverWriteRegister(RF_SETUP, &mask, sizeof(mask));
  mask = CONFIG_MASK;
  transceiverWriteRegister(CONFIG, &mask, sizeof(mask));
  mask = SETUP_RETR_MASK;
  transceiverWriteRegister(SETUP_RETR, &mask, sizeof(mask));
  mask = SETUP_AW_MASK;
  transceiverWriteRegister(SETUP_AW, &mask, sizeof(mask));    
  mask = PACKET_SIZE;
  transceiverWriteRegister(RX_PW_P0, &mask, sizeof(mask));    
  mask = DYNPD_MASK;
  transceiverWriteRegister(DYNPD, &mask, sizeof(mask));    
  mask = FEATURE_MASK;
  transceiverWriteRegister(FEATURE, &mask, sizeof(mask));    
  transceiverWriteRegister(TX_ADDR, address, 5);
  transceiverWriteRegister(RX_ADDR_P0, address, 5);
  transceiverSetChannel(2);  
  transceiverFlushStatus();
  transceiverFlushFIFO();
}

void transceiverSetChannel(unsigned char channel)
{
  unsigned char mask = channel;
  transceiverWriteRegister(RF_CH, &mask, sizeof(mask));   
}

void transceiverTrasmit()
{
  transceiverWriteRegister(W_TX_PAYLOAD, packet, PACKET_SIZE);
  nRF_CE_HIGH;
  _delay_us(15);
  nRF_CE_LOW;
  _delay_us(150);
  transceiverFlushStatus();
  transceiverFlushFIFO();
}

void transceiverFlushStatus()
{
  unsigned char mask = STATUS_CLEAR_MASK;
  transceiverWriteRegister(STATUS, &mask, sizeof(mask));
}

void transceiverFlushFIFO()
{
  transceiverCommand(FLUSH_TX);
  transceiverCommand(FLUSH_TX);
}
