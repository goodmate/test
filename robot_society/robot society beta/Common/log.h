//////////////////////////////////////////////////////
// Common files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://dart.kitech.re.kr
// Written by KwangWoong Yang<page365@gmail.com>
//
// 로그 메시지를 파일에 기록한다.

#pragma once 

typedef void (* log_fp)(const char *text);

// set_log_property() 함수는 로그 속성을 정의한다.
// [IN] const char *log_file_name : 로그를 기록할 파일 이름
// [IN] int max_file_size : 로그를 기록할 최대 파일 크기
// [IN] log_fp fp : 로그를 redirection할 함수 포인터
extern void set_log_property(const char *log_file_name, int max_file_size = 10000000, log_fp fp = 0);

// log() 함수의 사용법은 printf 함수와 동일하다.
extern void log(const char *format, ...);

/* Example
// 다음과 같이 사용한다.

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