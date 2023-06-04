# UART
UART and USART
- UART: universal asynchronous receiver transmitter
  - uart peripheral supports only asynchronous mode
- USART: universal synchronous asynchronous receiver transmitter
  - usart supports both synchronous and asynchronous mode

There is no specific port for usart communication. 
They are commonly used in conjugation with protocols like
RS-232, RS-434, USB etc.

In synchronous transmission, the clock is sent seperately from
the data steam and no start/stop bits are used

USART hardware components:
- baud rate generator
- TX and RX shift registers
- Transmit/receive control blocks
- Transmit/receive buffers
- First-in, first-out (FIFO) buffer memory

USART is just a piece hardware in your microcontroller which
transmits and receives data bits either in synchronous mode or in
asynchronous mode

If it is asynchronous mode, then clock will not be sent along with
the data, instead we use synchronization bits like start and stop
along with the useful data

```txt
UART 1                           UART 2
    TX ------------------------> RX
    RX <------------------------ TX
   RTS ------------------------> CTS
   CTS <------------------------ RTS
```
Where,
- TX: When hardware flow control is used, 
      the UART module will send the data out of TX line 
      only when the CTS is pulled to low
- RX: receiver.
- RTS: request to send. UART module uses this line to 
       request data from the other device. make RTS low.
- CTS: clear to send. it's a active low pin

## UART FRAME

## Baud Rate
The significance of baud rate is how fast the data is sent over a serial line
It's usually expressed in units of bit-per-second. If you invert the baud rate,
you can find out, just how long it takes to transmit a single bit.
This value determines how long the transmitter holds a serial line high or low

E.g. baud rate = 9600
1 bit duration = 1 / 9600 = 104 us

Both transmitting as well as receiving devices should operate at the same rate

## UART Parity
Adding parity bit is a simplest method of error detection. Parity is simply the
number of ones appearing in the binary form of a number

55 -> 0b00110111, the parity is 5
parity -> (1) even parity, (2) odd parity

### even parity

### odd parity


notice: even parity results in even number of 1s, wheras odd parity results in odd
number od 1s, when counted including the parity bit

## USART Transmitter
- Program the M bit usart_cr1 to define the word length
- Program the number of stop bits in usart_cr2 register
- select the desired baud rate using the usart_brr register
- Set the TE bit in usart_cr1 to enable the transmit block
- Enable the usart by wrting the ue bit in usart_cr1
- Now if txe flag is set, then write the data byte to send, in the usart_dr register
- After writing the last data into the usart_dr register, wait until TC=1

## USART Receiver
- Program the M bit in USART_CR1 to define the word length
- Program the number od stop bits in USART_CR2
- Select the desired baud rate using the USART_BRR register
- Enable the USART by wrting the UE bit in USART_CR1
- Set the RE bit in the USART_CR1 register, which enables the receiver block of the usart peripheral
- When a character is received, wait till the RXNE bit is set and read the data byte from the data register
- The RXNE bit must be cleared by reading the data register, 
  before the end of the reception of the character to avoid the overrun error

## Oversampling
- The receiver implements different user-configurable oversampling techniques (except in synchronous
  mode) for data recovery by discriminating between valid incoming data and noise
- The oversampling method can be selected by programming the OVER8 bit in the USART_CR1 register and
  can be either 16 or 8 times the baud rate clock
- Configurable oversampling method by 16 or by 8 to give flexibility between speed and clock tolerance
- We can see the NF flags to get the noise 