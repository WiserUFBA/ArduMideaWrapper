# MideaIR

[![Build Status](https://travis-ci.org/WiserUFBA/ArduMideaWrapper.svg)](https://travis-ci.org/WiserUFBA/ArduMideaWrapper)
[![License Badge](https://img.shields.io/github/license/wiserufba/ardumideawrapper.svg)](https://github.com/WiserUFBA/ArduMideaWrapper/blob/master/LICENSE)
[![Issues Badge](https://img.shields.io/github/issues/wiserufba/ardumideawrapper.svg)](https://github.com/WiserUFBA/ArduMideaWrapper/issues)
[![Join the chat at https://gitter.im/WiserUFBA/ArduMideaWrapper](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/WiserUFBA/ArduMideaWrapper?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/WiserUFBA/ardumideawrapper/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

### Introduction

The remote control of Midea Air Conditioner have an UI point of view, the values of the commands on the remote control like Temperature, and Speed Fan are all synchronized with the Air Conditioner when you change some of them, this implies in the following problem: you can't emit only one command! You need to emit all the states on the remote control, even if you only just wanna change the temperature, the only independent command on this remote control is the command to turn off, all the others including the turn on need to be concatenated.

In order to solve this problem, this library provides an object that simulate the interface present on the remote control, making the process of control the Midea Air Conditioner more easier.

### How to Use?

To use this library you need to include the traditional IR library and pass the reference of the object irsend in the constructor of the MideaIR class.

```cpp
IRsend irsend;
MideaIR remote_control(&irsend);
```

Then, you can use the functions to control your air conditioner.

You can use the functions to turnON and turnOFF without the need of call `emit()`.:

```cpp
// To turn the Air Conditioner ON
remote_control.turnON();
// and the following to turn the Air Conditioner OFF
remote_control.turnOFF();
```

`emit()` Is a function used to emit the IR Signal to the Air Conditioner, if you make a change on the mode or temperature, use `emit()` to send the signal, if you don't use emit() the air conditioner won't be changed.
There are functions to set Mode, Temperature and Speed Fan:

The function to set temperature (`setTemperature()`) receive as paramenter an int with the required temperature, the range accepted is between 17 and 30, if you use more than 30, the class will change this to 30 and if you use less then 17 the class will change this to 17:

```cpp
remote_control.setTemperature(18);
remote_control.emit();
```
The function to set mode (`setMode()`) receive a constant as a parameter, if you don't use a correct constant the class with the required mode will change this to the default that is `mode_auto`:

```cpp
remote_control.setMode(mode_cool);
remote_control.emit();
```

There are four modes, represented as the following constants: `mode_cool`, `mode_heat`, `mode_no_humidity`, `mode_auto`.

The function to set speed fan (`setSpeedFan()`) receive a constant as a paramenter, like the `setMode()` function, if you don't use a correct constant the class will use the default `fan_auto` instead:

```cpp
remote_control.setSpeedFan(fan_speed_3);
remote_control.emit();
```

There are five fan configurations, represented as the following constants: `fan_off`, `fan_speed_1`, `fan_speed_2`, `fan_speed_3`, `fan_auto`.

Like we have said above, set functions just change local variables, if you want to send these to the air conditioner you need to call `emit()`. You can set as many operations as you can, before send the signal, and all of them will be synchronized once.

Example:

```cpp
remote_control.setTemperature(25);
remote_control.setMode(mode_auto);
remote_control.setSpeedFan(fan_speed_3);
remote_control.emit();
```

You can use the following function to retrieve information from the class:

```cpp
// Get Mode
remote_control.getMode();
// Get Speed Fan
remote_control.getSpeedFan();
// Get Temperature
remote_control.getTemperature();
// Get State ~ ON or OFF ~ true or false
remote_control.getState();
```

You can download the IR library here: [Arduino-IRremote](https://github.com/z3t0/Arduino-IRremote)

**P.S.:** Don't forget to use `setState(true)` before you emit commands like `setTemperature()`or `setMode()`, if you don't set the state to true the air conditioner won't turn on, or change the value. The default value to state is `false`.

### Schematic 

To improve Infrared Signal we recommend make a amplifier, you can use a simple resistor:

<p align="center">
  <img alt="InfraRed Booster1" width="600"src="https://wiki.dcc.ufba.br/pub/SmartUFBA/ProjectLogo/IRBooster1png.png"/>
</p>

Or, you can use a circuit with capacitor and a transistor NPN:

<p align="center">
  <img alt="InfraRed Booster" width="600" src="https://wiki.dcc.ufba.br/pub/SmartUFBA/ProjectLogo/IRB.png"/> 
</p>

**P.S.:** To better range use a super bright LED

### Credits

Thanks a lot Daniel Veillard (http://veillard.com) **[@veillard](https://github.com/veillard)** to point how to send the IR signals of Midea AC in the post ([http://veillard.com/embedded/midea.html](http://veillard.com/embedded/midea.html)), they help us a lot in the construction of this library, and thanks to **[Tom Blough](http://thebloughs.net/design-a-custom-ac-timer/)** for help me (**[@jefersonla](https://github.com/jefersonla)**) and **[@veillard](https://github.com/veillard)** in the proccess of make reverse enginering. Thanks for the contributors of [https://github.com/z3t0/Arduino-IRremote](https://github.com/z3t0/Arduino-IRremote) too.

Developers **Jeferson Lima** (**[@jefersonla](https://github.com/jefersonla)**) and **Andressa Andrade** (**[@AndressAndrade](https://github.com/AndressAndrade)**)

--
<p align="center">
	Developed by </br>
  <img alt="Wiser Research Group Logo" src="https://wiki.dcc.ufba.br/pub/SmartUFBA/ProjectLogo/wiserufbalogo.jpg"/> 
</p>
