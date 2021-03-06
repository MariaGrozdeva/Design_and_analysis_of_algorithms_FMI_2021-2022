# Алчни алгоритми (greedy algorithms)

Изчислителните задачи, които алчните алгоритми решават, са оптимизационни задачи. Например, задачата за намиране на минимално покриващо дърво е именно оптимизационна.  

При алчните алгоритми се прави поредица от **локално оптимални избори**, която води до **глобално оптимално решение**.  

При някои задачи (например МПД) локалната алчност е печеливша стратегия. Има обаче задачи, в които проявата на локална алчност води до решение, което не е оптимално. Всички NP-трудни задачи са такива.  

## Задачи

### Задача 1 (Activity Selection Problem):
Дадено е множество от мероприятия, всяко от които се характеризира с начален час и краен час. Съставете алгоритъм, който избира **възможно най-голям брой мероприятия, така че никои две от тях да не се застъпват** (допуска се краят на едното да съвпада с началото на следващото).

### Решение:
**Пример:** Нека мероприятията се провеждат в следните времеви интервали: **[0 ; 13]**, **[2 ; 5]**, **[4 ; 6]**, **[5 ; 9]**, **[8 ; 14]**, **[11 ; 12]**, **[15 ; 20]**.  

Алчната стратегия се състои в това да вземем първото възможно мероприятие (за да можем след него да вземем максимален брой). Трябва да уточним обаче в какъв ред разглеждаме мероприятията, т.е. най-напред трябва да извършим подходящо сортиране.  

Трябва да **сортираме мероприятията по техните краища** и после вече да прилагаме алчна стратегия (т.е. всеки път да добавяме към нашия списък първото мероприятие, което не се застъпва с никое от досега избраните). В конкретния пример резултатът е [2 ; 5], [5 ; 9], [11 ; 12], [15 ; 20], т.е. четири мероприятия, което е максималният възможен брой.  

**Коректност на алгоритъма:**  
Първо ще докажем, че най-рано завършващото мероприятие непременно е в поне едно от оптималните решения. Избираме произволно оптимално множество. Нека първото (по краен час) мероприятие в това множество не е първото от всички мероприятия. Тогава заменяме първото мероприятие на множеството с най-рано завършващото от всички мероприятия. След тази замяна крайният час на първото мероприятие на множеството ще стане по-ранен. Значи, това мероприятие ще продължава да не се застъпва с останалите мероприятия в множеството (които не се застъпват едно с друго). Следователно новото множество пак е оптимално, защото то съдържа същия (максималният) брой две по две незастъпващи се мероприятия. Обаче новото оптимално множество вече съдържа най-рано завършващото от всички мероприятия.  

Ето защо няма да сбъркаме, ако, конструирайки оптимално множество стъпка по стъпка, вземем най-рано завършващото мероприятие на първата стъпка от алгоритъма. Тогава всички други мероприятия, които ще вземем, или завършват преди неговото начало, или започват след неговия край (за да не се застъпват с него). Първият вариант е невъзможен: иначе най-рано завършващото мероприятие не би било такова. Остава другият вариант. Затова отсяваме оставащите мероприятия, като премахваме всички, започващи преди края на най-рано завършващото мероприятие. От останалите трябва да вземем колкото може повече, т.е. решаваме същата задача за останалите мероприятия. По същата логика няма да сбъркаме (т.е. ще стигнем до оптимално решение), ако пак вземем най-рано завършващото от останалите мероприятия и т.н.  

Този алчен алгоритъм изисква време **O(nlgn)** заради сортирането, където n е броят на мероприятията. (Вторият етап — построяването на максимално множество, след като масивът е сортиран — се изпълнява за линейно време.)

---

### Задача 2:
Даден е стринг с дължина 2n, състоящ се от символите '[' и ']'. Стринг е балансиран <=> може да бъде представен във вида s1[s2], където s1 и s2 са балансирани стрингове. Намерете минималния брой размени, с които можем да балансираме подаден стринг.

---

### Задача 3:
Дадени са банкноти с номинал 1, 7 и 10.  
Съставете алгоритъм, който намира най-малкия брой банкноти, с които може да се изплати сумата n точно (без ресто).

