/*	Роман Сарчук (КНМС-11 / 2 група) "Dop Task"
21. Діагностування комп’ютерних несправностей  */
#include <Windows.h>
#include "Questions.h"

// Poiters
void OutputResult(void);


int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	cout << "Роман Сарчук (КНМС-11 / 2 група) ©\n" << "Діагностування комп’ютерних несправностей.\n\n";
	short answer;
	QstList basic{
		"У чому проблема?",
		"1) У роботі компютер",
		"2) У підключені до інтернета"
	};
	cout << "! Обирайте цифрою !\n\n";
	answer = Ask(basic);
	if (answer == 1)
		computer();
	else if (answer == 2)
		internet();
	OutputResult();
}


string StatOutput(ErrStatus stat)
{
	switch (stat)
	{
	case ErrStatus::SAFE:
		return "Можете вирішити проблему самі або звернутись до спеціалістів.";
		break;
	case ErrStatus::MEDIUM:
		return "Вам вартує звернутись до спеціалістів або вирішити самим, якщо ви знаєте, що робите!";
		break;
	case ErrStatus::DANGEROUS:
		return "Рекомендуєм звернутись до спеціалістів!";
		break;
	}
	return "???";
}

void OutputResult(void)
{
	cout << "#--- Результат ---#\n\n";

	for (short i = 0; i < ESIZE; i++)
	{
		if (err[i] != "")
			cout << i + 1 << ") " << err[i] << endl;
		if (status[i] != ErrStatus::NONE)
			cout << "Статус: " << StatOutput(status[i]) << endl;
		if (err[i] != "")
			cout << endl;
	}

	cout << "#-----------------#\n";
}
