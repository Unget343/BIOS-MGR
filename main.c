#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/utsname.h>
#include <sys/statvfs.h>
#endif

const char *get_current_os() {
    static char current_os[100];

#ifdef _WIN32
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (GetVersionEx(&osvi)) {
        snprintf(current_os, sizeof(current_os), "Windows %ld.%ld",
                 osvi.dwMajorVersion, osvi.dwMinorVersion);
    } else {
        strncpy(current_os, "Windows (Unknown Version)", sizeof(current_os));
    }
#else
    struct utsname buffer;
    if (uname(&buffer) == 0) {
        snprintf(current_os, sizeof(current_os), "%s %s", buffer.sysname, buffer.release);
    } else {
        strncpy(current_os, "Unknown OS", sizeof(current_os));
    }
#endif

    return current_os;
}

unsigned long long get_os_size(const char *path) {
    struct statvfs stat;

    if (statvfs(path, &stat) != 0) {
        return 0;
    }

    unsigned long long size = stat.f_frsize * stat.f_blocks;
    return size;
}

int get_installed_os(char installed_os[][100], int max_os) {
    const char *current_os = get_current_os();
    strncpy(installed_os[0], current_os, 100);
    return 1;
}

const char *get_os_status(const char *os_name) {
    const char *current_os = get_current_os();
    if (strcmp(os_name, current_os) == 0) {
        return "Active";
    } else {
        return "Inactive";
    }
}

unsigned long long get_os_weight(const char *os_name) {
    const char *path = "/";
    return get_os_size(path);
}

void launch_os(const char *os_name) {
    printf("Launching OS: %s\n", os_name);
}

int main() {
    char installed_os[10][100];
    int os_count = get_installed_os(installed_os, 10);

    printf("Current OS: %s\n", get_current_os());

    for (int i = 0; i < os_count; i++) {
        const char *os_name = installed_os[i];
        const char *status = get_os_status(os_name);
        unsigned long long weight = get_os_weight(os_name);

        double weight_in_gb = weight / (1024.0 * 1024 * 1024);
        printf("OS: %s, Status: %s, Size: %.2f GB\n", os_name, status, weight_in_gb);
    }

    launch_os(installed_os[0]);
    return 0;
}
