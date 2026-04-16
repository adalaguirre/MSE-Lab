/* Defining Firmware's entry point */
ENTRY(Reset_Handler)

/* Defining memory sections */
MEMORY{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K  
}
/**
  *  attributes:
  *  r: Allows memory to be read.
  *  w: Permits data to be written to the memory
  *  x: Allows the execution of code from the specified memory region
  *  empty: Does not grant any access permissions by default.
*/

/* Defining top the the stack */

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

/** Symbol Creation
  *  Symbols are identifiers that can reference a memory location,
  *  value or address within the memory space.
  *  Symbols can be referenced in the linker script but also in the C code.
  *  Examples of important symbols:
  *  _estack, __max_heap_size, _etext, _sbss, _ebss, etc.
*/

SECTIONS{
    .text : {
        . = ALIGN(4);
        *(.isr_vector_tbl)
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } >FLASH
    .data : {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } >SRAM AT>FLASH /* execute in VMA store at LMA */
    .bss : {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    } >SRAM
}

/** Sections Directive
  *  output_section_name: Output section being defined (e.g., .text, .data)
  *  input_section_information: Input sections to be included. Wildcards suach as *(.text) can
  *  be used to include all .text from all input files.
  *  >memory_region: Assigns section to a specific memory region defined in MEMORY.
  *  AT>load_address: This is optional. Specifies the load address of the section.
*/

/** Keep Directive
  *  The KEEP directive ensures that specified sections or symbols are
  *  not eliminated by the linker during the optimization process, even
  *  if they appear unused.
*/

/** Align Directive
  *  The ALIGN directive adjust the location counter to align with
  *  specified memory boundaries. The location counter is a built-in
  *  variable(.) that represents the current address in memory where
  *  The linker is placing section during the linking process.
*/