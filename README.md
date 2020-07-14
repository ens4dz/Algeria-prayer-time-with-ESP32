
# 1-create 3MB empty image with:
python mk_espfatPython3.py
Enter partition size (in hex or decimal) :
3080192

# 2-add db to filesystem.img:
in windows add your files to image with any Fat12 editor (OSFMount,WinImage ..)

# 3- flash that file (filesystem.img) to esp32:
go to esptool.py path, with cmd run esptools.
example:
```
cd "F:\arduino-1.8.12\portable\packages\esp32\hardware\esp32\1.0.4\tools"
python esptool.py --chip esp32 -p com3 -b 921600 write_flash 0x111000 "F:\arduino-1.8.12\portable\sketchbook\sqlite3_FAT-salat\mk_espfat-master\filesystem.img"
```


# esp32 boot log:
```
Total space:    3026944
Free space:     258048
Listing directory: /
  FILE: /Djelfa.db	SIZE: 2766848
Opened database successfully
SELECT _id,MADINA_ID,GeoDate,Fajr,Shurooq, Kibla, Dhuhr, Asr, Maghrib,Isha FROM itc_tab_mawakit_salat WHERE MADINA_ID = 1 AND GeoDate = '2019-07-19'
Callback function called: _id = 81405
MADINA_ID = 1
GeoDate = 2019-07-19
Fajr = 04:07:00
Shurooq = 05:48:00
Kibla = 10:23:00
Dhuhr = 12:54:00
Asr = 16:40:00
Maghrib = 20:02:00
Isha = 21:34:00

Operation done successfully
Time taken:1172770
SELECT _id,ParentId,MADINA_NAME FROM itc_tab_madina WHERE _id = 1
Callback function called: _id = 1
ParentId = NULL
MADINA_NAME = الجلفة

Operation done successfully
Time taken:8898
```
