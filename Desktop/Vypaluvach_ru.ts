<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>AboutWindow</name>
    <message>
        <location filename="aboutwindow.cpp" line="26"/>
        <source>About</source>
        <translation>О приложении</translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="36"/>
        <source>Programm </source>
        <translation>Программа </translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="36"/>
        <source> can distributed free, and should be available to everyone.

Author - Stadnyk Volodymyr.
e-mail - Wladymyr1996@gmail.com
Version - </source>
        <translation> может распространяться свободно, и должна быть доступна всем.

Автор - Стадник Владимир.
e-mail - Wladymyr1996@gmail.com
Версия - </translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="41"/>
        <source>License - GNU General Public License v3.0

Thanks: Rick101
</source>
        <translation>Лицензия - GNU General Public License v3.0

Благодарность: Rick101
</translation>
    </message>
</context>
<context>
    <name>CNC</name>
    <message>
        <location filename="cnc.cpp" line="373"/>
        <location filename="cnc.cpp" line="384"/>
        <source>Information - Vypaluvach</source>
        <translation>Информация - Vypaluvach</translation>
    </message>
    <message>
        <location filename="cnc.cpp" line="373"/>
        <source>Printing was succesfully end!</source>
        <translation>Вижигание было успешно завершено!</translation>
    </message>
    <message>
        <location filename="cnc.cpp" line="384"/>
        <source>Printing was stoped!</source>
        <translation>Выжигание было остановлено!</translation>
    </message>
    <message>
        <source>Printing succesfully end!</source>
        <translation type="vanished">Выжигание успешно завершено!</translation>
    </message>
    <message>
        <source>Stopped print!</source>
        <translation type="vanished">Выжигание остановлено!</translation>
    </message>
</context>
<context>
    <name>CNCsettingswindow</name>
    <message>
        <location filename="cncsettingswindow.cpp" line="34"/>
        <source>CNC settings</source>
        <translation>Настройки ЧПУ</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="46"/>
        <source>Scan ports</source>
        <translation>Сканировать порты</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="47"/>
        <source>Apply</source>
        <translation>Применить</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="52"/>
        <source>Baudrate:</source>
        <translation>Baudrate:</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="53"/>
        <source>Port:</source>
        <translation>Порт:</translation>
    </message>
</context>
<context>
    <name>HelpWindow</name>
    <message>
        <location filename="helpwindow.cpp" line="25"/>
        <source>Help</source>
        <translation>Помощь</translation>
    </message>
    <message>
        <location filename="helpwindow.cpp" line="33"/>
        <source>1. Program Settings -------------------
1.1. The maximum number of steps can be entered in order to notify the user when the image is larger than allowed.
1.2. The maximum and minimum speeds are entered to determine the speed limits. The smaller the number, the faster the sting moves, because the speed is measured in milliseconds between the steps.
1.3. Proportion is determined by the experimental method. Put &quot;1&quot; in the main window menu and run the test proportion and wait for the completion of all actions. Must print a square with sides of 1000x1000 steps. After need to take a ruler and measure the length of the two adjacent sides. Now we need to find a number that must be multiplied by Y so that all sides are equal.
1.4. The number of skipped rows depends on the thickness of the sting, you need to determine it experimentally until you get the desired result.

2. Configure the connection ---------------------
2.1. To configure the connection, in the menu, open &quot;Settings -&gt; Connection settings&quot;. Select the desired port (by default ttyUSB0), if necessary, scan the ports again (the CNC must be connected to the computer). And click &quot;Apply&quot;.

3. Burning -------------------------------
3.1. Open the image (File -&gt; Open image), then wait until the program scans the image. Then use the arrows to select the initial position for burning. We set this position as zero (Control -&gt; Set the current position as zero). And in order to start the burning process (Control -&gt; Start Burning).
3.2. Burning goes automatically. Each time, the sting goes to the ruler with a cleaver. Purification goes in two stages: 300 steps to the left of zero (since you need to calculate that the zero of the coordinate plane should be farther from the edge). As the burnout progresses, the red line marks the row that is currently being burned.
3.3. In case of an unforeseen situation, when the burning was left, it can be continued. If the red line does not indicate the place from which you would like to continue burning, you can set it by clicking the mouse in the desired place of renewal, and set the arrows, if necessary, sting at zero on X, and on Y in the row where the burning was interrupted . After that, click &quot;Management -&gt; Resume burning&quot;

