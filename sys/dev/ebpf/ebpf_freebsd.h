/*
 * Copyright 2017 Yutaro Hayakawa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#ifndef user
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/malloc.h>
#include <sys/systm.h>
#include <sys/libkern.h>
#include <sys/elf.h>
#include <sys/endian.h>
#include <sys/ioccom.h>
#include <sys/file.h>
#include <sys/filedesc.h>
#include <sys/fcntl.h>
#include <sys/refcount.h>
#include <sys/capsicum.h>
#include <machine/stdarg.h>

typedef struct thread ebpf_thread_t;
typedef struct file ebpf_file_t;

#define EBPF_OBJ(filep) filep->f_data

#endif

#define EBPFIOC_LOAD_PROG _IOWR('i', 151, union ebpf_req)
#define EBPFIOC_MAP_CREATE _IOWR('i', 152, union ebpf_req)
#define EBPFIOC_MAP_LOOKUP_ELEM _IOWR('i', 153, union ebpf_req)
#define EBPFIOC_MAP_UPDATE_ELEM _IOWR('i', 154, union ebpf_req)
#define EBPFIOC_MAP_DELETE_ELEM _IOWR('i', 155, union ebpf_req)
#define EBPFIOC_MAP_GET_NEXT_KEY _IOWR('i', 156, union ebpf_req)
