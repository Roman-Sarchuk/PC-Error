#include "query.h"


void internet(void)
{
	enum ConnectTypeList
	{
		WIRED,
		WIRELESS
	};
	short connect, answer;

	// *********
	QstList connecting{
		"Яке у вас підключення?",
		"1) Дротове",
		"2) Без дротове"
	};
	connect = Ask(connecting);
	switch (connect)
	{
	case 1:		// Wired
		connect = ConnectTypeList::WIRED;
		break;
	case 2:		// Wireless
		connect = ConnectTypeList::WIRELESS;
		break;
	}

	// *********
	QstList wifistaus{
		"Який статутс підключення?",
		"1) Немає підключення",
		"2) Підключенно, але без доступу до інтернета"
	};
	answer = Ask(wifistaus);
	switch (answer)
	{
	case 1:		// <- No cnct
		switch (connect)
		{
		case ConnectTypeList::WIRED:
			err[0] = "Перевірте чи підключений кабель";
			err[1] = "Пошкодження інтернет кабеля";
			status[1] = ErrStatus::DANGEROUS;
			break;
		case ConnectTypeList::WIRELESS:
			err[0] = "Перевірте чи включений wifi на пристрої";
			err[1] = "Перевірте чи все впроядку з роутером";
			err[2] = "Роутер може бути не коректно налаштований";
			status[2] = ErrStatus::MEDIUM;
			break;
		}
		break;
	case 2:		// <- Cnct no intrn
		// *********
		answer = Ask("Ви оплатили інтернет?");
		switch (answer)
		{
		case 1:		// <- paid
			if (connect == ConnectTypeList::WIRELESS)
				err[0] = "Перезапустити роутер";
			err[1] = "Перезапустити Комп'ютер";
			err[2] = "Провести діагностику мережі";
			err[3] = "Інакше радимо звернутись до професіоналів";
			break;
		case 2:		// <- no paid
			err[0] = "Оплатіть інтернет, провайдер вас відключив";
			break;
		}
		break;
	}
}

void computer(void)
{
	short answer;
	// *********
	QstList launch{
		"Що робить компютер?",
		"1) Перезапускається",
		"2) Не Включається",
		"3) ОС не загружається"
	};
	answer = Ask(launch);
	switch (answer)
	{
	case 1:		// <- Restart
		// *********
		answer = Ask("Ви давно чистили систкмний блок?");
		switch (answer)
		{
		case 1:		// <- No clean
			err[0] = "Радимо почистити системник.";
			err[1] = "Через пил могли забитись вентелятори, щерез що системник перегрівався";
			err[2] = "Також могла висохти паста на процесорі.";
			err[3] = "Або могли пошкодитись інші деталі системника";
			status[0] = ErrStatus::SAFE;
			status[2] = ErrStatus::MEDIUM;
			status[3] = ErrStatus::DANGEROUS;
			break;
		case 2:		// <- Сlean
			err[0] = "Блоку живлення не вистачає потужності для працездатності даної конфігурації комп'ютера. Наприклад - блок живлення потужністю 350 ват, в системному блоці встановили потужну відеокарту.";
			err[1] = "Також операційна система може бути заражена вірусами.";
			err[2] = "Або є несправність системного блоку живлення.";
			status[0] = ErrStatus::MEDIUM;
			status[1] = ErrStatus::MEDIUM;
			status[2] = ErrStatus::DANGEROUS;
			break;
		}
		break;
	case 2:		// <- No Start
	{
		// *********
		QstList device{
			"Що саме не вмикається?",
			"1) Монітор",
			"2) Системник"
		};
		answer = Ask(device);
		switch (answer)
		{
		case 1:		// <- Monitor
			answer = Ask("Чи підключенний монітора джерела електроенергії та чи вімкнена кнопка живлення?");
			switch (answer)
			{
			case 1:		// <- Power
				// *********
				answer = Ask("Кабель передачі зображення підключений?");
				switch (answer)
				{
				case 1:		// <- Cnct cable
					err[0] = "Переіврте підключення кабеля, він міг відійти.";
					err[1] = "Кабель може бути зламаний і потребувати заміни.";
					err[2] = "Можуть бути проблеми з відеокартою.";
					err[3] = "Або інша суперечна ситуація.";
					status[1] = ErrStatus::SAFE;
					status[2] = ErrStatus::MEDIUM;
					status[3] = ErrStatus::DANGEROUS;
					break;
				case 2:		// <- No cnct cable
					err[0] = "Підключіть кабель живлення..";
					break;
				}
				break;
			case 2:		// <- No power
				err[0] = "Підключіть монітор до джерела живлення.";
				err[1] = "Переконайтесь чи кнопка живлення вімкнена!";
				break;
			}
			break;
		case 2:		// <- System block
			// *********
			answer = Ask("Системник підключенний до джерела електроенергії та чи вімкнена кнопка живлення?");
			switch (answer)
			{
			case 1:		// <- Power
				err[0] = "Переіврте підключення кабеля, він міг відійти.";
				err[1] = "Або у компютері сталася поломка якоїсь деталі.";
				status[1] = ErrStatus::DANGEROUS;
				break;
			case 2:		// <- No power
				err[0] = "Підключіть кабель живлення..";
				break;
			}
			break;
		}
		break;
	}
	case 3:		// <- OC
		err[0] = "Могли бути перепади напруги живлення";
		err[1] = "Компютер некоректнео вимкнули";
		err[2] = "Виходу з ладу жорсткого диска";
		err[3] = "Некоректно встановлені драйвера або програма";
		status[2] = ErrStatus::SAFE;
		status[3] = ErrStatus::MEDIUM;
		break;
	}
}
