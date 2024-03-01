#include "msg_types.h"

#define FLAG_0 0x00
#define FLAG_1 0x01
#define FLAG_2 0x02
#define FLAG_3 0x03
#define FLAG_4 0x04
#define FLAG_5 0x05
#define FLAG_6 0x06
#define FLAG_7 0x07

typedef byte_t num_bytes;

                                /* Meta Flags */
                    /*   10   |   10   |   10   |   10   */
                    /*  RSVD     RSVD     RSVD     SIZE  */
typedef struct MetaFlags {
    const byte_t RSVD_0;
    const byte_t RSVD_1;
    const byte_t RSVD_2;
    const byte_t MSG_SIZE;
} MetaFlags;                  

MetaFlags EXTRACT_META_FLAGS(const byte_t meta_flags);

                            /* Data Flags */
                    /*   10   |   10   |   10   |   10   */
                    /*  RSVD     RSVD     RSVD     TYPE  */

byte_t COMPOSE_META_FLAGS(const MetaFlags* meta_flags);

typedef struct DataFlags {
    const byte_t RSVD_0;
    const byte_t RSVD_1;
    const byte_t RSVD_2;
    const byte_t MSG_TYPE;
} DataFlags; 

DataFlags EXTRACT_DATA_FLAGS(const byte_t data_flags);