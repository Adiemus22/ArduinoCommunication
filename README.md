This software is used to simplify microcontroller control.

The communication software consists of two parts: The arduino software and the windows software. The windows software is used to write commands and send them to the arduino. The arduino software analyses these commands, executes them and sends back a return sign (or a string).


How it works
-----------------

Once the communication between computer and arduino is setup, the command transfer can start. The commands are send one by one to the arduino. As soon as a command is executed, the arduino returns a char to signalise that is is ready for the next command.
The first character of a command determines the function that the arduino shall call. The last character of a function is the end character, telling the arduino that the command ends here. The characters in-between (optional) handle over some parameters to the arduino.
One in-built example is the wait function, which idles the arduino for a given timespan. A valid command would be:

			d500#

Here, 'd' means that the function 'delay' in the arduino code shall be called. The following characters ('5', '0', '0') declare the timespan (500 milliseconds). '#' determines the end of this command.
The arduino will now execute this function and be idle for 500 ms. After that, he will return a return end sign ('*') so the computer knows that the arduino has finished the command execution and sends the next command.
The computer software protocols the time of command sending and arrival of the return end sign of every command.



Getting started
-------------------

1. Preparation

1.1 Modify the arduino code (add functions)
1.2 Upload the arduino code
1.3 Save the .exe-file of the arduino to a path you can easily find



2. Working

2.1 Start the computer software
2.2 On the upper left combo box, check for available COM-Ports. Plug in arduino and click the "R"-button ("Refresh"). Check the combo box for new available COM-Ports. The new one is the arduino. Chose this one.
2.3 Click "Connect".
2.4 Type in commands into the right textbox. Use one line for every command. You do not have to write the '#' at the end, it will be sent automatically.

	If you want to repeat one or more lines several times, do the following:

		a. Write one line with the number of loops followe by a curly opening bracket
		b. Write the code to repeat in the following lines
		c. Write a line with one single closing curly bracket

		e.g.	4 {
			t500
			}

		This will send the command "t500#" 4 times. Is is equivalent to:

			t500
			t500
			t500
			t500

      Dots in commands are ignored.
      
2.5 Once you are happy with your commands, click "Start" to start the procedure.
2.6 In the end, please do not forget to click "Disconnect" to disconnect from the arduino.

In case there are problems, please send a single '%' as command to the arduino to reset the arduino by code.
	
