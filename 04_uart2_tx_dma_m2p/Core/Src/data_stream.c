#include <stdint.h>

uint8_t data_stream[] = "Memeory to peripheral Data Transfer\
===================================\
1) Each time a pheripheral request occurs, the data item is moved from memory to the peripheral register.\
2) Here also there are 2 modes\
	i) Direct mode (FIFO is used without threshhold)\
	ii) FIFO mode   (FIFO is used with threshhold)\
3) In direct mode the threshold level of the FIFO is not used. Once the steam is enabled, the DMA preloads the first data to \
transfer into an internal FIFO. As soon as the peripheral requests a data transfer, the DMA transfers the preloaded value into the configured destination. It then \
reloads again the empty internal FIFO with the next data to be tranfered.\
4) In FIFO mode, as soon as you enable the stream, the FIFO will be preloaded fully from memory. When peripheral	 requests for a data tranfer the contents of the FIFO are drained and stored into the destination.\
When the level of the FIFO is lower than or equal to the predefined threshold level, the FIFO is fully reloaded with data from the memory.";

uint32_t data_length = sizeof(data_stream);
