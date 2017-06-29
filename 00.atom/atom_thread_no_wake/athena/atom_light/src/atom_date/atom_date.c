#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/wait.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/time.h>

#include <asm/io.h>
#include <asm/uaccess.h>

#include <linux/hrtimer.h>
#include <linux/sched/rt.h>
#include <linux/ktime.h>
#include <linux/version.h>
#include <linux/mutex.h>
#include <linux/i2c.h>
#include <linux/leds.h>

#include "../../inc/atom_light_out.h"
//#include "../atom_pwm/atom_pwm.h"
#include "../atom_timer/atom_timer.h"

#define plog(x...) printk("lynn_pwm_led " x)

//#define FIX_LOW_TIME 10*US 
//static long long ppm_values[2] = {FIX_LOW_TIME,90*US};

static int constant_atom_ioctl(unsigned int cmd, unsigned long arg)
{
	int i4RetValue = 0;
//	int ior_shift;
//	int iow_shift;
//	int iowr_shift;
//
//	ior_shift = cmd - (_IOR(FLASHLIGHT_MAGIC, 0, int));
//	iow_shift = cmd - (_IOW(FLASHLIGHT_MAGIC, 0, int));
//	iowr_shift = cmd - (_IOWR(FLASHLIGHT_MAGIC, 0, int));
/*	PK_DBG
	    ("LM3642 constant_flashlight_ioctl() line=%d ior_shift=%d, iow_shift=%d iowr_shift=%d arg=%d\n",
	     __LINE__, ior_shift, iow_shift, iowr_shift, (int)arg);
*/
	switch (cmd) {

	case ATOM_WRITE_INT:
 
//        _atom_sub_led_pin_pwm2_out_pwm();
		break;


	case ATOM_WRITE_OFF:
        timer_stop();
//         close_pwm();
        _atom_en_pin_output_low();
		break;


	case ATOM_WRITE_ON:
       timer_start();
//        _atom_sub_led_pin_pwm2_out_pwm();
//        open_pwm(99,arg);

//        if(arg)
//            _atom_en_pin_output_high();
//        else
//            _atom_en_pin_output_low();
		break;


	default:

		break;
	}
	return i4RetValue;
}




static int constant_atom_open(void *pArg)
{
	int i4RetValue = 0;

    plog("%s\n", __func__);
//	INIT_WORK(&workTimeOut, work_timeOutFunc);
    dw_fp_key_sys_init();
//    _atom_en_pin_output_high();
    return i4RetValue;

}


static int constant_atom_release(void *pArg)
{
	return 0;

}


ATOM_FUNCTION_STRUCT constant_atom_Func = {
	constant_atom_open,
	constant_atom_release,
	constant_atom_ioctl
};


MUINT32 constant_atom_Init(P_ATOM_FUNCTION_STRUCT *pfFunc)
{
	if (pfFunc != NULL)
		*pfFunc = &constant_atom_Func;
	return 0;
}



/* LED flash control for high current capture mode*/
ssize_t atom_data_VDIrq(void)
{
	return 0;
}
EXPORT_SYMBOL(atom_data_VDIrq);
