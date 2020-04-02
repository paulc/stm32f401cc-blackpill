
.PHONY = libopencm3 clean_libopencm3

# Build libopencm3 for STM32F4
libopencm3: libopencm3/lib/libopencm3_stm32f4.a

libopencm3/lib/libopencm3_stm32f4.a:
	$(MAKE) -C libopencm3 TARGETS=stm32/f4

clean_libopencm3:
	rm -f libopencm3/lib/libopencm3_stm32f4.a
	-$(MAKE) -$(MAKEFLAGS) -C ./libopencm3 clean

