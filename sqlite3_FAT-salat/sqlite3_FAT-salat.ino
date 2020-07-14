/*
    This reades SQLITE3 database from the FFat file:
*/
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <FS.h>
#include "FFat.h"
// This file should be compiled with 'Partition Scheme' (in Tools menu)
// set to 'NO OTA (1MB APP/3MB FATFS)' 

// You only need to format FFat the first time you run a test
#define FORMAT_FFAT false

const char* data = "Callback function called";
static int callback(void *data, int argc, char **argv, char **azColName) {
   int i;
   Serial.printf("%s: ", (const char*)data);
   for (i = 0; i<argc; i++){
       Serial.printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   Serial.printf("\n");
   return 0;
}

int db_open(const char *filename, sqlite3 **db) {
   int rc = sqlite3_open(filename, db);
   if (rc) {
       Serial.printf("Can't open database: %s\n", sqlite3_errmsg(*db));
       return rc;
   } else {
       Serial.printf("Opened database successfully\n");
   }
   return rc;
}

char *zErrMsg = 0;
int db_exec(sqlite3 *db, const char *sql) {
   Serial.println(sql);
   long start = micros();
   int rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if (rc != SQLITE_OK) {
       Serial.printf("SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
   } else {
       Serial.printf("Operation done successfully\n");
   }
   Serial.print(F("Time taken:"));
   Serial.println(micros()-start);
   return rc;
}

void setup() {

   Serial.begin(115200);
   Serial.setDebugOutput(true);
   sqlite3 *db1;
   int rc;
   
    if (FORMAT_FFAT) FFat.format();
    if(!FFat.begin()){
        Serial.println("FFat Mount Failed");
        return;
    }

   // list FFat contents
   File root = FFat.open("/");
    Serial.printf("Total space: %10u\n", FFat.totalBytes());
    Serial.printf("Free space: %10u\n", FFat.freeBytes());
    
   if (!root) {
       Serial.println("- failed to open directory");
       return;
   }
   if (!root.isDirectory()) {
       Serial.println(" - not a directory");
       return;
   }
   File file = root.openNextFile();
   while (file) {
       if (file.isDirectory()) {
           Serial.print("  DIR : ");
           Serial.println(file.name());
       } else {
           Serial.print("  FILE: ");
           Serial.print(file.name());
           Serial.print("\tSIZE: ");
           Serial.println(file.size());
       }
       file = root.openNextFile();
   }



   sqlite3_initialize();

   if (db_open("/ffat/Djelfa.db", &db1))
       return;
       
   rc = db_exec(db1, "SELECT _id,MADINA_ID,GeoDate,Fajr,Shurooq, Kibla, Dhuhr, Asr, Maghrib,Isha FROM itc_tab_mawakit_salat WHERE MADINA_ID = 1 AND GeoDate = '2019-07-19'");
   if (rc != SQLITE_OK) {
       sqlite3_close(db1);
       return;
   }

   rc = db_exec(db1, "SELECT _id,ParentId,MADINA_NAME FROM itc_tab_madina WHERE _id = 1");  //1 is Djelfa ID
   if (rc != SQLITE_OK) {
       sqlite3_close(db1);
       return;
   }

   sqlite3_close(db1);

}

void loop() {
}
