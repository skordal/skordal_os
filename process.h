// SkordalOS Process Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef PROCESS_H
#define PROCESS_H

#include "asm_macros.h"
#include "types.h"

#include "mm.h"
#include "mmu.h"
#include "timer.h"

#include "hardware/timers.h"

// Register indexes in the register file structure:
#define PROCESS_SP	14

// Store register information:
typedef struct {
	// ARM registers:
	uint32_t registers[15];
	uint32_t pc;
	uint32_t cpsr;
	// NEON registers:
	uint64_t * neon_registers[32];
	uint32_t fp_status;
} __attribute((packed)) register_file_t;

// Process state information:
typedef struct {
	enum {
		RUNNING,
		SLEEPING,
	} state;

	union {

	} params;
} process_state_t;

// Process information structure:
typedef struct __process_t {
	// Next process:
	struct __process_t * next;
	// Previous process:
	struct __process_t * prev;

	// Stored registers:
	register_file_t registers;

	// MMU descriptor table:
	uint32_t * descriptor_table;

	// Process ID:
	pid_t pid;

	// Owner of the process:
	uid_t uid;
	gid_t gid;

	// Process state:
	process_state_t state;
} process_t;

// Executable file header:
typedef struct {
	void * start_address;
	uint32_t magic_bytes;
	void * data_section_start;
	void * bss_section_start;
	void * end_address;
} __attribute((packed)) process_header_t;

// Initializes the process manager:
void process_init_mgr();

// Creates a process from the specified data buffer:
process_t * process_create(void * data_buffer);

// Process switch timer interrupt handler:
void process_switch_handler();

#endif

