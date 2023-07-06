# WindTurbineSimulation
The main objective is to develop wind farm simulator considering the wind turbine system constraints such as operating speed range and design features in terms of electrical machines. This leads that each turbine has its own constraints and working conditions depending on the wind speed. Considering these limitations and conditions, the simulator task is to estimate the total power generation, income and efficiency of single turbine as well as whole wind farm groups. Finally, giving the wind speed in time series, simulator must output report that includes everything mentioned above in detail. 

This project involves designing and implementing software which simulates the output of a
wind farm or a group of wind farms based on wind speed data for different sites. The following paragraph will remind the user requirements and discuss whether all points are met.

•	The program should be able to read from the csv file or set of csv files and obtain the wind speed information for hourly time series.
•	The functionality that allow user to split the data file by choosing a period time for initial implementations due to the large data set. 
•	The program should able to allow user to set parameters of wind turbine for every group of wind farm such as rated power, type of electrical machine, rotor swept area, blade pitch, cut-in speed, optimum speed and cut-off speed of the wind turbine.
•	The functionality that can fix the data that consist of some missing data. The missing data appears in term of “-99999” or “-99999.0”. The program should complete the data and add variance range for speed that is defined by user.
•	The functionality that calculates the power of every wind farm based on the wind speed and different turbine, considering the speed operation range of certain wind turbine.
