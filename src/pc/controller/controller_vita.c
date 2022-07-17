#if defined(TARGET_VITA)

#include <psp2/ctrl.h>

#include <ultra64.h>

#include "controller_api.h"

#define DEADZONE 20

static void vita_init(void) {
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
}

static void vita_read(OSContPad *pad) {
    SceCtrlData ctrl;
    sceCtrlPeekBufferPositive(0, &ctrl, 1);

    if (ctrl.buttons & SCE_CTRL_UP)       pad->button |= U_JPAD;
    if (ctrl.buttons & SCE_CTRL_DOWN)     pad->button |= D_JPAD;
    if (ctrl.buttons & SCE_CTRL_LEFT)     pad->button |= L_JPAD;
    if (ctrl.buttons & SCE_CTRL_RIGHT)    pad->button |= R_JPAD;
    if (ctrl.buttons & SCE_CTRL_START)    pad->button |= START_BUTTON;
    if (ctrl.buttons & SCE_CTRL_LTRIGGER) pad->button |= Z_TRIG;
    if (ctrl.buttons & SCE_CTRL_RTRIGGER) pad->button |= L_TRIG;
    if (ctrl.buttons & SCE_CTRL_CROSS)    pad->button |= A_BUTTON;
    if (ctrl.buttons & SCE_CTRL_CIRCLE)   pad->button |= B_BUTTON;
    if (ctrl.buttons & SCE_CTRL_SQUARE)   pad->button |= B_BUTTON;
    if (ctrl.buttons & SCE_CTRL_TRIANGLE) pad->button |= R_TRIG;

    pad->stick_x = (s8)((s32) ctrl.lx - 128);
    pad->stick_y = (s8)(-((s32) ctrl.ly - 127));

    // Taken from SDL controller backend.
    uint32_t magnitude_sq = (uint32_t)(pad->stick_x * pad->stick_x) + (uint32_t)(pad->stick_y * pad->stick_y);
    if (magnitude_sq < (uint32_t)(DEADZONE * DEADZONE)) {
        pad->stick_x = 0;
        pad->stick_y = 0;
    }

    if (ctrl.rx < 40)
        pad->button |= L_CBUTTONS;
    if (ctrl.rx > 200)
        pad->button |= R_CBUTTONS;
    if (ctrl.ry < 40)
        pad->button |= U_CBUTTONS;
    if (ctrl.ry > 200)
        pad->button |= D_CBUTTONS;
}

struct ControllerAPI controller_vita = {
    vita_init,
    vita_read
};

#endif
