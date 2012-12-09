#ifndef CRC_H
#define CRC_H

#    include <stdint.h>
#    include <cstdlib>

uint_least32_t crc32(const unsigned char * buf, size_t len);


#endif /* CRC_H */