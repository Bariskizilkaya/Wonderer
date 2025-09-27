#include "dr_api.h"
#include <stdint.h>
static uint64_t instr_count = 0;

static void event_exit(void);
static dr_emit_flags_t event_basic_block(void *drcontext, void *tag,
                                         instrlist_t *bb, bool for_trace,
                                         bool translating);

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {
    dr_set_client_name("Instruction Counter", "https://dynamorio.org");

    dr_register_exit_event(event_exit);
    dr_register_bb_event(event_basic_block);

    dr_printf("Instruction counter client loaded\n");
}

static dr_emit_flags_t event_basic_block(void *drcontext, void *tag,
                                         instrlist_t *bb, bool for_trace,
                                         bool translating) {
    // Count instructions in this basic block
    instr_t *instr;
    for (instr = instrlist_first(bb); instr != NULL; instr = instr_get_next(instr)) {
        instr_count++;
    }
    return DR_EMIT_DEFAULT;
}

static void event_exit(void) {
    dr_printf("Total instructions executed: %llu\n",
              (unsigned long long)instr_count);
}
