<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="en_US">
<context>
    <name>AboutWindow</name>
    <message>
        <location filename="aboutwindow.cpp" line="26"/>
        <source>About</source>
        <translation>About</translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="36"/>
        <source>Programm </source>
        <translation>Programm </translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="36"/>
        <source> can distributed free, and should be available to everyone.

Author - Stadnyk Volodymyr.
e-mail - Wladymyr1996@gmail.com
Version - </source>
        <translation> can distributed free, and should be available to everyone.

Author - Stadnyk Volodymyr.
e-mail - Wladymyr1996@gmail.com
Version - </translation>
    </message>
    <message>
        <location filename="aboutwindow.cpp" line="41"/>
        <source>License - GNU General Public License v3.0

Thanks: Rick101
</source>
        <translation>License - GNU General Public License v3.0

Thanks: Rick101
</translation>
    </message>
</context>
<context>
    <name>CNC</name>
    <message>
        <location filename="cnc.cpp" line="373"/>
        <location filename="cnc.cpp" line="384"/>
        <source>Information - Vypaluvach</source>
        <translation>Information - Vypaluvach</translation>
    </message>
    <message>
        <location filename="cnc.cpp" line="373"/>
        <source>Printing was succesfully end!</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="cnc.cpp" line="384"/>
        <source>Printing was stoped!</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <source>Printing succesfully end!</source>
        <translation type="vanished">Burning succesfully end!</translation>
    </message>
    <message>
        <source>Stopped print!</source>
        <translation type="vanished">Stopped burn!</translation>
    </message>
</context>
<context>
    <name>CNCsettingswindow</name>
    <message>
        <location filename="cncsettingswindow.cpp" line="34"/>
        <source>CNC settings</source>
        <translation>CNC Settings</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="46"/>
        <source>Scan ports</source>
        <translation>Scan ports</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="47"/>
        <source>Apply</source>
        <translation>Apply</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="52"/>
        <source>Baudrate:</source>
        <translation>Baudrate:</translation>
    </message>
    <message>
        <location filename="cncsettingswindow.cpp" line="53"/>
        <source>Port:</source>
        <translation>Port:</translation>
    </message>
</context>
<context>
    <name>HelpWindow</name>
    <message>
        <location filename="helpwindow.cpp" line="25"/>
        <source>Help</source>
        <translation>Help</translation>
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
        <translation>1. Program Settings -------------------
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
The program &quot;Vypaluvach&quot; can read more image types like *.bmp, *jpg, *png without information about the alpha channel. (Alpha chanel be ignored)</translation>
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
        <translation>&amp;File</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="45"/>
        <source>&amp;Settings</source>
        <translation>&amp;Settings</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="54"/>
        <source>&amp;Control</source>
        <translation>&amp;CNC</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="63"/>
        <location filename="mainframe.ui" line="162"/>
        <source>&amp;Help</source>
        <translation>&amp;Help</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="67"/>
        <source>&amp;Language</source>
        <translation>&amp;Language</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="94"/>
        <source>&amp;Open image</source>
        <translation>&amp;Open image</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="99"/>
        <source>&amp;Close app</source>
        <translation>&amp;Close app</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="108"/>
        <source>&amp;App settings</source>
        <translation>&amp;App settings</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="117"/>
        <source>&amp;Serial settings</source>
        <translation>&amp;Serial settings</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="126"/>
        <source>&amp;Proportion test</source>
        <translation>&amp;Proportion test</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="135"/>
        <source>&amp;Set as zero</source>
        <translation>&amp;Set current postion as zero</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="144"/>
        <source>&amp;Begin burn</source>
        <translation>&amp;Begin burn</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="153"/>
        <source>&amp;Continue burn</source>
        <translation>&amp;Continue burn</translation>
    </message>
    <message>
        <location filename="mainframe.ui" line="171"/>
        <source>&amp;About vypaluvach</source>
        <translation>&amp;About vypaluvach</translation>
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
        <translation>&amp;Return head to zero</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="49"/>
        <source>Disconnected</source>
        <translation>Disconnected!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="52"/>
        <source>Try connect!</source>
        <translation>Try connect!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="55"/>
        <source>Burn time: unkown</source>
        <translation>Burn time: unkown</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="57"/>
        <location filename="mainframe.cpp" line="241"/>
        <source>Remaining time: uknown</source>
        <translation>Remaining time: uknown</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="59"/>
        <source>worked 0/0</source>
        <translation>Worked 0/0</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="61"/>
        <source>(0 %)</source>
        <translation>(0 %)</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="116"/>
        <source>Open Image</source>
        <translation>Open image</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="118"/>
        <source>Image (*.jpg *.jpeg *.png *.bmp);; All files (*.*)</source>
        <translation>Image (*.jpg *.jpeg *.png *.bmp);; All files (*.*)</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="126"/>
        <source>worked </source>
        <translation>Worked </translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="249"/>
        <source>Burn time: </source>
        <translation>Burn time: </translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="254"/>
        <source>Remaining time: </source>
        <translation>Remaining time: </translation>
    </message>