### Решение:
**Наблюдение 1:** Няма смисъл да използваме повече от две банкноти с номинал 7, защото три банкноти с номинал 7 могат да се заменят с две банкноти с номинал 10 и една банкнота с номинал 1 : 3\*7 = 21 = 2\*10 + 1\*1. Така едно оптимално решение (с три банкноти) се заменя с друго оптимално решение (със същия брой банкноти). Ограничавайки до 0, 1 или 2 броя на банкнотите с номинал 7, губим някои от оптималните решения, но не всички. Това е допустимо, понеже търсим едно оптимално решение, а не всички такива.  

**Наблюдение 2:** Можем да ограничим и броя на банкнотите с номинал 1. Броят им е не повече от шест (защото седем банкноти с номинал 1 могат да се заменят с една банкнота с номинал 7), и то само ако няма банкноти с номинал 7. А ако има, то броят на банкнотите с номинал 1 е максимум две (защото три банкноти с номинал 1 и една с номинал 7 могат да се заменят с една банкнота с номинал 10).  

Накратко: Ако cnt1 и cnt7 са съответно броят на банкнотите с номинал 1 и номинал 7, то за всяко n съществува оптимално решение измежду следните наредени двойки (cnt7; cnt1):  
**(0; 0), (0; 1), (0; 2), (0; 3), (0; 4), (0; 5), (0; 6); (1; 0), (1; 1), (1; 2); (2; 0), (2; 1), (2; 2)**.  

За да решим задачата, ще приложим **модификация** на следния алчен алгоритъм:
- Използваме колкото може повече банкноти с номинал 10.
- Като остане сума, по-малка от 10, използваме (ако може) една банкнота с номинал 7.
- Остатъка (ако има такъв) изплащаме с банкноти с номинал  1.

:bangbang: Директно приложен алчният алгоритъм не би работил коректно.  
***Пример:*** За n = 15 алчният алгоритъм намира представяне с шест банкноти (10+1+1+1+1+1 = 15) вместо с минималния брой три (7+7+1 = 15).  

Нека разгледаме следната таблица (само със сумите от 0 до 16 поради горните две наблюдения):

![alt_text](https://i.ibb.co/LgBb0Hj/nominals.png)

Не е трудно да се види, че от случаите, изброени в таблицата, алчният алгоритъм греши само при n = 14, 15 и 16. Понеже използва банкноти с номинал 10 докогато е възможно, той греши при всички стойности на n, завършващи на 4, 5 или 6 (и различни от 4, 5 и 6). В останалите случаи алчният алгоритъм работи коректно. Следователно алчният алгоритъм може да бъде поправен така: ако числото n завършва на някоя от цифрите 4, 5 и 6 (и е различно от 4, 5 и 6), то трябва да използваме една банкнота по-малко с номинал 10, а вместо нея си служим с две банкноти с номинал 7. Остатъка (ако има) изплащаме с банкноти с номинал 1.

![alt_text](https://i.ibb.co/jRBrRKW/nominals-Code.png)

1) Когато n завършва на 0, 1, 2 или 3, няма поправка: използваме колкото може повече банкноти с номинал 10. В тези случаи остатъкът е по-малък от 7, затова се изплаща с банкноти с номинал 1.  
***Примери:***  
- 253 = 250 + 3 = 25 × 10 + 3 × 1 — общо 28 банкноти.
- 461 = 460 + 1 = 46 × 10 + 1 × 1 — общо 47 банкноти.
---
2) Когато n завършва на 7, 8 или 9, пак няма поправка: използваме колкото може повече банкноти с номинал 10. Сега остатъкът е поне 7, затова освен банкнотите с номинал 1 има и една с номинал 7.  
***Примери:***  
- 519 = 510 + 9 = 51 × 10 + 1 × 7 + 2 × 1 — общо 54 банкноти.
- 367 = 360 + 7 = 36 × 10 + 1 × 7 — общо 37 банкноти.
---
3) Когато n завършва на 4, 5 или 6, има поправка: банкнотите с номинал 10 са с една по -малко. Вместо нея използваме две банкноти с номинал 7. Евентуалния остатък изплащаме с банкноти с номинал 1.  
***Примери:***  
- 106 = 90 + 16 = 9 × 10 + 2 × 7 + 2 × 1 — общо 13 банкноти.
- 875 = 860 + 15 = 86 × 10 + 2 × 7 + 1 × 1 — общо 89 банкноти.
