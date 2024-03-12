MOSQUITTO MQTT SETUP:
Installation mosquitto in terminal:
https://mosquitto.org/download/

sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa  

sudo apt-get install mosquitto 

sudo apt-get install mosquitto-clients
Configuration methods:
https://mosquitto.org/documentation/authentication-methods/

https://test.mosquitto.org/config/

The above sites has the config method to make the connection successfully.

My mosquitto.conf file:
 #Place your local configuration in /etc/mosquitto/conf.d/ 
 
 
 #A full description of the configuration file is at 

 #/usr/share/doc/mosquitto/examples/mosquitto.conf.example 

 persistence true 

 persistence_location /var/lib/mosquitto/ 

 log_dest file /var/log/mosquitto/mosquitto.log 

 include_dir /etc/mosquitto/conf.d  

 listener 1883          
 allow_anonymous true
After configuring the file:
sudo mosquitto -c /etc/mosquitto/mosquitto.conf  
Which is used to connected with the remote server (Mobile)

we need to give the mosquitto -c config with its < path > to make connection.

In another terminal we need to get subscribe with our topic by using,

mosquitto_sub -v -t "Topic_name"
It shows the value that our client sends by using the mobile.

https://stackoverflow.com/questions/26716279/how-to-test-the-mosquitto-server (Ref. for Testing the server which we get to connect now.)

open 3 terminal windows and each window should run these 3 different commands.

1:  sudo mosquitto -c /etc/mosquitto/mosquitto.conf

2:  mosquitto_sub -v -t "Topic_name" 

3:  sudo tail -f /var/log/mosquitto/mosquitto.log 
Checking the log whether the client is connected or not:
sudo tail -f /var/log/mosquitto/mosquitto.log 
To check the client connectivity.

Installing the MQTT Alert in Mobile:
https://play.google.com/store/apps/details?id=gigiosoft.MQTTAlert

(/images/img1.png)
(/images/img2.png)

Install MQTT Alert App in your mobile and set the MQTT Broker access by click Broker give configuration with connection name and Client ID.

The default allocated or manually change the connection name and Client ID, after give IP/Web Address and Port.

Then if you have to give security to the project assign username and password and give confirm (The message is show connection test ok! Your are ready to go!)

MQTT Alert configuration:

(/images/img3.png)
(/images/img4.png)

Click the plus symbol and give the MQTT Event name, Alert Tag and MQTT topic give payload value, Alert type (Analog), Comparision and Hysteresis (for graph)

Then give the alarm for obstacle detected, log to db (database) and click confirm.

Then click connect button to connect with IP Address and connection name (successfuly connected to the connection #1 MQTT Broker running on IP address)

Run the Alert Message:

(/images/img5.png)

Then click the button to check the alert message is receive from the MQTT Broker

Check the Database:

(/images/img6.png)
(/images/img7.png)

It show the obstacle detected in dd/mm/yy, time and distance - Alarm

Dashboard show the graph of obstacle detected with distance, date and time


