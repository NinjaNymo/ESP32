# ESP32/Servo

After tons of debugging, valuable data was found.

### ESP-IDF Stuff:
- The MCPWM timing does not depend on FreeRTOS tickrate. MCPWM actually runs on the same timer (well, u can choose) as FreeRTOS, not on a software timer provided by the OS.


### General Servo Stuff 
- It's the _pulse width [us]_ that controls the servo, not the _duty cycle [%]_ nor the _frequency [Hz]_.
- 50 Hz was made standard by old school RC guys.
- A servo needs to be calibrated without breaking it. I should make a program for that (for breaking it, that is).
- Different servos might have completely different pulse width requirements.

|Servo|Min PW|Max PW|
|-----|------|------|
|SG92R|500   |2300



