# Accelerometer_ADXL345_Mobile_Band

This is a library of code samples to make a falling and drowning detection wearable band. The device is based on Teensy 3.2 and it's for people using in daily life. The core sensor is ADXL345, which is a high resolution 3-axis digital accelerometer. 

In this library you can find sample sketches for different part or modules you want to use, like button sketch or button written in interrupts sketch, and so on. Based on these sketches, you can switch moods of the mobile band to walking mood, swimming mood or any other moods you design. 

Besides, there is also a reset button. When there is a wrong detection, or the user can save himself/herself, like getting up after falling, the user can press the reset button and the alarm will be canceled. To make your device fancier, we can add a GPRS module inside, sending a specific text when there is an alarm. 

For the algorithm of dangerous detection, it's based on the 3-axis accelerometer. The accelerometer sensor can get accelerated speed on x, y, z three directions, the algorithm calculates the sum of squares of three directions. And when the sum is larger than 400.00, a inside timer interrupt starts and automatically ends in 1500ms. During the timer, there will be a counter to test how many times the sum is larger than 150.00, if the count is larger than 1 and smaller than 4, it means that the user has fallen, and if the count is another number out of that range, it means that the user is doing some strenuous exercises. The alarm will be trigger at the end of the timer. 

Contributing to this library is warmly welcomed. You can do this basically by [forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above for operating guide). Adding change log and your contact into file header is encouraged. Thanks for your contribution.
