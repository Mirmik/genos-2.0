#include <hal/board.h>

#include <arch/irqs.h>
#include <arch/gpio.h>
#include <arch/uart.h>

#include <genos/systime.h>
#include <drivers/uartring.h>
//
#include <genos/tasklet.h>
#include <genos/timer.h>
#include <genos/schedule.h>
#include <genos/sched/schedee.h>

#include <gxx/history.h>

#include <genos/banner.h>
#include <genos/apps/history_terminal.h>

char serbuf[48], iserbuf[8];
arch::usart u0(usart0_data);
drivers::uartring serial(&u0, serbuf, iserbuf);

genos::history_terminal term(serial, gxx::history(10));

void reader_func(); genos::tasklet reader_tasklet { reader_func };
void reader_func() {
	while(serial.avail()) serial.putchar(serial.getchar()); 
	serial.set_avail_callback(reader_tasklet.make_plan_delegate());
}

arch::gpio::pin rled(GPIOB, 7);
arch::gpio::pin gled(GPIOC, 7);
arch::gpio::pin yled(GPIOC, 6);

genos::timer gblink_timer ( gxx::make_delegate(&arch::gpio::pin::tgl, &gled), 1000, 0 );
genos::timer yblink_timer ( gxx::make_delegate(&arch::gpio::pin::tgl, &yled), 500, 0 );
genos::timer rblink_timer ( gxx::make_delegate(&arch::gpio::pin::tgl, &rled), 250, 0 );


//genos::tasklet_terminal term;

int main() {
	board_init();
	
	rled.mode(hal::gpio::output);
	gled.mode(hal::gpio::output);
	yled.mode(hal::gpio::output);

	rled.set();
	gled.set();
	yled.set();

	u0.setup(115200); 

	serial.init();
	serial.set_avail_callback(reader_tasklet.make_plan_delegate());

	u0.enable();
	arch::irqs::enable();

	genos::print_banner(serial);
	genos::print_about(serial);

	rblink_timer.autorepeat(true).plan();
	gblink_timer.autorepeat(true).plan();
	yblink_timer.autorepeat(true).plan();

	while(1) {
		genos::schedule();
	}
}

void genos::schedule() {
		genos::tasklet_manager.execute();
		genos::timer_manager.execute();
		genos::schedee_manager.execute();
}