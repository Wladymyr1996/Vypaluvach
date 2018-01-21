<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="uk_UA">
<context>
    <name>AboutWindow</name>
    <message>
        <location filename="aboutwindow.cpp" line="26"/>
        <source>About</source>
        <translation>Про додаток</translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="36"/>
        <source>Programm </source>
        <translation>Програма </translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="36"/>
        <source> can distributed free, and should be available to everyone.

Author - Stadnyk Volodymyr.
e-mail - Wladymyr1996@gmail.com
Version - </source>
        <translation> може розповсюджуватись вільно, та повинна бути доступна всім і вся.

Автор - Стадник Володимир.
e-mail - Wladymyr1996@gmail.com
Версія - </translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="41"/>
        <source>License - GNU General Public License v3.0

Thanks: Rick101
</source>
        <translation>Ліцензія - GNU General Public License v3.0

Щира подяка: Rick101
</translation>
    </message>
</context>
<context>
    <name>CNC</name>
    <message>
        <location filename="cnc.cpp" line="373"/>
        <location filename="cnc.cpp" line="384"/>
        <source>Information - Vypaluvach</source>
        <translation>Інформація - Vypaluvach</translation>
    </message>
    <message>
        <location filename="cnc.cpp" line="373"/>
        <source>Printing was succesfully end!</source>
        <translation>Випалювання було успішно завершено!</translation>
    </message>
    <message>
        <location filename="cnc.cpp" line="384"/>
        <source>Printing was stoped!</source>
        <translation>Випалювання було зупинено!</translation>
    </message>
    <message>
        <source>Printing succesfully end!</source>
        <translation type="vanished">Випалювання успішно завершено!</translation>
    </message>
    <message>
        <source>Stopped print!</source>
        <translation type="vanished">Випалювання зупинено!</translation>
    </message>
</context>
<context>
    <name>CNCsettingswindow</name>
    <message>
        <location filename="cncsettingswindow.cpp" line="34"/>
        <source>CNC settings</source>
        <translation>Налаштування ЧПК</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="46"/>
        <source>Scan ports</source>
        <translation>Сканувати порти</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="47"/>
        <source>Apply</source>
        <translation>Застосувати</translation>
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
        <translation>Допомога</translation>
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
        <translation>1. Налаштування програми -------------------
1.1. Максимальна кількість кроків вводиться для того, щоб повідомити користувача, коли зображення буде завеликим. 
1.2. Максимальна та мінімальна швидкості вводяться для виділення меж швидкостей. Чим менше число тим швидше жало рухається, оскільки швидкість вводиться в мілісекундах між кроками.
1.3. Пропорція вводиться експерементальним шляхом. Поставте одиницю, в меню головного вікна та запустіть тест пропорції й очікуйте завершення всіх дій. Повинно надрукувати квадрат зі сторонами 1000х1000 кроків. Після цього потрібно взяти лінійку й поміряти довжину двох прилеглих сторін. Тепер потрібно знайти таке число, на яке потрібно помножити соторону Y, щоб всі сторони були рівні.
1.4. Кількість пропущених рядкв залежить від товщини жала, визначити потрібно експерементальним шляхом, доки не доб&apos;єтеся бажаного результату.

2. Налаштування зʼєднання --------------------
2.1. Для налаштування зʼєднання, в меню відкриваємо &quot;Налаштування -&gt; Налаштування зʼєднання&quot;. Обираємо потрібний порт (зазвичай ttyUSB0), якщо потрібно скануємо порти ще раз (ЧПК повинен бути підʼєднаним до компʼютера). Й нажимаємо &quot;Застосувати&quot;.

3. Випалювання -------------------------------
3.1. Відкриваємо зобрження (Файл -&gt; Відкрити зображення), після чого очікуємо доки програма просканує зображення. Потім стрілочками обираємо початкове положення для друку. Виставляємо це положення як нульове (Керування -&gt; Встановити поточне положення як нуль). А для того, щоб запустити процес випалювання (Керування -&gt; Почати випалювання).
3.2. Випалювання йде автоматично. Кожного разу жало виходить на лінійку з чищалкою. Чищення йде в два етапа: на 300 кроків вліво від нуля (тому потрібно розраховувати на те що, нуль координатної площини повинен бути далі від краю). По мірі випалювання, червона лінія позначає той рядок, який на разі випалюється.
3.3. При непередбачуваній ситуації, коли випалювання було зупинено, його можна продовжити. Якщо червона лінія не вказує на те місце з якого ви б хотіли відновити випалювання, її можна встановити клацнувши мишею в потрібному місці відновлення, й виставити стрілками, якщо потрібно, жало в нуль по Х, а по Y в той рядок, де було перервано випалювання. Після цього потрібно натиснути &quot;Керування -&gt; Відновити друк&quot;.

