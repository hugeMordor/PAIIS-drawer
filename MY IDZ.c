
#include "5510drv.h"

//Сигналы на обмотку двагателей
unsigned char Signal[2] = {0, 1};
unsigned char Work[2] = {0, 1};

//Сигнал состояния пера и кнопки Stand_By
unsigned char Stand_By = 0;

//Переменные для номеров слотов
unsigned char _5050_0 = 0;
unsigned char _5050_1 = 1;

//Декларирование функций
void Motor(char Slot, char Course);
void Pen_State(char State);

void main()
{
	//Дополнительные переменные для циклов
	int i;
	int j;
	int x;
	
	// Дополнительные переменные для рисования
	float deltamax= 1.1f;
	float deltamin = 0.9f;

	//Ожидание нажатия кнопки Stand_By
	while(Stand_By == 0)
	{
		//Сигналы на обмотку первого мотора 0 0 0 0
		Set5050(&Signal[0], _5050_0, 0, ABit);
		Set5050(&Signal[0], _5050_0, 1, ABit);
		Set5050(&Signal[0], _5050_0, 2, ABit);
		Set5050(&Signal[0], _5050_0, 3, ABit);
		//Сигналы на обмотку второго мотора 0 0 0 0
		Set5050(&Signal[0], _5050_1, 0, ABit);
		Set5050(&Signal[0], _5050_1, 1, ABit);
		Set5050(&Signal[0], _5050_1, 2, ABit);
		Set5050(&Signal[0], _5050_1, 3, ABit);
		//Поднять перо и проверить Stand_By
		Set5050(&Work[0], _5050_0, 4, ABit);
		Get5050(_5050_1, 4, ABit, &Stand_By);
	}
	
	//Смещение пера вправо и вверх на 10 см
	for(i = 0; i < 100; i++)
	{
		Motor(_5050_0, 'R');
		Motor(_5050_1, 'U');
	}

	//Опустить перо и нарисовать 10 см линию под углом 60° вправо и вниз
	Pen_State('D');
	x=0;
	for(i=0;i<87;i++){
		Motor(_5050_1, 'D');
		if(i<=(deltamax*x*1000/577) && i>=(deltamin*x*1000/577)){
			x++;
			Motor(_5050_0, 'R');
		}
	}

	//Нарисовать 10 см линию под углом 60° вправо и вверх
	x=0;
	for(i=0;i<87;i++){
		Motor(_5050_1, 'U');
		if(i<=(deltamax*x*1000/577) && i>=(deltamin*x*1000/577)){
			x++;
			Motor(_5050_0, 'R');
		}
	}

	//Нарисовать 10 см линию влево
	for(i=0;i<111;i++){
		Motor(_5050_0, 'L');
	}

	//Поднять перо и сместиться на 5 см под углом 60° вправо и вниз
	Pen_State('U');
	x = 0;
	for (i = 0; i < 44; i++) {
		Motor(_5050_1, 'D');
		if (i <= (deltamax * x * 1000 / 577) && i >= (deltamin * x * 1000 / 577)) {
			x++;
			Motor(_5050_0, 'R');
		}
	}

	//Опустить перо и нарисовать медиану под углом 30° вправо и вверх
	Pen_State('D');
	x = 0;
	for (i = 0; i < 80; i++) {
		Motor(_5050_0, 'R');
		if (i <= (deltamax * x * 1000 / 500) && i >= (deltamin * x * 1000 / 500)) {
			x++;
			Motor(_5050_1, 'U');
		}
	}

	//Поднять перо и сместиться на 5 см под углом 60° влево и вниз
	Pen_State('U');
	x = 0;
	for (i = 0; i < 44; i++) {
		Motor(_5050_1, 'D');
		if (i <= (deltamax * x * 1000 / 577) && i >= (deltamin * x * 1000 / 577)) {
			x++;
			Motor(_5050_0, 'L');
		}
	}

	//Опустить перо и нарисовать медиану под углом 30° влево и вверх
	Pen_State('D');
	x = 0;
	for (i = 0; i < 80; i++) {
		Motor(_5050_0, 'L');
		if (i <= (deltamax * x * 1000 / 495) && i >= (deltamin * x * 1000 / 495)) {
			x++;
			Motor(_5050_1, 'U');
		}
	}

	//Поднять перо и сместиться на 5 см вправо
	Pen_State('U');
	for (i = 0; i < 56; i++) {
		Motor(_5050_0, 'R');
	}

	//Опустить перо и нарисовать медиану вниз
	Pen_State('D');
	for (i = 0; i < 87; i++) {
		Motor(_5050_1, 'D');
	}

	//Поднять перо
	Pen_State('U');
}

