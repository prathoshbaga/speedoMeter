# speedoMeter
Repository which contains the code for a speedometer for displaying values at an output of 60fps.which consists of two parts:
1. Two Applications:
     1. [generator](https://github.com/prathoshbaga/speedoMeter/tree/main/generator): continuous periodic generation function depending on time - for example, the sum of sines with different periods and coefficients
     2. [speedometer](https://github.com/prathoshbaga/speedoMeter/tree/main/speedometer): receives data and displays speedometer.
  
2. Library [pipe](https://github.com/prathoshbaga/speedoMeter/tree/main/pipe) : The library provides functionality for asynchronous data exchange between Apps 1 and 2 based on an IPC ;
