# 1_C_problem
## Решение задачи 1С для поступления на кафедру

## Задача
Пасьянс.

Две колоды карт (по 36 штук) соединяются и перемешиваются, а после раскладываются в 8 кучек по 9 карт. 

Можно работать только с верхними картами в каждой из кучек, а именно перекладывать одну или несколько последовательных карт меньшего номинала на карту большего (масти не учитываются). 
Если в одной из кучек оказалось 9 карт в правильном порядке (Напомню, туз-король-дама-валет-10-9-8-7-6), то этот набор убирается. 
Если из одной кучки убрали все карты, её всё ещё можно использовать и класть наверх любую карту. 
Необходимо реализовать программу, которая по информации об исходном состоянии восьми кучек посчитает, можно ли будет убрать все карты.
Формат ввода карт определите самостоятельно

## Реализация 

* Создаем класс Playing_card, где храним значения карты в enum, так как по условию масть неважна, и bool открыта ли карта
* Создаем класс Pack - стопку карт, в котором храним кол-во открытых карт, послледнюю открытую и дек карт
* Перегружаем соответствующие операторы в обоих классах: арифметические, ввод/вывод и т.д.

В классе Pack следующие методы: 
* GetOpenCards - возвращает stack открытык карт
* ShiftOpenCards - перемещение открытых карт с отдной стопки на другую 
* LastOpen/FirstOpen

## Идея

Решение осуществляется перебором с оптимизациями.

Алгоритм:
* Сортируем наши колоды по возрастанию открытой карты с помощью std::sort
* Проверяем количество открытых колод(пустых, так как убираем их), в конце, если их количество == начальному, то мы выиграли
* Проверяет, если на какой-то итерации ничего не произошло (переменная no_actions), то возвращаем false
* В отсортированной колоде, если у рядом стоящего номинал на 1 больше, то перекладываем карты ShiftOpenCards

### Уточнение
В алгоритме предполагаем, что, как в обычной игре "косынка" после того, как мы положили карту на карту - это считается уже фиксированной комбинацией и ее разъединять мы не можем

## Тесты
Не было уверенности, что можно использовать фреймоврки для тестирования, поэтому простой тест написан вручную.

```
7 9 10 12 12 13 14 9 11
7 10 12 8 9 6 13 13 9
14 12 7 10 11 8 11 6 8
10 11 6 7 12 11 13 8 14
14 8 13 6 10 11 9 9 8
11 7 14 6 12 7 6 13 12
7 6 9 8 10 13 14 11 10
8 7 14 9 10 12 13 6 14
```
В выводе:
```
Loose
14 12 7 10 11 8 11 6 8op 
11 7 14 6 12 7 6 13 12op 11op 10op 9op 8op 
14 8 13 6 10 11 9 9op 
7 9 10 12 12 13 14 9op 
7 6 9 8 10 13 14 11op 
7 10 12 8 9 6 13op 
10 11 6 7 12 11 13 8 14op 13op 
8 7 14 9 10 12 13 6 14op 
```
Что соответствует действительности.