</context>
<context>
    <name>MainWidget</name>
    <message>
        <location filename="mainwidget.cpp" line="33"/>
        <source>Error</source>
        <translation>Error!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="33"/>
        <source>You don&apos;t setting the app or wrong settings</source>
        <translation>You don&apos;t setting the app or wrong settings!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="48"/>
        <source>Warning</source>
        <translation>Warning!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="48"/>
        <source>Your Image is too large for your settings.</source>
        <translation>Your Image is too large for your settings!</translation>
    </message>
    <message>
        <location filename="mainwidget.cpp" line="148"/>
        <source>No image</source>
        <translation>NO IMAGE</translation>
    </message>
</context>
<context>
    <name>SettingsForm</name>
    <message>
        <location filename="settingswindow.cpp" line="34"/>
        <source>App settings</source>
        <translation>App settings</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="51"/>
        <location filename="settingswindow.cpp" line="76"/>
        <source>Get HeadPos from CNC</source>
        <translation>Geting head coordinates from CNC</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="54"/>
        <source>Like for map</source>
        <translation>Like for map</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="55"/>
        <source>Simple marker</source>
        <translation>Simple marker</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="59"/>
        <source>Full step</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="60"/>
        <source>Half step</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="61"/>
        <source>Quarter step</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="62"/>
        <source>Microstep</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="65"/>
        <source>Cancel</source>
        <translation>Cancel</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="66"/>
        <source>Apply</source>
        <translation>Apply</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="69"/>
        <source>Max Count steps per X:</source>
        <translation>Max number steps per X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="70"/>
        <source>Max Count steps per Y:</source>
        <translation>Max number steps per Y:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="71"/>
        <source>Min speed per X:</source>
        <translation>Minimal miliseconds per step for X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="72"/>
        <source>Max speed per X:</source>
        <translation>Maximal miliseconds per step on X:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="73"/>
        <source>Skipped Y steps on skipped lines:</source>
        <translation>Number skipped steps per Y on one CNC line:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="74"/>
        <source>Skipped lines:</source>
        <translation>Skipped lines of image per one CNC line:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="75"/>
        <source>Time to wait heating:</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="77"/>
        <source>Marker:</source>
        <translation>Marker:</translation>
    </message>
    <message>
        <location filename="settingswindow.cpp" line="78"/>
        <source>Step mode:</source>
        <translation type="unfinished"></translation>
    </message>
</context>
<context>
    <name>StatusConnect</name>
    <message>
        <location filename="mainframe.cpp" line="292"/>
        <source>Connected</source>
        <translation>Connected</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="293"/>
        <source>Disconnect!</source>
        <translation>Disconnect!</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="298"/>
        <source>Disconnected</source>
        <translation>Disconnected</translation>
    </message>
    <message>
        <location filename="mainframe.cpp" line="299"/>
        <source>Try connect!</source>
        <translation>Try connect!</translation>
    </message>
</context>
</TS>
