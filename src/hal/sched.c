#include "sched.h"
#include "tim.h"

void sched_init(uint32_t period) {
    tim_reload_set(SCHED_TIMG, SCHED_TIM, period);
    tim_write     (SCHED_TIMG, SCHED_TIM, period);
    tim_alarm_set (SCHED_TIMG, SCHED_TIM, 0);
    tim_alarm_en  (SCHED_TIMG, SCHED_TIM, 1);
    tim_config    (SCHED_TIMG, SCHED_TIM, 1, 0, 1, 54);
    
    krnl_log("K-SCHED", "initialized: switch period %d us", period);
}