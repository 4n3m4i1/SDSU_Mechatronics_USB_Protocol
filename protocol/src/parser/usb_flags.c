#include "usb_flags.h"

#define GET_FLAG(flag_position, byte) ((byte) & (1 << (flag_position)))

const byte_t MSG_SIZES[4] = {EMPTY_MSG, SML_MSG_SIZE, MED_MSG_SIZE, LRG_MSG_SIZE};

num_bytes get_msg_size(const byte_t meta_flags)
{
    const byte_t MSG_SIZE_MASK = 0b00000011;
    const byte_t msg_size = meta_flags & MSG_SIZE_MASK;
    return MSG_SIZES[msg_size];
}

MetaFlags EXTRACT_META_FLAGS(const byte_t meta_flags)
{
    return (MetaFlags)
    {   .RSVD_0     = 0, 
        .RSVD_1     = 0, 
        .RSVD_2     = 0, 
        .MSG_SIZE   = get_msg_size(meta_flags)
    };
}

/* TODO */
DataFlags EXTRACT_DATA_FLAGS(const byte_t data_flags)
{
    return (DataFlags)
    {   .RSVD_0     = 0, 
        .RSVD_1     = 0, 
        .RSVD_2     = 0, 
        .MSG_TYPE   = 0
    };
}
