SimulationsSavior
=================

A simple and stupid code to save C++ simulations data to PostgreSQL.

Motivation
=========

To make simulations is more appropriated to use C/C++, since these languages
have a better performance, and simulations have the bad habit to get really complex,
and slow, very fast. 
However, to analyse the simulation results, C/C++ are not convenient, since these
languages are not agile, in the sense of development. So, it is a better idea to
save the simulation and use another language/program to analyse the results.
It may not be a good idea to save simulations on files, since it is
impossible, or very complicated at least, to keep track of the different parameters 
of many different samples, because of this, it seems a much better idea to save the 
simulations on a database.
