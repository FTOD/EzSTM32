#ifndef ITM_H
#define ITM_H
#include <stdint.h>
#include <printf.h>

// Debug Exception and Monitor Control Register base address
#define DBG_DEMCR        		*((volatile uint32_t*) 0xE000EDFCU )
#define DBG_DEMCR_TRCENA		( 1 << 24)

// ITM register addresses 
#define ITM_STIMULUS_PORT0   	*((volatile uint32_t*) 0xE0000000 )
#define ITM_TRACE_EN          	*((volatile uint32_t*) 0xE0000E00 )
#define ITM_TRACE_EN_PORT0		(1 << 0)


class ITM{
	public:
		static int printf_(const char* format, ...)	{
			va_list va;
			va_start(va, format);
			int ret = vprintf(format, va);
			va_end(va);
			return ret;
		}
};

void ITM_putc(uint8_t ch);
void ITM_puts(const char *s);

inline void _putchar(char character){
	ITM_putc(character);
}
#endif //ITM_H
