## Using USB Protocol 

    for (;;)
    {
        const byte_t init = read_byte();
        if (init == INIT_BYTE)
        {
            const byte_t meta_flags_byte = read_byte();
            const MetaFlags meta_flags = EXTRACT_META_FLAGS(meta_flags_byte);
            const byte_t msg_size = meta_flags.MSG_SIZE - 2;
            byte_t buffer[msg_size] = {0};
            read_buffer(buffer, msg_size);
            HANDLE_MESSAGE(buffer);
        }   
    }