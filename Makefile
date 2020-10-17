podcrc: ccitt32_crc.o podcrc.o
	$(CC) $(CFLAGS) ccitt32_crc.o podcrc.o -o podcrc
clean: ccitt32_crc.o podcrc.o podcrc
	$(RM) ccitt32_crc.o podcrc.o podcrc
