/**
 * @file usart.c
 *
 * Describe the driver implementation for the USART of the ATMega328p.
 */

#include <Lazuli/sys/arch/AVR/usart.h>
#include <Lazuli/sys/config.h>

/**
 * The baud rate value to set in UBRR0.
 */
#define UBRR0_VALUE ((CLOCK_FREQUENCY / 16 * USART_BAUD_RATE) - 1)

/**
 * A constant pointer to the memory mapped Usart structure.
 */
static Usart * const usart = (Usart*)&UCSR0A;

void
Usart_Init()
{
  /* Set baud rate */
  usart->ubrr0l = 12; /* LO8(UBRR0_VALUE); */
  usart->ubrr0h = 0; /* HI8(UBRR0_VALUE); */

  /* Enable transmitter */
  usart->ucsr0b = UCSR0B_TXEN0;

  /* 8 bits, 1 stop bit, no parity */
  usart->ucsr0c = UCSR0C_UCSZ01 | UCSR0C_UCSZ00;
}

void
Usart_PutChar(char c)
{
  while(!(usart->ucsr0a & UCSR0A_UDRE0));

  usart->udr0 = c;
}

/* TODO: Store this is program memory */
/**
 * Array used to get the character representation of a hexadecimal digit
 */
static const char hexachars[] = {
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  'a',
  'b',
  'c',
  'd',
  'e',
  'f'
};

/**
 * Union to access individual bytes of an integer value (with a maximum width of
 * 32 bits).
 */
typedef union {
  void *pointer;  /** < Holds the pointer value              */
  u8    u8Value;  /** < Holds the 8-bits value               */
  u16   u16Value; /** < Holds the 16-bits value              */
  u32   u32Value; /** < Holds the 32-bits value              */
  char  bytes[4]; /** < Easily access each byte of the value */
}IntegerBytes;

/**
 * Print a numerical value stored in an IntegerBytes union to its hexadecimal
 * form, accordig to the correct length.
 *
 * This serves as the base implementation for all specialized
 * Usart_HexaPrint_<*>() functions.
 *
 * @param intergerBytes A pointer to the IntergerBytes union to print.
 * @param size The size in bytes of the value to print.
 */
static void
Usart_HexaPrint_IntegerBytes(IntegerBytes const * const integerBytes,
                             const size_t size)
{
  u8 i;
  u8 upperPart;
  u8 lowerPart;

  Usart_PutChar('0');
  Usart_PutChar('x');

  for (i = size; i != 0; i--) {
    upperPart = (integerBytes->bytes[i - 1] >> 4) & 0x0f;
    lowerPart = integerBytes->bytes[i - 1] & 0x0f;

    Usart_PutChar(hexachars[upperPart]);
    Usart_PutChar(hexachars[lowerPart]);
  }
}

void
Usart_HexaPrint_u32(const u32 value)
{
  IntegerBytes integerBytes;
  integerBytes.u32Value = value;

  Usart_HexaPrint_IntegerBytes(&integerBytes, sizeof(u32));
}

void
Usart_HexaPrint_u16(const u16 value)
{
  IntegerBytes integerBytes;
  integerBytes.u16Value = value;

  Usart_HexaPrint_IntegerBytes(&integerBytes, sizeof(u16));
}

void
Usart_HexaPrint_u8(const u8 value)
{
  IntegerBytes integerBytes;
  integerBytes.u8Value = value;

  Usart_HexaPrint_IntegerBytes(&integerBytes, sizeof(u8));
}

void
Usart_HexaPrint_Pointer(void * const pointer)
{
  IntegerBytes integerBytes;
  integerBytes.pointer = pointer;

  Usart_HexaPrint_IntegerBytes(&integerBytes, sizeof(void *));
}

