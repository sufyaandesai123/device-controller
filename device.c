/*
 * device.c - a tiny simulated device controller.
 *
 * It reads one command per line, then turns bits on or off in a fake
 * hardware register, the same way firmware controls real hardware.
 *
 * Commands: LED ON, LED OFF, FAN ON, FAN OFF, STATUS, RESET
 */
#include <stdio.h>
#include <string.h>

#define LED_BIT (1 << 0)   /* bit 0 of the register controls the LED */
#define FAN_BIT (1 << 1)   /* bit 1 of the register controls the fan */

unsigned char reg = 0;     /* the simulated control register, all off */

void handle(const char *cmd) {
    if (strcmp(cmd, "LED ON") == 0) {
        reg |= LED_BIT;                 /* set bit 0 */
        printf("OK\n");
    } else if (strcmp(cmd, "LED OFF") == 0) {
        reg &= ~LED_BIT;                /* clear bit 0 */
        printf("OK\n");
    } else if (strcmp(cmd, "FAN ON") == 0) {
        reg |= FAN_BIT;                 /* set bit 1 */
        printf("OK\n");
    } else if (strcmp(cmd, "FAN OFF") == 0) {
        reg &= ~FAN_BIT;                /* clear bit 1 */
        printf("OK\n");
    } else if (strcmp(cmd, "STATUS") == 0) {
        if (reg & LED_BIT) {
            printf("LED=ON ");
        } else {
            printf("LED=OFF ");
        }

        if (reg & FAN_BIT) {
            printf("FAN=ON ");
        } else {
            printf("FAN=OFF ");
        }

        printf("REG=0x%02X\n", reg);
    } else if (strcmp(cmd, "RESET") == 0) {
        reg = 0;
        printf("OK\n");
    } else {
        printf("ERROR unknown command\n");
    }
}

int main(void) {
    char line[64];

    while (fgets(line, sizeof line, stdin) != NULL) {
        line[strcspn(line, "\r\n")] = '\0';   /* remove the newline */
        handle(line);
    }
    return 0;
}