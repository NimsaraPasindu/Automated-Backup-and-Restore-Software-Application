#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function to perform backup
int performBackup(const char* sourceFile, const char* backupFolder) {
    FILE* source1;
    FILE* backup1;
    char data;

    // Open the source file in binary read mode
    source1 = fopen(sourceFile, "rb");
    if (source1 == NULL) {
        printf("Failed to open the source file.\n");
        return -1;
    }

    // Create the backup file with a timestamp in the backup folder
    time_t current_Time;
    struct tm* timeInfo;
    char backupFileName[100];
    time(&current_Time);
    timeInfo = localtime(&current_Time);
    strftime(backupFileName, sizeof(backupFileName), "backup_%Y%m%d%H%M%S.txt", timeInfo);

    char backupPath[150];
    snprintf(backupPath, sizeof(backupPath), "%s/%s", backupFolder, backupFileName);

    backup1 = fopen(backupPath, "wb");
    if (backup1 == NULL) {
        printf("Failed to create the backup file.\n");
        fclose(source1);
        return -1;
    }

    // Read data from the source file and write it to the backup file
    while ((data = fgetc(source1)) != EOF) {
        fputc(data, backup1);
    }

    // Close the file pointers
    fclose(source1);
    fclose(backup1);

    printf("Backup successful! The backup file is saved as '%s'.\n", backupFileName);
    return 0;
}

// Function to perform restore
int performRestore(const char* backupFile, const char* destinationFolder) {
    FILE* backup1;
    FILE* destination1;
    char data;

    // Open the backup file in binary read mode
    backup1 = fopen(backupFile, "rb");
    if (backup1 == NULL) {
        printf("Failed to open the backup file.\n");
        return -1;
    }

    // Create the destination file in the destination folder
    char destinationFileName[100];
    snprintf(destinationFileName, sizeof(destinationFileName), "%s/restored_file.txt", destinationFolder);

    destination1 = fopen(destinationFileName, "wb");
    if (destination1 == NULL) {
        printf("Failed to create the destination file.\n");
        fclose(backup1);
        return -1;
    }

    // Read data from the backup file and write it to the destination file
    while ((data = fgetc(backup1)) != EOF) {
        fputc(data, destination1);
    }

    // Close the file pointers
    fclose(backup1);
    fclose(destination1);

    printf("Restore successful! The file is restored to '%s'.\n", destinationFileName);
    return 0;
}

int main() {
    const char* sourceFile = "source_file.txt";
    const char* backupFolder = "backup";
    const char* backupFile = "backup/backup_20230730102030.txt";
    const char* destinationFolder = "restored";

    // Perform backup
    if (performBackup(sourceFile, backupFolder) == -1) {
        printf("Backup failed.\n");
    }

    // Perform restore
    if (performRestore(backupFile, destinationFolder) == -1) {
        printf("Restore failed.\n");
    }

    return 0;
}

