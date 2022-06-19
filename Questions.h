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
		"��� � ��� ����������?",
		"1) �������",
		"2) ��� �������"
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
		"���� ������� ����������?",
		"1) ���� ����������",
		"2) ϳ���������, ��� ��� ������� �� ���������"
	};
	answer = Ask(wifistaus);
	switch (answer)
	{
	case 1:		// <- No cnct
		switch (connect)
		{
		case ConnectTypeList::WIRED:
			err[0] = "�������� �� ���������� ������";
			err[1] = "����������� �������� ������";
			status[1] = ErrStatus::DANGEROUS;
			break;
		case ConnectTypeList::WIRELESS:
			err[0] = "�������� �� ��������� wifi �� �������";
			err[1] = "�������� �� ��� �������� � ��������";
			err[2] = "������ ���� ���� �� �������� ������������";
			status[2] = ErrStatus::MEDIUM;
			break;
		}
		break;
	case 2:		// <- Cnct no intrn
		// *********
		answer = Ask("�� �������� ��������?");
		switch (answer)
		{
		case 1:		// <- paid
			if (connect == ConnectTypeList::WIRELESS)
				err[0] = "������������� ������";
			err[1] = "������������� ����'����";
			err[2] = "�������� ���������� �����";
			err[3] = "������ ������ ���������� �� �����������";
			break;
		case 2:		// <- no paid
			err[0] = "������� ��������, ��������� ��� ��������";
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
		"�� ������ ��������?",
		"1) ���������������",
		"2) �� ����������",
		"3) �� �� �����������"
	};
	answer = Ask(launch);
	switch (answer)
	{
	case 1:		// <- Restart
		// *********
		answer = Ask("�� ����� ������� ��������� ����?");
		switch (answer)
		{
		case 1:		// <- No clean
			err[0] = "������ ��������� ���������.";
			err[1] = "����� ��� ����� �������� �����������, ����� �� ��������� �����������";
			err[2] = "����� ����� ������� ����� �� ��������.";
			err[3] = "��� ����� ����������� ���� ����� ����������";
			status[0] = ErrStatus::SAFE;
			status[2] = ErrStatus::MEDIUM;
			status[3] = ErrStatus::DANGEROUS;
			break;
		case 2:		// <- �lean
			err[0] = "����� �������� �� ������� ��������� ��� ������������� ���� ������������ ����'�����. ��������� - ���� �������� ��������� 350 ���, � ���������� ����� ���������� ������� ���������.";
			err[1] = "����� ���������� ������� ���� ���� �������� �������.";
			err[2] = "��� � ����������� ���������� ����� ��������.";
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
			"�� ���� �� ���������?",
			"1) ������",
			"2) ���������"
		};
		answer = Ask(device);
		switch (answer)
		{
		case 1:		// <- Monitor
			answer = Ask("�� ����������� ������� ������� �����������㳿 �� �� ������� ������ ��������?");
			switch (answer)
			{
			case 1:		// <- Power
				// *********
				answer = Ask("������ �������� ���������� ����������?");
				switch (answer)
				{
				case 1:		// <- Cnct cable
					err[0] = "�������� ���������� ������, �� �� �����.";
					err[1] = "������ ���� ���� �������� � ����������� �����.";
					err[2] = "������ ���� �������� � ����������.";
					err[3] = "��� ���� ��������� ��������.";
					status[1] = ErrStatus::SAFE;
					status[2] = ErrStatus::MEDIUM;
					status[3] = ErrStatus::DANGEROUS;
					break;
				case 2:		// <- No cnct cable
					err[0] = "ϳ�������� ������ ��������..";
					break;
				}
				break;
			case 2:		// <- No power
				err[0] = "ϳ�������� ������ �� ������� ��������.";
				err[1] = "������������� �� ������ �������� �������!";
				break;
			}
			break;
		case 2:		// <- System block
			// *********
			answer = Ask("��������� ����������� �� ������� �����������㳿 �� �� ������� ������ ��������?");
			switch (answer)
			{
			case 1:		// <- Power
				err[0] = "�������� ���������� ������, �� �� �����.";
				err[1] = "��� � �������� ������� ������� ����� �����.";
				status[1] = ErrStatus::DANGEROUS;
				break;
			case 2:		// <- No power
				err[0] = "ϳ�������� ������ ��������..";
				break;
			}
			break;
		}
		break;
	}
	case 3:		// <- OC
		err[0] = "����� ���� �������� ������� ��������";
		err[1] = "�������� ����������� ��������";
		err[2] = "������ � ���� ��������� �����";
		err[3] = "���������� ���������� �������� ��� ��������";
		status[2] = ErrStatus::SAFE;
		status[3] = ErrStatus::MEDIUM;
		break;
	}
}
