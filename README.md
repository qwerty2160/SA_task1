# Системный анализ, решение первой задачи. 
(Пример реализации алгоритма ПУРО)

<h1 class="code-line" data-line-start=1 data-line-end=2 ><a id="___1"></a>Пример входных данных:</h1>
<p class="has-line-data" data-line-start="2" data-line-end="9">Введите количество экспертов: 5<br>
Введите количество вариантов: 6<br>
Номер эксперта 1: 1<br>
Номер эксперта 2: 2<br>
Номер эксперта 3: 3<br>
Номер эксперта 4: 4<br>
Номер эксперта 5: 5</p>
<p class="has-line-data" data-line-start="10" data-line-end="11">Ввод исходной таблицы:</p>
<p class="has-line-data" data-line-start="12" data-line-end="19">E1 E2 E3 E4 E5<br>
V1:dhfbf<br>
V2:hdcab<br>
V3:fbbfc<br>
V4:bcaca<br>
V5:cahhd<br>
V6:afddh</p>
<h1 class="code-line" data-line-start=20 data-line-end=21 ><a id="___20"></a>Пример выходных данных:</h1>
<p class="has-line-data" data-line-start="21" data-line-end="22">Таблица 1. Участники экспертного опроса и ранжируемые объекты.</p>
<p class="has-line-data" data-line-start="23" data-line-end="30">E1   E2  E3  E4  E5<br>
V1a:    V4  V5  V6  V2  V6<br>
V2b:    V5  V4  V3  V1  V2<br>
V3c:    V6  V2  V2  V6  V3<br>
V4d:    V2  V3  V1  V3  V1<br>
V5h:    V3  V1  V5  V5  V4<br>
V6f:    V1  V6  V4  V4  V5</p>
<p class="has-line-data" data-line-start="31" data-line-end="32">Матрица упорядочения в канонической форме для эксперта E1.</p>
<p class="has-line-data" data-line-start="33" data-line-end="40">E1  V1  V2  V3  V4  V5  V6<br>
V1  0       -1  -1  -1  -1  -1<br>
V2  1       0       1       -1  -1  -1<br>
V3  1       -1  0       -1  -1  -1<br>
V4  1   1   1   0   1   1<br>
V5  1   1   1   -1  0   1<br>
V6  1   1   1   -1  -1  0</p>
<p class="has-line-data" data-line-start="41" data-line-end="42">Матрица упорядочения в канонической форме для эксперта E2.</p>
<p class="has-line-data" data-line-start="43" data-line-end="50">E2  V1  V2  V3  V4  V5  V6<br>
V1  0   -1  -1  -1  -1  1<br>
V2  1   0   1   -1  -1  1<br>
V3  1   -1  0   -1  -1  1<br>
V4  1   1   1   0   -1  1<br>
V5  1   1   1   1   0   1<br>
V6  -1  -1  -1  -1  -1  0</p>
<p class="has-line-data" data-line-start="51" data-line-end="52">Матрица упорядочения в канонической форме для эксперта E3.</p>
<p class="has-line-data" data-line-start="53" data-line-end="60">E3  V1  V2  V3  V4  V5  V6<br>
V1  0   -1  -1  1   1   -1<br>
V2  1   0   -1  1   1   -1<br>
V3  1   1   0   1   1   -1<br>
V4  -1  -1  -1  0   -1  -1<br>
V5  -1  -1  -1  1   0   -1<br>
V6  1   1   1   1   1   0</p>
<p class="has-line-data" data-line-start="61" data-line-end="62">Матрица упорядочения в канонической форме для эксперта E4.</p>
<p class="has-line-data" data-line-start="63" data-line-end="70">E4  V1  V2  V3  V4  V5  V6<br>
V1  0   -1  1   1   1   1<br>
V2  1   0   1   1   1   1<br>
V3  -1  -1  0   1   1   -1<br>
V4  -1  -1  -1  0   -1  -1<br>
V5  -1  -1  -1  1   0   -1<br>
V6  -1  -1  1   1   1   0</p>
<p class="has-line-data" data-line-start="71" data-line-end="72">Матрица упорядочения в канонической форме для эксперта E5.</p>
<p class="has-line-data" data-line-start="73" data-line-end="80">E5  V1  V2  V3  V4  V5  V6<br>
V1  0   -1  -1  1   1   -1<br>
V2  1   0   1   1   1   -1<br>
V3  1   -1  0   1   1   -1<br>
V4  -1  -1  -1  0   1   -1<br>
V5  -1  -1  -1  -1  0   -1<br>
V6  1   1   1   1   1   0</p>
<p class="has-line-data" data-line-start="81" data-line-end="82">Расстояния между ответами-ранжированиями экспертов E1-E5.</p>
<p class="has-line-data" data-line-start="83" data-line-end="90">Dij E1  E2  E3  E4  E5  ΣрК ΣкрК<br>
E1  0   8   20  24  16  68  1296<br>
E2  8   0   24  20  24  76  1616<br>
E3  20  24  0   8   4   56  1056<br>
E4  24  20  8   0   8   60  1104<br>
E5  16  24  4   8   0   52  912<br>
Σ   68  76  56  60  52  312</p>
<p class="has-line-data" data-line-start="91" data-line-end="92">Наиболее согласованное ранжирование - эксперт E5.</p>
<h1 class="code-line" data-line-start=93 data-line-end=94 ><a id="____93"></a>Второй пример входных данных:</h1>
<p class="has-line-data" data-line-start="94" data-line-end="99">Введите количество экспертов: 3<br>
Введите количество вариантов: 6<br>
Номер эксперта 1: 10<br>
Номер эксперта 2: 12<br>
Номер эксперта 3: 14</p>
<p class="has-line-data" data-line-start="100" data-line-end="101">Ввод исходной таблицы:</p>
<p class="has-line-data" data-line-start="102" data-line-end="109">E10 E12 E14<br>
V1:cda<br>
V2:bfc<br>
V3:ahh<br>
V4:haf<br>
V5:fcd<br>
V6:dbb</p>
<h1 class="code-line" data-line-start=109 data-line-end=110 ><a id="____109"></a>Второй пример выходных данных:</h1>
<p class="has-line-data" data-line-start="110" data-line-end="111">Таблица 1. Участники экспертного опроса и ранжируемые объекты.</p>
<p class="has-line-data" data-line-start="112" data-line-end="119">E10 E12 E14<br>
V1a:    V3  V4  V1<br>
V2b:    V2  V6  V3<br>
V3c:    V1  V5  V5<br>
V4d:    V5  V1  V6<br>
V5h:    V6  V3  V4<br>
V6f:    V4  V2  V2</p>
<p class="has-line-data" data-line-start="120" data-line-end="121">Матрица упорядочения в канонической форме для эксперта E10.</p>
<p class="has-line-data" data-line-start="122" data-line-end="129">E10 V1  V2  V3  V4  V5  V6<br>
V1  0   -1  -1  1   1   1<br>
V2  1   0   -1  1   1   1<br>
V3  1   1   0   1   1   1<br>
V4  -1  -1  -1  0   -1  -1<br>
V5  -1  -1  -1  1   0   1<br>
V6  -1  -1  -1  1  -1   0</p>
<p class="has-line-data" data-line-start="130" data-line-end="131">Матрица упорядочения в канонической форме для эксперта E12.</p>
<p class="has-line-data" data-line-start="132" data-line-end="139">E12 V1  V2  V3  V4  V5  V6<br>
V1  0   1   1   -1  -1  -1<br>
V2  -1  0   -1  -1  -1  -1<br>
V3  -1  1   0   -1  -1  -1<br>
V4  1   1   1   0   1   1<br>
V5  1   1   1   -1  0   -1<br>
V6  1   1   1   -1  1   0</p>
<p class="has-line-data" data-line-start="140" data-line-end="141">Матрица упорядочения в канонической форме для эксперта E14.</p>
<p class="has-line-data" data-line-start="142" data-line-end="149">E14 V1  V2  V3  V4  V5  V6<br>
V1  0   1   1   1   1   1<br>
V2  -1  0   -1  -1  -1  -1<br>
V3  -1  1   0   1   1   1<br>
V4  -1  1   -1  0   -1  -1<br>
V5  -1  1   -1  1   0   1<br>
V6  -1  1   -1  1   -1  0</p>
<p class="has-line-data" data-line-start="150" data-line-end="151">Расстояния между ответами-ранжированиями экспертов E10-E14.</p>
<p class="has-line-data" data-line-start="152" data-line-end="157">Dij E10 E12 E14 ΣрК ΣкрК<br>
E10 0   28  10  38  884<br>
E12 28  0   18  46  1108<br>
E14 10  18  0   28  424<br>
Σ   38  46  28  112</p>
<p class="has-line-data" data-line-start="158" data-line-end="159">Наиболее согласованное ранжирование - эксперт E14.</p>
