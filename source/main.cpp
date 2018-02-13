#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <sys/stat.h>

void sceneInit();
void renderText(float x, float y, float scaleX, float scaleY, bool baseline, const char* text);
void setTextColor(u32 color);
void startframe();
void endframe();
void drawon(gfxScreen_t screen);
void sceneExit();

using namespace std;

void _mkdir(const char *dir) { //http://nion.modprobe.de/blog/archives/357-Recursive-directory-creation.html
        char tmp[256];
        char *p = NULL;
        size_t len;

        snprintf(tmp, sizeof(tmp),"%s",dir);
        len = strlen(tmp);
        if(tmp[len - 1] == '/')
                tmp[len - 1] = 0;
        for(p = tmp + 1; *p; p++)
                if(*p == '/') {
                        *p = 0;
                        mkdir(tmp, S_IRWXU);
                        *p = '/';
                }
        mkdir(tmp, S_IRWXU);
}

inline bool pathExist(const string filename){
    struct stat buffer;
    return (stat (filename.c_str(),& buffer)==0);
}

int main(int argc, char **argv)
{
	sceneInit();
	
	accelVector accelerometer, oldAccelerometer;
	angularRate gyro, oldGyro;
	oldAccelerometer.x = 0; oldAccelerometer.y = 0; oldAccelerometer.z = 0;
	oldGyro.x = 0; oldGyro.y = 0; oldGyro.z = 0;
	HIDUSER_EnableAccelerometer();
	HIDUSER_EnableGyroscope();
	aptSetSleepAllowed(false);
	setTextColor(0xFF000000); //Black

	int entry = 1;

	string filedir = "/3ds/data/ROB/";
	int i = 1;
	if(!pathExist(filedir.c_str())) _mkdir(filedir.c_str());
	while(pathExist((filedir + "Test_" + to_string(i) + ".csv").c_str())) i++;
	ofstream out(filedir + "Test_" + to_string(i) + ".csv");
	out << "Entry, Accel X, Y, Z, Gyro Yaw, Pitch, Roll" << endl;

	// Main loop
	while (aptMainLoop())
	{
		startframe();
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		hidAccelRead(&accelerometer);
		hidGyroRead(&gyro);
		

		if (kDown & KEY_START) break; // break in order to return to hbmenu

		//Do the keys printing only if keys have changed
		if (accelerometer.x != oldAccelerometer.x || accelerometer.y != oldAccelerometer.y || accelerometer.z != oldAccelerometer.z || \
			gyro.x != oldGyro.x || gyro.y != oldGyro.y || gyro.z != oldGyro.z)
		{
			drawon(GFX_TOP);
			renderText(0, 00, 1, 1, false, "Accelerometer");
			renderText(0, 25, 1, 1, false, ("X: " + to_string(accelerometer.x)).c_str());
			renderText(0, 50, 1, 1, false, ("Y: " + to_string(accelerometer.y)).c_str());
			renderText(0, 75, 1, 1, false, ("Z: " + to_string(accelerometer.z)).c_str());
			renderText(0, 100, 1, 1, false, "Gyroscope");
			renderText(0, 125, 1, 1, false, ("Yaw:   " + to_string(gyro.z)).c_str());
			renderText(0, 150, 1, 1, false, ("Pitch: " + to_string(gyro.y)).c_str());
			renderText(0, 175, 1, 1, false, ("Roll:  " + to_string(gyro.x)).c_str());
			drawon(GFX_BOTTOM);
			renderText(0, 0, 0.7, 0.7, false, "ROB: A program to display and log\naccelerometer and gyroscope data.\nPress start to exit.\nLogging will continue when the\nscreen is closed.");
			out << entry++ << ',';
			out << to_string(accelerometer.x) << ',' << to_string(accelerometer.y) << ',' << to_string(accelerometer.z) << ',';
			out << to_string(gyro.z) << ',' << to_string(gyro.y) << ',' << to_string(gyro.x) << endl;
		}

		//Set keys old values for the next frame
		oldAccelerometer = accelerometer;
		oldGyro = gyro;
		endframe();
	}
	out.close();

	// Exit services
	gfxExit();

	return 0;
}
