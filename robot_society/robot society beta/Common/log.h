//////////////////////////////////////////////////////
// Common files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://dart.kitech.re.kr
// Written by KwangWoong Yang<page365@gmail.com>
//
// �α� �޽����� ���Ͽ� ����Ѵ�.

#pragma once 

typedef void (* log_fp)(const char *text);

// set_log_property() �Լ��� �α� �Ӽ��� �����Ѵ�.
// [IN] const char *log_file_name : �α׸� ����� ���� �̸�
// [IN] int max_file_size : �α׸� ����� �ִ� ���� ũ��
// [IN] log_fp fp : �α׸� redirection�� �Լ� ������
extern void set_log_property(const char *log_file_name, int max_file_size = 10000000, log_fp fp = 0);

// log() �Լ��� ������ printf �Լ��� �����ϴ�.
extern void log(const char *format, ...);

/* Example
// ������ ���� ����Ѵ�.

static void log_redirection(const char *text)
{
	puts (text);
}

void main ()
{
	set_log_property ("logfile.txt", 1000000, log_redirection);

	log ("INFO: EVER2 Motion V1");
}
*/