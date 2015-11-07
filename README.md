# MideaIR

[![Build Status](https://travis-ci.org/WiserUFBA/ArduMideaWrapper.svg)](https://travis-ci.org/WiserUFBA/ArduMideaWrapper)

### Introduction

The remote control of Midea Air Conditioner have an UI point of view, the values of the commands on the remote control like Temperature, and Speed Fan are all synchronized with the Air Conditioner when you change some of them, this implies in the following problem: you can't emit only one command! You need to emit all the states on the remote control, even if you only just wanna change the temperature, the only independent command on this remote control is the command to turn off, all the others including the turn on need to be concatenated.

In order to solve this problem, this library provides an object that simulate the interface present on the remote control, making the process of control the Midea Air Conditioner more easier.

### How to Use?

// Your turn Andressa ;)


--
<p align="center">
	Developed by </br>
  <img src="https://wiki.dcc.ufba.br/pub/SmartUFBA/ProjectLogo/wiserufbalogo.jpg"/>
</p>
