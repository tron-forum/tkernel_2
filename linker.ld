/* linker.ld - 멀티부트 커널 배치 (1 MiB 적재) */
ENTRY(_start)

SECTIONS
{
	. = 1M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text*)
	}

	.rodata BLOCK(4K) : ALIGN(4K) { *(.rodata*) }
	.data   BLOCK(4K) : ALIGN(4K) { *(.data*) }
	.bss    BLOCK(4K) : ALIGN(4K) { *(COMMON) *(.bss*) }

	/DISCARD/ : { *(.comment) *(.eh_frame) *(.note*) }
}