4. Image Types -------------------------
The program &quot;Vypaluvach&quot; can read more image types like *.bmp, *jpg, *png without information about the alpha channel. (Alpha chanel be ignored)</source>
        <translation>1. Настройки программы -------------------
1.1. Максимальное количество шагов вводиться для того, что-бы уведомлять пользователя, когда изображение будет больше, чем разрешено. 
1.2. Максимальная и минимальная скоростя вводяться для определения границ скоростей. Чем меньше число, тем быстрее двигаеться жало, поскольку скорость измеряеться в милисекундах между шагами.
1.3. Пропорция определяеться эксперементальным путем. Поставьте единицу, в меню главного окна и запустите тест пропорции и ожидайте завершения всех действий. Должно напечатать квадрат со сторонами 1000х1000 шагов. После чеого нужно взять линейку и померять длинну двех прилежащих сторон. Теперь нужно найти такое число, на которое нкжно умножить соторону Y, чтобы все стороны были равны.
1.4. Количесвто пропущеных рядов зависит от толщины жала, нужно определить эксперементальным путем, пока не добъётесь желаемого результата.

2. Настройка соединения --------------------
2.1. Для настройки соединения, в меню открываем &quot;Настройки -&gt;; Настройки соединения&quot;. Выбираем нужный порт (по-умолчанию ttyUSB0), если нужно, сканируем порты еще раз (ЧПУ должен быть подключен к компъютеру). И нажимаем &quot;Применить&quot;.
3. Выжигание -------------------------------
3.1. Открываем изображение (Файл -&gt; Открыть изображение), после чего ждем пока программа просканирует изображение. Потом стрелочками выбираем начальное положение для выжигания. Вычставляем это положение как нулевое (Управление -&gt;; Установить текущее положение как ноль). А для того, чтобы запустить процесс выжигания (Управление -&gt; Начать выжигание).
3.2. Выжигание идет автоматически. Каждый раз жало выходит на линейку с чищалкой. Очищение идет в два этапа: на 300 шагов влево от нуля (так как нужно расчитать на то, чтоо ноль координатной плоскости должен быть дальше от края). По мере выжыгания, красная линия отмечает тот ряд, который на данный момент выжигается.
3.3. При непредвиденной ситуации, когда выжигание было остаовлено, его можна продолжить. Если красная линия не указывает на то место с которого Вы хотели бы продолжить выжигание, её можна установить клликнув мышкой в нужном месте возобновления, и выставить стрелочками, если потребуеться, жало в ноль по Х, а по Y в тот ряд, где было прервано выжигание. После этого нужно нажать &quot;Управление -&gt;; Возобновить выжигание&quot;

4. Типы изображений-------------------------
Программа &quot;Vypaluvach&quot; может читать большинство типов изображения.(альфаканал будет проигнорирован)</translation>
    </message>
</context>
<context>
    <name>MainFrame</name>
    <message>
        <location filename="mainframe.ui" line="23"/>
        <source>MainFrame</source>
        <translation></translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="37"/>
        <source>&amp;File</source>
        <translation>&amp;Файл</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="45"/>
        <source>&amp;Settings</source>
        <translation>&amp;Настроойки</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="54"/>
        <source>&amp;Control</source>
        <translation>&amp;ЧПУ</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="63"/>
        <location filename="mainframe.ui" line="162"/>
        <source>&amp;Help</source>
        <translation>&amp;Помощь</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="67"/>
        <source>&amp;Language</source>
        <translation>&amp;Язык</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="94"/>
        <source>&amp;Open image</source>
        <translation>&amp;Открыть изображение</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="99"/>
        <source>&amp;Close app</source>
        <translation>&amp;Закрыть</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="108"/>
        <source>&amp;App settings</source>
        <translation>Настройки &amp;приложения</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="117"/>
        <source>&amp;Serial settings</source>
        <translation>Настройки &amp;порта</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="126"/>
        <source>&amp;Proportion test</source>
        <translation>&amp;Тест пропорции</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="135"/>
        <source>&amp;Set as zero</source>
        <translation>&amp;Установить текущую позицию как ноль</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="144"/>
        <source>&amp;Begin burn</source>
        <translation>&amp;Начать выжигание</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="153"/>
        <source>&amp;Continue burn</source>
        <translation>&amp;Возобновить выжигание</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="171"/>
        <source>&amp;About vypaluvach</source>
        <translation>&amp;О vypaluvach</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="180"/>
        <source>&amp;English</source>
        <translation>&amp;English</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="189"/>
        <source>&amp;Ukrainian</source>
        <translation>&amp;Уркаїнська</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="198"/>
        <source>&amp;Russian</source>
        <translation>&amp;Русский</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="207"/>
        <source>&amp;Return to zero</source>
        <translation>Вернуть &amp;головку в нулевое положение</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="49"/>
        <source>Disconnected</source>
        <translation>Отключен!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="52"/>
        <source>Try connect!</source>
        <translation>Попоробовать подключиться!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="55"/>
        <source>Burn time: unkown</source>
        <translation>Время выжигания: неизвестно</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="57"/>
        <location filename="mainframe.cpp" line="241"/>
        <source>Remaining time: uknown</source>
        <translation>Оставшееся время: неизвестно</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="59"/>
        <source>worked 0/0</source>
        <translation>Зделано 0/0</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="61"/>
        <source>(0 %)</source>
        <translation>(0 %)</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="116"/>
        <source>Open Image</source>
        <translation>Открыть изображение</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="118"/>
        <source>Image (*.jpg *.jpeg *.png *.bmp);; All files (*.*)</source>
        <translation>Изображение (*.jpg *.jpeg *.png *.bmp);; Все файлы (*.*)</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="126"/>
        <source>worked </source>
        <translation>Зделано </translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="249"/>
        <source>Burn time: </source>
        <translation>Время выжигания: </translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="254"/>
        <source>Remaining time: </source>
        <translation>Оставшееся время: </translation>
    </message>
