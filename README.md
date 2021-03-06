Proyecto 'breakout' de un R820T2 más un QSD para obtener salida IQ directamente a la tarjeta de sonido del PC. La idea es experimentar con el R820T2 y un QSD cuya frecuencia de refencia es 4X a la de demodulación, generada por un Si5351. 

El proyecto contiene:

- Carpeta KICAD: esquemas y PCB directos para generar gerbers.

- Carpeta r820t2: código Arduino para controla el R820T2 y Si5351.

+ Existe un modo consola de comandos serial para controlar los registros del R820T2 directamente y experiemntar.

+ Modo CAT para controlar la frecuencia de sintonía a través de OMNIRIG y el HDSDR por ejemplo.

Los principales aspectos del diseño son:

- El microcontrolador que usemos debe ser 3.3V. 
- El código inicia el R820T2 mediante protocolo I2C. El led, pin 13, y la salida por el puerto serie nos dan indicación del proceso de inicio.
- La parte LOOP consiste en una librería CAT para controlar la frecuencia de sintonía mediante el PC, como por ejemplo el OMNIRIG y el HDSDR.

El principio de hardware es:

- La salida del R820T2 se fija en 5 MHz. El tuner hace un proceso de mezcla de la entrada RF, y la frecuencia de sintonía aparecerá en su salida en esos 5 MHz.
- Se emplea la salida CLKOUT del R820T2, como entrada para un Si5351. Lo ideal es usar un cristal de 25 Mhz en el R820T2.
- Se programa la salida del Si5351 CLK2 a 20 Mhz, que será la entrada del demodulador QSD. Esto realmente es un 'exceso' pero la idea es experimentar con el Si5351 también. Bastaría con instalar un TCXO de 20Mhz al R820T2 para tener exactamente la frecuencia necesaria de demodulación en el QSD, esto es 5 Mhz. Este TCXO sería precisamente el U1. 
- La conversión tiene lugar justo en esos 20MHz/4, esto es, 5 Mhz, justo la salida del R820T2.
- La salida IQ es pues en banda base y directamente aplicable a la tarjeta de sonido del PC. Es recomendable ajustar la entrada a 192 Khz para poder demodular WFM correctamente.
- Con cualquier software que soporte la tarjeta de sonido como entrada, SDR#, o HDSDR, por ejemplo, nos permitirá ver el espectro y demodular la señal resultante.

Modelo 3D de la placa PCB mediante KICAD:

![pcb](pcb.PNG)

El proyecto está basado en fuentes como:

Driver del kernel linux del R820T2 ofrecido bajo licencia GPL.
Datasheet del R820T2.
Breakout y fuentes del proyecto del R820T2 de Eric Brombaugh https://github.com/emeb/r820t2/. Licencia MIT.

Esteban EA8DGL estebanjbs < at > gmail.com


Breakout project of an R820T2 plus a QSD to get IQ output directly to the PC sound card. The idea is to experiment with the R820T2 and a QSD whose reference frequency is 4X that of demodulation, generated by a Si5351.

The project contains:

- KICAD folder: diagrams and direct PCBs to generate gerbers.

- r820t2 folder: Arduino code to control the R820T2 and Si5351.

+ There is a serial command console mode to control the registers of the R820T2 directly and experiment.

+ CAT mode to control the tuning frequency through OMNIRIG and HDSDR for example.

The main aspects of the design are:

- The microcontroller that we use must be 3.3V.
- The code starts the R820T2 using the I2C protocol. The led, pin 13, and the output through the serial port give us an indication of the startup process.
- The LOOP part consists of a CAT library to control the tuning frequency through the PC, such as OMNIRIG and HDSDR.

The hardware principle is:

- The R820T2's output is fixed at 5 MHz. The tuner does a process of mixing the RF input, and the tuning frequency will appear at its output at those 5 MHz.
- The CLKOUT output of the R820T2 is used as input for a Si5351. Ideally, use a 25Mhz crystal on the R820T2.
- The output of Si5351 CLK2 is programmed at 20 Mhz, which will be the input of the QSD demodulator. This really is 'overkill' but the idea is to experiment with the Si5351 as well. It would be enough to install a 20Mhz TCXO to the R820T2 to have exactly the necessary demodulation frequency in the QSD, this is 5 Mhz. This TCXO would be precisely U1.
- The conversion takes place right at those 20MHz / 4, that is, 5Mhz, just the output of the R820T2.
- The IQ output is thus in baseband and directly applicable to the PC sound card. It is recommended to set the input to 192 Khz in order to demodulate WFM correctly.
- With any software that supports the sound card as input, SDR #, or HDSDR, for example, it will allow us to see the spectrum and demodulate the resulting signal.

3D model of the PCB board using KICAD:

! [pcb] (pcb.PNG)

The project is based on sources such as:

R820T2 Linux kernel driver offered under the GPL license.
Datasheet of the R820T2.
Breakout and sources for Eric Brombaugh's R820T2 project https://github.com/emeb/r820t2/. MIT license.

Esteban EA8DGL estebanjbs <at> gmail.com
