#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5c7202ab, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x138fe6fb, __VMLINUX_SYMBOL_STR(nf_unregister_hook) },
	{ 0x7ed82276, __VMLINUX_SYMBOL_STR(nf_register_hook) },
	{ 0x28318305, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x92a9c60c, __VMLINUX_SYMBOL_STR(time_to_tm) },
	{ 0x4f68e5c9, __VMLINUX_SYMBOL_STR(do_gettimeofday) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xdb7305a1, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0xd46908ef, __VMLINUX_SYMBOL_STR(filp_close) },
	{ 0xb6cb30bd, __VMLINUX_SYMBOL_STR(vfs_read) },
	{ 0x53f00cac, __VMLINUX_SYMBOL_STR(filp_open) },
	{ 0x3356b90b, __VMLINUX_SYMBOL_STR(cpu_tss) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7AC90936F86CE285AEE2703");
