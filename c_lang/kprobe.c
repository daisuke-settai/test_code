#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

MODULE_DESCRIPTION("kprobe test");
MODULE_AUTHOR("y.kitamura");
MODULE_LICENSE("GPL");

static void printk_regs(const char* msg, struct kprobe *p, struct pt_regs *regs);

static int pre_kprobe(struct kprobe *p, struct pt_regs *regs)
{
      printk_regs("pre kprobe", p, regs);
      return 0;
}

static void post_kprobe(struct kprobe *p, struct pt_regs *regs,
                              unsigned long flags)
{
      printk_regs("post kprobe", p, regs);
}

static void printk_regs(const char* msg, struct kprobe *p, struct pt_regs *regs)
{
      printk(KERN_INFO "%s:"
                      "p->addr = 0x%p, ip = %lx\n"
                      "    ax=0x%lx,bx=0x%lx\n"
                      "    cx=0x%lx,dx=0x%lx\n"
                      "    sp=0x%lx\n\n",
              msg,
              p->addr, regs->ip,
              regs->ax, regs->bx, regs->cx, regs->dx, regs->sp);
}

static struct kprobe kp = {
      .symbol_name    = "do_fork",
      .pre_handler = pre_kprobe,
      .post_handler = post_kprobe,
};

static int __init kprobe_init(void)
{
      int ret;

      ret = register_kprobe(&kp);
      if (ret < 0) {
              return -1;
      }
      return 0;
}

static void __exit kprobe_exit(void)
{
      unregister_kprobe(&kp);
}

module_init(kprobe_init)
module_exit(kprobe_exit)
