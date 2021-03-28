# R.O.B.
A 3DS homebrew program to display and log the 3DS' accelerometer and gyroscope data.
# Usage
Drop the app wherever on your SD card and enter the homebrew launcher through whatever means convenient to you, be it ninjhax or Luma CFW's Rosalina. Open the app and it'll do the rest. Logs are stored in CSV format at /3ds/data/ROB/Test_X.csv, where X is the number of logs (or times you've opened the app).

The entry format looks like this:

```Entry, Accel X, Y, Z, Gyro Yaw, Pitch, Roll```

Where Entry is the iteration of the log, and all other values all self explanatory.

ROB will also display these values on the screen in real time.
# Building
R.O.B. requires the latest devkitARM, libctru, and citro3d (the latter two should have come with devkitARM). Type ``make`` in the project directory and you should see ROB.3dsx magically pop out.
# Credits
Smealum, fincs, mtheall, yellows8 and co.- libctru and all the amazing work in reverse engineering the 3DS

fincs- Citro3D and *lots* of help with using it. I can't thank this guy in particular enough.

Henke37#6119 on Discord- Commissioning this program to be created.

R.O.Bs are not a dying race.
