#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/io/stat.h>
#include <psp2/sysmodule.h>
#include "sqlite3.h"
#include "graphics.h"

#define printf psvDebugScreenPrintf

#define DEBUG 0

#if DEBUG
#define LOG psvDebugScreenPrintf
#else
#define LOG(...)
#endif

#define APP_DB "ur0:shell/db/app.db"

static unsigned buttons[] = {
	SCE_CTRL_SELECT,
	SCE_CTRL_START,
	SCE_CTRL_UP,
	SCE_CTRL_RIGHT,
	SCE_CTRL_DOWN,
	SCE_CTRL_LEFT,
	SCE_CTRL_LTRIGGER,
	SCE_CTRL_RTRIGGER,
	SCE_CTRL_TRIANGLE,
	SCE_CTRL_CIRCLE,
	SCE_CTRL_CROSS,
	SCE_CTRL_SQUARE,
};

int get_key(void) {
	static unsigned prev = 0;
	SceCtrlData pad;
	while (1) {
		memset(&pad, 0, sizeof(pad));
		sceCtrlPeekBufferPositive(0, &pad, 1);
		unsigned new = prev ^ (pad.buttons & prev);
		prev = pad.buttons;
		for (int i = 0; i < sizeof(buttons)/sizeof(*buttons); ++i)
			if (new & buttons[i])
				return buttons[i];

		sceKernelDelayThread(1000); // 1ms
	}
}


void sql_simple_exec(sqlite3 *db, const char *sql) {
	char *error = NULL;
	int ret = 0;
	ret = sqlite3_exec(db, sql, NULL, NULL, &error);
	if (error) {
		printf("Failed to execute %s: %s\n", sql, error);
		sqlite3_free(error);
		goto fail;
	}
	return;
fail:
	sqlite3_close(db);
}

void patch() {
	int ret;
	char sql[0x1000];
	char *error = NULL;

	sqlite3 *db;
	ret = sqlite3_open(APP_DB, &db);
	if (ret) {
		printf("Failed to open the database: %s\n", sqlite3_errmsg(db));
		goto fail;
	}

	sql_simple_exec(db, "BEGIN TRANSACTION;");
    sql_simple_exec(db, "UPDATE tbl_appinfo_icon SET titleid=REPLACE(titleid,'PKGE00001','NPXS10031');");
    sql_simple_exec(db, "COMMIT TRANSACTION;");
    sql_simple_exec(db, "BEGIN TRANSACTION;");
    sql_simple_exec(db, "UPDATE tbl_appinfo_icon SET title=REPLACE(title,'Enable Package Installer','★Package Installer');");
    sql_simple_exec(db, "COMMIT TRANSACTION;");
	sqlite3_close(db);
	db = NULL;

	return;

fail:
	if (db)
		sqlite3_close(db);
	psvDebugScreenSetFgColor(COLOR_RED);
	printf("FAILURE! Reboot your PSTV/PSV into recovery mode and select 'rebuild database'\n");
	
}

int main(void) {
	int key = 0;
    patch();
    scePowerRequestColdReset();
}
