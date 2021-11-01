typedef  unsigned char uint8_t;


#define F_CPU 1000000UL

#define TCCRO (*((volatile uint8_t * ) (0x33)  )) 

#define TCNTO (*((volatile uint8_t * )  (0x32) ))

#define TIMSK (*((volatile uint8_t * ) (0x39) ))

#define DDRA   (*((volatile uint8_t * ) (0x1A) ))

#define PORTA (*((volatile uint8_t * ) (0x1B) ))

#define PA0 0

#define WGM00 6

#define WGM01 3

#define COM00 4

#define COM01 5

#define CS00    0

#define CS01    1

#define CS02    2

#define TOIE0    0


// initialize delay

volatile uint8_t delay = 200;


ISR(TOV0_VECT)

{

	PORTA ^= (1<<PA0);

	TCNT0 = delay;

}


void TIMER_init()

{

	TCCR0 &=~((1<<WGM00) | (1<<WGM01) | (1<<COM00) | (1<<COM01));

	TIMSK |= (1<<TOIE0);

	TCNT0 = 0;

}


void TIMER_start(void)

{

	TCCR0 |= (1<<CS01);

}


void TIMER_stop(void)

{

	TCCR0 &=~( (1<<CS02) | (1<<CS01) | (CS00) );

}


void TIMER_set(uint8_t value)

{

	TCNT0 = value;

}


uint8_t TIMER_get(void)

{

	return TCNT0;

}


void main(void)

{


	

	// intialize DIO

	DDRA |= (1<<PA0);

	PORTA &= ~(1<<PA0);	

	

	// initialize Timer

	TIMER_init();

	TIMER_set(delay);

	TIMER_start();

	while(1);

	






}