4. Типи зображень ----------------------------
Програма &quot;Vypaluvach&quot; може відкривати більшість типів зображень. (альфа каналом буде знехтувано)</translation>
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
        <translation>&amp;Налаштування</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="54"/>
        <source>&amp;Control</source>
        <translation>&amp;ЧПК</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="63"/>
        <location filename="mainframe.ui" line="162"/>
        <source>&amp;Help</source>
        <translation>&amp;Допомога</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="67"/>
        <source>&amp;Language</source>
        <translation>&amp;Мова</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="94"/>
        <source>&amp;Open image</source>
        <translation>&amp;Відкрити зображення</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="99"/>
        <source>&amp;Close app</source>
        <translation>&amp;Закрити</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="108"/>
        <source>&amp;App settings</source>
        <translation>Налаштування &amp;додатку</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="117"/>
        <source>&amp;Serial settings</source>
        <translation>Налаштування &amp;порта</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="126"/>
        <source>&amp;Proportion test</source>
        <translation>&amp;Тест пропорції</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="135"/>
        <source>&amp;Set as zero</source>
        <translation>Встановити поточну позицію як &amp;нуль</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="144"/>
        <source>&amp;Begin burn</source>
        <translation>&amp;Почати випалювання</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="153"/>
        <source>&amp;Continue burn</source>
        <translation>&amp;Відновити випалювання</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="171"/>
        <source>&amp;About vypaluvach</source>
        <translation>&amp;Про випалювач</translation>
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
        <translation>Повернути &amp;голівку в нульове положення</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="49"/>
        <source>Disconnected</source>
        <translation>Від&apos;єднано!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="52"/>
        <source>Try connect!</source>
        <translation>Спробувати під&apos;єднатися!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="55"/>
        <source>Burn time: unkown</source>
        <translation>Час випалювання: невідомо</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="57"/>
        <location filename="mainframe.cpp" line="241"/>
        <source>Remaining time: uknown</source>
        <translation>Час до кінця: невідомо</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="59"/>
        <source>worked 0/0</source>
        <translation>Зроблено 0/0</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="61"/>
        <source>(0 %)</source>
        <translation>(0 %)</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="116"/>
        <source>Open Image</source>
        <translation>Відкрити зображення</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="118"/>
        <source>Image (*.jpg *.jpeg *.png *.bmp);; All files (*.*)</source>
        <translation>Зображення (*.jpg *.jpeg *.png *.bmp);; Всі файли (*.*)</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="126"/>
        <source>worked </source>
        <translation>Зроблено </translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="249"/>
        <source>Burn time: </source>
        <translation>Час випалювання: </translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="254"/>
        <source>Remaining time: </source>
        <translation>Час до кінця: </translation>
    </message>
</context>
<context>
    <name>MainWidget</name>
    <message>
        <location filename="mainwidget.cpp" line="33"/>
        <source>Error</source>
        <translation>Помилка!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="33"/>
        <source>You don&apos;t setting the app or wrong settings</source>
        <translation>Ви не налаштували програму або неправильні налаштування!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="48"/>
        <source>Warning</source>
        <translation>Увага!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="48"/>
        <source>Your Image is too large for your settings.</source>
        <translation>Ваше зображення завелике для Ваштх налаштувань!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="148"/>
        <source>No image</source>
        <translation>НЕМА ЗОБРАЖЕННЯ</translation>
    </message>
</context>
<context>
    <name>SettingsForm</name>
    <message>
        <location filename="settingswindow.cpp" line="34"/>
        <source>App settings</source>
        <translation>Налаштування додатку</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="51"/>
        <location filename="settingswindow.cpp" line="76"/>
        <source>Get HeadPos from CNC</source>
        <translation>Отримувати координати голівки ЧПК</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="54"/>
        <source>Like for map</source>
        <translation>Як для мапи</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="55"/>
        <source>Simple marker</source>
        <translation>Звичайний маркер</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="59"/>
        <source>Full step</source>
        <translation>Повнокроковий</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="60"/>
        <source>Half step</source>
        <translation>Напівкроковий</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="61"/>
        <source>Quarter step</source>
        <translation>Чвертькроковий</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="62"/>
        <source>Microstep</source>
        <translation>Мікрокроковий</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="65"/>
        <source>Cancel</source>
        <translation>Скасувати</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="66"/>
        <source>Apply</source>
        <translation>Застосувати</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="69"/>
        <source>Max Count steps per X:</source>
        <translation>Максимальна кількість кроків по X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="70"/>
        <source>Max Count steps per Y:</source>
        <translation>Максимальна кількість кроків по X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="71"/>
        <source>Min speed per X:</source>
        <translation>Мінімум мілісекунд на крок по X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="72"/>
        <source>Max speed per X:</source>
        <translation>Максимум мілісекунд на крок по X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="73"/>
        <source>Skipped Y steps on skipped lines:</source>
        <translation>Кількість пропущених кроків по Y на одну ЧПК лінію:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="74"/>
        <source>Skipped lines:</source>
        <translation>Пропущені лінії зображення на одну ЧПК лінію:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="75"/>
        <source>Time to wait heating:</source>
        <translation>Час до повного розігріву:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="77"/>
        <source>Marker:</source>
        <translation>Маркер:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="78"/>
        <source>Step mode:</source>
        <translation>Кроковий режим:</translation>
    </message>
</context>
<context>
    <name>StatusConnect</name>
    <message>
        <location filename="mainframe.cpp" line="292"/>
        <source>Connected</source>
        <translation>З&apos;єднано</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="293"/>
        <source>Disconnect!</source>
        <translation>Від&apos;єднати!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="298"/>
        <source>Disconnected</source>
        <translation>Роз&apos;єднано</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="299"/>
        <source>Try connect!</source>
        <translation>Спробувати під&apos;єднатися!</translation>
    </message>
</context>
</TS>
