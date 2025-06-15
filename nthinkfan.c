//  nthinkfan - Control ThinkPads fan speed with dialog on Linux
//  Copyright (C) 2025 Connor Thomson
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *FANFILE = "/proc/acpi/ibm/fan";

int main() {
    char cmd[1024];
    char choice[32];

    while (1) {
        snprintf(cmd, sizeof(cmd),
            "dialog --backtitle \"nthinkfan v1.0\" "
            "--title \"Set Fan Speed\" "
            "--ok-label \"Set\" --cancel-label \"Exit\" "
            "--menu \"\" 20 55 10 "
            "0 \"0 RPM\" "
            "1 \"3280 RPM\" "
            "2 \"3680 RPM\" "
            "3 \"3880 RPM\" "
            "4 \"4080 RPM\" "
            "5 \"4680 RPM\" "
            "6 \"5080 RPM\" "
            "7 \"5080 RPM\" "
            "disengaged \"6830 RPM\" "
            "auto \"Automatic\" "
            "2> /tmp/nthinkfan.tmp");

        int ret = system(cmd);
        system("clear");

        if (ret != 0) break;

        FILE *fp = fopen("choice.tmp", "r");
        if (!fp) break;
        fgets(choice, sizeof(choice), fp);
        fclose(fp);
        remove("choice.tmp");

        choice[strcspn(choice, "\n")] = 0;

        if (strlen(choice) > 0) {
            char apply[256];
            snprintf(apply, sizeof(apply), "echo level %s | sudo tee %s > /dev/null", choice, FANFILE);
            system(apply);        
        }
    }
    return 0;
}
