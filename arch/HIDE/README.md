На примере avr преполагается следующая структура каталогов

ldscripts 							- скрипты линкёра
include/arch 						- заголовки, касающиеся ядра (не переферии)
include/asm/{limits.h, types.h} 	- согласно стандарту
include/periph						- базовый код переферии :
	{/irqdefs.h}					- карта прерываний
	{/regs/\*}						- регистры переферии и базовые операции
src/\*								- компилируемый код.

TODO: avr - убрать таймер из arch. Перенести в драйверы.