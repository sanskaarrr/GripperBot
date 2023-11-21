# GripperBot
This is a Gripper Bot which is used for the movement of payload from point A to B.
It has 4 DC motors for movement comtrolled by a Motor Driver L298 which is connected to a NodeMCU(ESP8266), a Wi-Fi enabled microcontroller for the processing and working of the bot.
The main feature of this bot is its capability to Grip/Hold Payload which has to be moved.For this a Servo-Motor(MG90S 9g) is attach to a Gripper mechanism which can be opened and be closed by commands.
We are controlling this Bot through joysticks and the output of the joysticks are analog and since NodeMCU has only one analog pin so we have used Ardiuno UNO for processing of commands
But the problem was Arduino UNO R3 was not Wifi enabled so we used Arduino for proceesing then we send the output/commands to another NodeMCU through Serial Communication.
Then we connected both the NodeMCU using client server method.
