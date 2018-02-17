/* 
 * Copyright (c) 2017 Yutaro Hayakawa
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */

#include <dev/ebpf/ebpf_platform.h>
#include <sys/ebpf.h>
#include <sys/ebpf_vm.h>
#include <dev/ebpf/ebpf_prog.h>
#include <dev/ebpf/ebpf_map.h>

void *
ebpf_malloc(size_t size)
{
    return kmalloc(size, GFP_KERNEL);
}

void *
ebpf_calloc(size_t number, size_t size)
{
    void *ret = kmalloc(number * size, GFP_KERNEL);
    if (ret == NULL) {
        return NULL;
    }

    memset(ret, 0, number * size);

    return ret;
}

void *
ebpf_exalloc(size_t size)
{
    return __vmalloc(size, GFP_KERNEL, PAGE_KERNEL_EXEC);
}

void
ebpf_exfree(void *mem, size_t size)
{
    vfree(mem);
}

void
ebpf_free(void *mem)
{
    kfree(mem);
}

int
ebpf_error(const char *fmt, ...)
{
    int ret;
    va_list ap;

    va_start(ap, fmt);
    ret = vprintk(fmt, ap);
    va_end(ap);

    return ret;
}

void
ebpf_assert(bool expr)
{
    BUG_ON(!(expr));
}

uint16_t
ebpf_ncpus(void) {
    return nr_cpu_ids;
}

static int
ebpf_init(void)
{
    printk("ebpf loaded\n");
    return 0;
}

static void
ebpf_fini(void)
{
    printk("ebpf unloaded\n");
}

EXPORT_SYMBOL(ebpf_create);
EXPORT_SYMBOL(ebpf_destroy);
EXPORT_SYMBOL(ebpf_register);
EXPORT_SYMBOL(ebpf_load);
EXPORT_SYMBOL(ebpf_load_elf);
EXPORT_SYMBOL(ebpf_exec);
EXPORT_SYMBOL(ebpf_exec_jit);
EXPORT_SYMBOL(ebpf_compile);
EXPORT_SYMBOL(ebpf_malloc);
EXPORT_SYMBOL(ebpf_calloc);
EXPORT_SYMBOL(ebpf_free);
EXPORT_SYMBOL(ebpf_exalloc);
EXPORT_SYMBOL(ebpf_exfree);
EXPORT_SYMBOL(ebpf_error);
EXPORT_SYMBOL(ebpf_assert);
EXPORT_SYMBOL(ebpf_ncpus);
EXPORT_SYMBOL(ebpf_prog_init);
EXPORT_SYMBOL(ebpf_prog_deinit_default);
EXPORT_SYMBOL(ebpf_prog_deinit);
EXPORT_SYMBOL(ebpf_map_delete_elem);
EXPORT_SYMBOL(ebpf_map_lookup_elem);
EXPORT_SYMBOL(ebpf_map_update_elem);
EXPORT_SYMBOL(ebpf_map_get_next_key);
EXPORT_SYMBOL(ebpf_map_init);
EXPORT_SYMBOL(ebpf_map_deinit_default);
EXPORT_SYMBOL(ebpf_map_deinit);

module_init(ebpf_init);
module_exit(ebpf_fini);
MODULE_AUTHOR("Yutaro Hayakawa");
MODULE_DESCRIPTION("Generic eBPF Module");
MODULE_LICENSE("GPL");
