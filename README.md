# ROT TIMEPROFILLER

This is a simple tool to generate a JSON file with timing information about the function calls that you want. 

## --------- USING IT ---------

To use it, just instanciate a <code>rot::EventLogger</code> passing a string to a JSON file (if not exist, it will be created) at the start of the region you want to mesure performance. You can stop it by calling the <code>EndSession()</code> function on the instance or it will stop automaticly once out of scope. Inside the region, instantiate <code>rot::Timer</code> with two strings: A name and a category, and a referente to the instance of the EventLogger so it will know were to log the timer results. The timer stops when out of scope.

**TIP** you can use <code>\_\_func\_\_</code> to automaticly pass the function name as a string to the <code>rot::Timer</code> constructor;

To vizualise the data you collected, just go to a chromium-based browser (Chrome or the new Edge) and go to the tracing page (chrome://tracing or edge://tracing) and drago-drop the JSON file. It will generate the tree of funcion calls and a easy-to-visualize timeline of your scope.


## --------- USING MACROS ---------

Instanciating all those objects can add a lot of overhead in your program, so we the want it to profiller at all run. To control it we can use macros.

Start the Logger with <code>ROTPROFILLERSTART(x)</code> passing a string for the filepath of the JSON file. End with the end of the scope or when <code>ROTPROFILLEREND</code> is called. You can use <code>ROTPROFILLERFUNCION</code> at the beggining of a function and it will use a funcion name as the identificatioan parameter, for specific scopes use <code>ROTPROFILERNAMED(x)</code> passing a string with a identification. They will end at the end of the scope.

To activate the Profiler, write  <code>#define ROTPROFILLERTOOL</code> before including the ROTProfiller.h. To deactivate, just remove and all the macros will resolve to nothing at compile time.


## --------- KNOWN ISSUES ---------

1. You can't use multiple instance of the <code>rot::EventLogger</code> if you use macros, only the instanciated by the macro itself.
