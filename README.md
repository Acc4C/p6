## Сборка
Чтобы скомпилировать программы, нужно выполнить **make build** в корневой папке.
```command
make build
```

## Создание таблицы с пассажирами
Программа **createtable** позволяет преобразовать текстовый файл **-i** в бинарный файл **-o**:
```command
./createtable -i <input> -o <output> 
```
 
Пример:
```command
./createtable -i ./inp.txt -o ./out.bin

```

## Вывод данных
Программа **printtable** считывает бинарный файл **-f** и выводит информацию о пассажирах в виде таблицы.
```command
./printtable -f <filename>
```
Пример:
```command
./printtable -f out.bin
```
```command
|     SURNAME     | INITIALS | NUMBER OF THINGS | WEIGHT OF THINGS |   DESTINATION   |   DEPARTURE TIME  | TRANSFERS | CHILDREN |
| Passenger1      | R. A.    | 264              | 927              | London          | 01.04.2029 14:50  | 2         | 3        |
| Passenger2      | L. B.    | 422              | 920              | Hollywood       | 19.05.2026 09:45  | 4         | 2        |
| Passenger3      | H. K.    | 251              | 88               | Moscow          | 08.12.2029 07:12  | 0         | 1        |
| Passenger4      | B. G.    | 296              | 571              | Singapore       | 01.05.2026 13:20  | 6         | 1        |
| Passenger5      | S. N.    | 498              | 354              | Washington      | 12.07.2028 04:35  | 0         | 4        |
| Passenger6      | F. H.    | 56               | 380              | Bangladesh      | 05.11.2027 08:03  | 1         | 2        |
. . .
```

## Обработка данных
Программа **main** считывает бинарный файл **-f** и ищет среди пассожиров двух таких, у которых багаж совпадает по числу вещей и различается по весу не более чем на **-p** кг.
```command
./main -f <filename> -p <parameter>
```
Пример:
```command
./main -f out.bin -p 5
```
```command
|     SURNAME     | INITIALS | NUMBER OF THINGS | WEIGHT OF THINGS |   DESTINATION   |   DEPARTURE TIME  | TRANSFERS | CHILDREN |
| Passenger15     | X. W.    | 1                | 326              | Tokyo           | 26.12.2025 21:14  | 1         | 2        |
| Passenger38     | B. B.    | 1                | 321              | Florida         | 03.05.2026 06:13  | 7         | 0        |
time: 0.014ms
```
