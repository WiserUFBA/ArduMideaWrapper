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

We use two libraries to ArduMideaWrapper project,the traditional IR library and a especific library called MideaIR. Both needs an object be created:

IRsend irsend;<br />
MideaIR remote_control(&irsend);


Then, you can use the functions to control your air conditioner.

The functions turnON and turnOFF don't need parameters and can be used like this:

remote_control.turnON();<br />
remote_control.turnOFF();

There are functions to set Mode, Temperature and Speed Fan:

The function to set temperature receive as paramenter an int with the required temperature:

remote_control.setTemperature(18);<br />
remote_control.emit();

The function to set mode receive as paramenter a string with the required mode:

remote_control.setMode(mode_cool);<br />
remote_control.emit();

There are four modes: mode_cool, mode_heat, mode_no_humidity, mode_auto.

The function to set speed fan receive as paramenter a string with the required speed:

remote_control.setSpeedFan(fan_speed_3);<br />
remote_control.emit();


There are five fan configurations: fan_off, fan_speed_1, fan_speed_2, fan_speed_3, fan_auto.

These functions needs another function to work, the emit function, which will send the signal to air conditioner.
You can set how many operations you want and then use this function to make all alterations once.Example:

remote_control.setTemperature(25);<br />
remote_control.setMode(mode_auto);<br />
remote_control.setSpeedFan(fan_speed_3);<br />
remote_control.emit();

The library offers also a way to get information from air conditioner:

To get mode: remote_control.getMode()<br />
To get speed fan: remote_control.getSpeedFan()<br />
To get temperature:  remote_control.getTemperature()


You can download the IR library here: https://github.com/z3t0/Arduino-IRremote


--
<p align="center">
	Developed by </br>
  <img alt="Wiser Research Group Logo" src="https://wiki.dcc.ufba.br/pub/SmartUFBA/ProjectLogo/wiserufbalogo.jpg"/> 
</p>
