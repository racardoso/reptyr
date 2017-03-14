/*
 * /TODO I still need to check copyright
 *  original license is MIT
 *
 *
 *
 *
 *
*/
static struct ptrace_personality arch_personality[1] = {
  {
    // TODO: abi is not very clear about it
    offsetof(struct user, regs.gpr[3]), /* return value */
    offsetof(struct user, regs.gpr[3]), /* arg0 */
    offsetof(struct user, regs.gpr[4]), /* arg1 */
    offsetof(struct user, regs.gpr[5]), /* arg2 */
    offsetof(struct user, regs.gpr[6]), /* arg3 */
    offsetof(struct user, regs.gpr[7]), /* arg4 */
    offsetof(struct user, regs.gpr[8]), /* arg5 */
    offsetof(struct user, regs.nip),    /* ip */
  }
};

static inline void arch_fixup_regs(struct ptrace_child *child) {
  // TODO: how fixup registers for PPC64?
  child->user.regs.nip -= 4;
}

static inline int arch_set_syscall(struct ptrace_child *child,
                                   unsigned long sysno) {
  return ptrace_command(child, PTRACE_POKEUSER,
                        child->user.regs.orig_gpr3,
                        sysno);
}

static inline int arch_save_syscall(struct ptrace_child *child) {
  #define ptr(user, off) ((unsigned long*)((void*)(user)+(off)))
  child->saved_syscall = *ptr(&child->user, child->user.regs.orig_gpr3);
  return 0;
}

static inline int arch_restore_syscall(struct ptrace_child *child) {
  // TODO
  return 0;
}



