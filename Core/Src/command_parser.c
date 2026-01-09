#include "command_parser.h"
#include <string.h>

uint8_t command_flag = 0;

void command_parser_init(void) {
    command_flag = 0; // Clear command flag
}

void command_parser_fsm(uint8_t* buffer) {
    const char CMD_RST[] = "!RST#";
    const char CMD_OK[] = "!OK#";

//    if (strncmp((char *)buffer, CMD_RST, strlen(CMD_RST)) == 0) {
//        // Xử lý lệnh !RST#
//        command_flag = 1;       // Set RTS command flag
//    } else if (strncmp((char *)buffer, CMD_OK, strlen(CMD_OK)) == 0) {
//        // Xử lý lệnh !OK#
//        command_flag = 0;       // Clear RTS command
//    }

    if (strcmp((char *)buffer, CMD_RST) == 0) {
            // Xử lý lệnh !RST#
            command_flag = 1;
    } else if (strcmp((char *)buffer, CMD_OK) == 0) {
            // Xử lý lệnh !OK#
            command_flag = 0;
    }
}
