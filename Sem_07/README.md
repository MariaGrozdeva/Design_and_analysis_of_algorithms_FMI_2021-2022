## Сортиране в линейно време. Задачи, използващи идеята на CountingSort.

### Задача 1 (Първо липсващо число):
Даден е масив от n цели положителни числа, които могат да са много големи. Предложете алгоритъм, който **намира първото цяло положително число, липсващо в масива**.  

### Решение:
Очевидно отговорът е някое от числата 1, 2, 3, ..., n+1.  

Тривиалният алгоритъм проверява първо дали масивът съдържа 1, после 2 и т.н. до n. Всяка проверка изисква линейно време. В най-лошия случай (когато масивът съдържа всички числа от 1 до n) се правят n проверки. Следователно **времевата сложност на този алгоритъм е O(n^2 )**.  

Второ възможно решение е да сортираме масива за време O(nlgn), a после да търсим първото липсващо число за линейно време:

![alt_text](https://i.ibb.co/JqVrfKx/first-Missing-Number-Naive.png)

**Времевата сложност на този алгоритъм е O(nlgn) + O(n) = O(nlgn)**, което е по-добре от предишния алгоритъм, но все още не е най-бързо.  

Тъй като първото липсващо число е от 1 до n+1, можем да приложим **модификация на CountingSort**, работеща в линейно време. (Оригиналният вариант е неприложим, понеже числата в масива могат да са много големи).  
Това решение (Task01_not-in-place.cpp) очевидно работи **в линейно време O(n)** и ползва **допълнителна памет** (за масива C) **в размер O(n)**, при това без да променя оригиналния масив. Ако такава промяна е допустима, то можем да спестим паметта за масива C и да сведем допълнителната памет до константен брой променливи от примитивен тип (напр. броячи) - Task01_in-place.cpp.  

### Задача 2:
Даден е масив от n цели числа. Предложете алгоритъм, който **намира индексите на две числа от масива, чиято разлика се дели на 3n** (ако няма такива, да се отпечата подходящо съобщение).  Алгоритъмът да работи за **време O(n)**.  

### Решение:
Отново ще използваме идеята за броене на CountingSort. Ще броим не самите числа, а **остатъците им при деление на 3n**  
(защото разликата на две числа се дели на 3n <=> те дават равни остатъци при деление на 3n).  

Истинските бройки (колко точно пъти се среща всеки остатък) не ни интересуват. **За всеки остатък се интересуваме само дали се среща поне два пъти**. Ако да - при повторно срещане се интересуваме къде е било първото му срещане (първото и второто срещане са индексите, които търсим). Ето защо в помощния масив ще пазим не броячи, а позиции (индекси). Тъй като даден остатък може да не се среща изобщо, ще инициализираме помощния масив с невалидна стойност (например -1).  

## Въведение в динамичното програмиране.

**Динамичното програмиране** се използва в задачи, при които за всеки достатъчно голям вход, решението на задачата се свежда до решения върху подзадачи, които обаче **не са независими, а имат общи подподзадачи**.  
При тези задачи може да измислим алгоритъм, който не е рекурсивен, а **работи от долу нагоре** и съхранява решенията за общите подподзадачи, при което отпада преизчисляването на едни и същи решения отново и отново и отново. В това е същността на схемата Динамично Програмиране.  

### Задача 3:
Разполагаме с калкулатор, който може да изпълнява следните операции:

- Умножение на число X по 2
- Умножение на число X по 3
- Събиране на число X с 1-ца

Дадено е цяло положително число n. Предложете алгоритъм, **който пресмята най- малкия брой операции, които трябва да изпълним, за да получим числото n** (започваме прилагането на операциите от числото 1).  

**Пример:**  
*Вход: 962340  
Изход: 17*  

Обяснение към примера:  
1 -> 3 -> 9 -> 27 -> 54 -> 55 -> 165 -> 495 -> 1485 -> 4455 -> 8910 -> 17820 -> 17821 -> 53463 -> 160389 -> 160390 -> 481170 -> 962340  

### Решение:
**Рекурсивна декомпозиция:**  
minOperations(1) = 0  
minOperations(n) = 1 + min{ minOperations(n-1), minOperations(n/2), minOperations(n/3) }  

Имаме ли припокриване (общи подподзадачи, които преизчисляваме) ?  
Да.  
Следователно решаваме задачата по схемата Динамично програмиране.  

DP[0...n]:  
DP[i] - минималният брой операции, с които можем да получим числото i.  
DP[i] = 1 + min{ DP[n-1], DP[i/2] (ако i е четно), DP[i/3] (ако i се дели на 3) }
Резултатът ще се пази в DP[n].  