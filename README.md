# plc_pp
PLC++

Данный репозиторий для систем АСУ ТП на ПЛК [ICP-DAS LP-8x21](https://ipc2u.com/news/product-news/new-products-in-linux-based-controllers/), [MOXA UC-2112](https://moxa.ru/shop/comp/risc/uc2100/uc-2112-t-lx/) и других на базе Debian

## Сборка для arm-linux-gnueabihf:
```
cd plc_pp\
arm-linux-gnueabihf-g++ -g -li8k -lmodbus -lmosquitto -lmysqlclient -lpthread -lz -lm -lrt -ldl -g -std=c++11 -c *.cpp 
arm-linux-gnueabihf-ar rcs ..\libPigment.a -o *.o
```

## Использование:

Использование библиотеки показано в файла **main.cpp**
