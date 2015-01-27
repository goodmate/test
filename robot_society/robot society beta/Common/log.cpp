//////////////////////////////////////////////////////
// Common files for Robot applications
// 
// Copyright (c) 2002-2008. All Rights Reserved.
// Division of Applied Robot Technology KITECH
// Web: http://dart.kitech.re.kr
// Written by KwangWoong Yang<page365@gmail.com>
//
 
#define _CRT_SECURE_NO_DEPRECATE

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include "log.h"

static int max_file_size = 10000000;
static char log_file_name[256+1] = "";
static log_fp external_log_fp = NULL;

void _limit_file_size(char *file)
{
	struct stat buf[1];

	if(0 <= stat(file,buf)){					// 파일의 상태를 읽어옴
		if(buf->st_size > max_file_size){		// 파일이 제한값을 넘어갈 때
			char file_name_old[256];

			strcpy(file_name_old, file);
			strcat(file_name_old, ".old");			// .old 파일이름 생성
			
			remove(file_name_old);					// .old 파일이 존재하면 삭제
			rename(file,file_name_old);				// .old 파일로 복사
		}
	}
}

static int _get_current_time(char *text, int len)
{
	struct _timeb timebuffer;
	struct tm tt;

	_ftime( &timebuffer );
	tt = *localtime(&timebuffer.time);

	return _snprintf (text, len, "%02d:%02d:%02d.%03d ", 
		(int)tt.tm_hour, (int)tt.tm_min, (int)tt.tm_sec, (int)timebuffer.millitm);
}

void set_log_property(const char *_log_file_name, int _max_file_size, log_fp _fp)
{
	if (!_log_file_name) _log_file_name = "";
	strncpy(log_file_name, _log_file_name, 256);
	log_file_name[256] = '\0';
	max_file_size = _max_file_size;
	external_log_fp = _fp;

	if (log_file_name[0]) {
		_limit_file_size(log_file_name);
	}
}

void log(const char *format, ...)
{
	int n = 0;
    va_list arg_list;
	char log_text[1024+1];

	if (log_file_name[0]) {
		_limit_file_size(log_file_name);
	}

	n += _get_current_time(log_text+n, 1024-n);
	va_start (arg_list,format);
	n += _vsnprintf (log_text+n, 1024-n, format, arg_list);
	va_end (arg_list);
	n += _snprintf (log_text+n, 1024-n, "\r\n");
	log_text[1024] = '\0';

	if (external_log_fp) {
		(*external_log_fp) (log_text);
	}

	if (log_file_name[0]) {
		FILE *fp = fopen (log_file_name, "ab");
		if(fp){
			fputs (log_text, fp);
			fclose(fp);
		}
	}
}

