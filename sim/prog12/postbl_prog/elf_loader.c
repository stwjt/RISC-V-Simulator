#include <string.h>
#include "elf_loader.h"
#include "mmap_soc.h"
#include "riscv_def.h"

#define ENTRY (uint64_t)(0x80200000)
#define MEGAPAGE (uint64_t)(PGSIZE << 9)
#define GIGAPAGE (uint64_t)(MEGAPAGE << 9)
#define kva2pa(x) ((uint64_t)(x) + ENTRY + (GIGAPAGE << 7))

void *elf_loader(ehdr64_t *elf)
{
    shdr64_t *sec_header =
        (shdr64_t *) ((uint64_t) elf + (uint64_t) elf->e_shoff);
    uint16_t sec_header_num = elf->e_shnum;
    uint32_t i;

    for (i = 0; i < sec_header_num; ++i) {
        if (sec_header[i].sh_type == SHT_PROGBITS && sec_header[i].sh_addr)
        {
            /* TM_PRINT="memcpy dst=%#lx src=%#lx size=%#x", kva2pa(sec_header[i].sh_addr), ((uint64_t) elf + sec_header[i].sh_offset), sec_header[i].sh_size */
            memcpy((void *)kva2pa(sec_header[i].sh_addr),
                   (const void *) ((uint64_t) elf + sec_header[i].sh_offset),
                   sec_header[i].sh_size);
        }
    }

    return (void *) elf->e_entry;
}
