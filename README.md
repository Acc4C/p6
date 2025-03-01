## Сборка
Чтобы скомпилировать программы, нужно выполнить **make build** в корневой папке.
```command
make build
```

## Генерация данных
Программа **generator** генерирует **-c** пассажиров и охраняет разультат в бинарном файле **-f**:
```command
./generator -c <count> -f <filename> 
```
Значение **count** должно быть не менее 20. 
Пример:
```command
./generator -c 20 -f out.bin

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
| Wlrbbmqbhcd     | R. A.    | 264              | 927              | Kkyh            | 01.04.2029 14:50  | 2         | 3        |
| Rjmowfrxsjy     | L. B.    | 422              | 920              | Fsarcbynecdy    | 19.05.2026 09:45  | 4         | 2        |
| Rellnmpapqfw    | H. K.    | 251              | 88               | Mcoq            | 08.12.2029 07:12  | 0         | 1        |
| Hsqm            | B. G.    | 296              | 571              | Cljjiv          | 01.05.2026 13:20  | 6         | 1        |
| Xixmvtrrbljpt   | S. N.    | 498              | 354              | Zqfjmafadr      | 12.07.2028 04:35  | 0         | 4        |
| Nuvq            | F. H.    | 56               | 380              | Aqxwpqca        | 05.11.2027 08:03  | 1         | 2        |
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
| Kskfojne        | X. W.    | 1                | 326              | Nofwltwjw       | 26.12.2025 21:14  | 1         | 2        |
| Pxchvczysvdgcx  | B. B.    | 1                | 321              | Meaylzifktmo    | 03.05.2026 06:13  | 7         | 0        |
time: 0.014ms
```
