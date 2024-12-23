#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void boot_linux() {
    printf("Booting Linux...\n");
    system("grub-reboot 0");
    system("reboot");
}

void boot_windows() {
    printf("Booting Windows...\n");
    system("bcdedit /set {default} bootmenupolicy legacy");
    system("reboot");
}

void boot_macos() {
    printf("Booting MacOS...\n");
    system("bless --mount /Volumes/Macintosh\\ HD --setBoot");
    system("reboot");
}

void boot_android() {
    printf("Booting Android...\n");
    system("reboot");
}

void display_os_options() {
  //
}

void boot_os(int choice) {
    switch (choice) {
        case 1:
            boot_linux();
            break;
        case 2:
            boot_windows();
            break;
        case 3:
            boot_macos();
            break;
        case 4:
            boot_android();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

int main() {
    int choice;

    display_os_options();

    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    boot_os(choice);

    return 0;
}