void Motor(char Slot, char Course)
{
	if (Course == 'U' && Slot == 1 || Course == 'R' && Slot == 0)
	{
		//Сигналы на обмотку 1 0 0 1
		Set5050(&Signal[1], Slot, 0, ABit);
		Set5050(&Signal[0], Slot, 1, ABit);
		Set5050(&Signal[0], Slot, 2, ABit);
		Set5050(&Signal[1], Slot, 3, ABit);
		ADAMdelay(10);
		//Сигналы на обмотку 1 1 0 0
		Set5050(&Signal[1], Slot, 0, ABit);
		Set5050(&Signal[1], Slot, 1, ABit);
		Set5050(&Signal[0], Slot, 2, ABit);
		Set5050(&Signal[0], Slot, 3, ABit);
		ADAMdelay(10);
		//Сигналы на обмотку 0 1 1 0
		Set5050(&Signal[0], Slot, 0, ABit);
		Set5050(&Signal[1], Slot, 1, ABit);
		Set5050(&Signal[1], Slot, 2, ABit);
		Set5050(&Signal[0], Slot, 3, ABit);
		ADAMdelay(10);
		//Сигналы на обмотку 0 0 1 1
		Set5050(&Signal[0], Slot, 0, ABit);
		Set5050(&Signal[0], Slot, 1, ABit);
		Set5050(&Signal[1], Slot, 2, ABit);
		Set5050(&Signal[1], Slot, 3, ABit);
		ADAMdelay(10);
	}
	else if(Course == 'D' && Slot == 1 || Course == 'L' && Slot == 0)
	{
		//Сигналы на обмотку 0 0 1 1
		Set5050(&Signal[0], Slot, 0, ABit);
		Set5050(&Signal[0], Slot, 1, ABit);
		Set5050(&Signal[1], Slot, 2, ABit);
		Set5050(&Signal[1], Slot, 3, ABit);
		ADAMdelay(10);
		//Сигналы на обмотку 0 1 1 0
		Set5050(&Signal[0], Slot, 0, ABit);
		Set5050(&Signal[1], Slot, 1, ABit);
		Set5050(&Signal[1], Slot, 2, ABit);
		Set5050(&Signal[0], Slot, 3, ABit);
		ADAMdelay(10);
		//Сигналы на обмотку 1 1 0 0
		Set5050(&Signal[1], Slot, 0, ABit);
		Set5050(&Signal[1], Slot, 1, ABit);
		Set5050(&Signal[0], Slot, 2, ABit);
		Set5050(&Signal[0], Slot, 3, ABit);
		ADAMdelay(10);
		//Сигналы на обмотку 1 0 0 1
		Set5050(&Signal[1], Slot, 0, ABit);
		Set5050(&Signal[0], Slot, 1, ABit);
		Set5050(&Signal[0], Slot, 2, ABit);
		Set5050(&Signal[1], Slot, 3, ABit);
		ADAMdelay(10);
	}
}

void Pen_State(char State)
{
	if(State == 'U')
	{
		Set5050(&Work[0], _5050_0, 4, ABit);
	}
	else if(State == 'D')
	{
		Set5050(&Work[1], _5050_0, 4, ABit);
	}
}