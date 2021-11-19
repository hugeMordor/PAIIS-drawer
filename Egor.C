
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
	int cnt;
	int temp;
	int time;

	//Тут попытки все сделать через таймер, но он не работает как надо
	/*
	int idx;
	int mtime = 1000;
	Timer_Init();
	idx = Timer_Set(mtime);
	
	while (tmArriveCnt[idx] == 0)
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
		if (Stand_By == 1 && cnt == temp) {
			cnt++;
		}
		else if (Stand_By == 0 && cnt != temp) {
			temp++;
		}
	}
	*/

	//Тут я сделал задержку тупо через нагрузку системы, мол он бегает по циклу много раз,
	//и в это же время проверяет и считает нажатия кнопки 
	//Ожидание нажатия кнопки Stand_By
	while (time <= 1000)//Максимальную задержку меняй в зависимости от нужного времени,
	{					//хотя я не знаю, влияет ли на нее мощность компьютера
	
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
		//Тут считает нажатия
		if (Stand_By == 1 && cnt == temp) {
			cnt++;
		}
		else if (Stand_By == 0 && cnt != temp) {
			temp++;
		}
		time++;
	}
	//Если кнопка не была ни разу нажата
	if (cnt == 0) {
		while (Stand_By == 0) {//То ждет ее нажатия
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
		time = 0;
		while (time <= 1000)//После нажатия запускает задержку и считывает нажатия
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

			if (Stand_By == 1 && cnt == temp) {
				cnt++;
			}
			else if (Stand_By == 0 && cnt != temp) {
				temp++;
			}
			time++;
		}
		cnt++;//Увеличение еще на 1 из-за того, что для запуска задержки была нажата кнопка
	}

	//Смещение пера вправо и вверх на 5 см
		for (i = 0; i < 50; i++)
		{
			Motor(_5050_0, 'R');
			Motor(_5050_1, 'U');
		}
	//Рисует несколько 2 см линий с промежутками в 1 см столько раз, сколько нажали кнопку
		for (j = 0; j < cnt; j++) {
			Pen_State('D');
			for (i = 0; i < 20; i++)
			{
				Motor(_5050_0, 'R');
			}
			Pen_State('U');
			for (i = 0; i < 10; i++)
			{
				Motor(_5050_0, 'R');
			}
		}
	
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