</context>
<context>
    <name>MainWidget</name>
    <message>
        <location filename="mainwidget.cpp" line="33"/>
        <source>Error</source>
        <translation>Ошибка!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="33"/>
        <source>You don&apos;t setting the app or wrong settings</source>
        <translation>Вы не настроили программу или неверные настройки!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="48"/>
        <source>Warning</source>
        <translation>Внимание!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="48"/>
        <source>Your Image is too large for your settings.</source>
        <translation>Ваше изображение слишком большое для Ваших настроек!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="148"/>
        <source>No image</source>
        <translation>НЕТ ИЗОБРАЖЕНИЯ</translation>
    </message>
</context>
<context>
    <name>SettingsForm</name>
    <message>
        <location filename="settingswindow.cpp" line="34"/>
        <source>App settings</source>
        <translation>Настройки приложения</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="51"/>
        <location filename="settingswindow.cpp" line="76"/>
        <source>Get HeadPos from CNC</source>
        <translation>Получать координаты головки ЧПУ</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="54"/>
        <source>Like for map</source>
        <translation>Как для карт</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="55"/>
        <source>Simple marker</source>
        <translation>Простой маркер</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="59"/>
        <source>Full step</source>
        <translation>Полношаговый</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="60"/>
        <source>Half step</source>
        <translation>Полушаговый</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="61"/>
        <source>Quarter step</source>
        <translation>Четвертичный</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="62"/>
        <source>Microstep</source>
        <translation>Микрошаговый</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="65"/>
        <source>Cancel</source>
        <translation>Отменить</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="66"/>
        <source>Apply</source>
        <translation>Применить</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="69"/>
        <source>Max Count steps per X:</source>
        <translation>Максимальное количество шагов по X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="70"/>
        <source>Max Count steps per Y:</source>
        <translation>Максимальное число шагов по X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="71"/>
        <source>Min speed per X:</source>
        <translation>Минимум милисекунд на шаг по X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="72"/>
        <source>Max speed per X:</source>
        <translation>Максимум милисекунд на шаг по X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="73"/>
        <source>Skipped Y steps on skipped lines:</source>
        <translation>Количество пропущеных шагов по Y на одну ЧПУ линию:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="74"/>
        <source>Skipped lines:</source>
        <translation>Пропущенные линии изображения на одну ЧПУ линию:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="75"/>
        <source>Time to wait heating:</source>
        <translation>Время до нагрева:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="77"/>
        <source>Marker:</source>
        <translation>Маркер:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="78"/>
        <source>Step mode:</source>
        <translation>Шаговый режим:</translation>
    </message>
</context>
<context>
    <name>StatusConnect</name>
    <message>
        <location filename="mainframe.cpp" line="292"/>
        <source>Connected</source>
        <translation>Соеденено</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="293"/>
        <source>Disconnect!</source>
        <translation>Разъеденить!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="298"/>
        <source>Disconnected</source>
        <translation>Разъеденено</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="299"/>
        <source>Try connect!</source>
        <translation>Попробовать подключиться!</translation>
    </message>
</context>
</TS>
