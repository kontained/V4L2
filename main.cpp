#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

using namespace std;

/*
This function gets and prints
the capabilities of the
video device
*/
void GetCapabilites(int fd, int request, struct v4l2_capability &arg)
{
	if (ioctl(fd, request, &arg) == -1)
		cout << "Error getting device capabilities." << endl;	

	//basic info about the camera

	cout << "\n---------- Device information -----------" << endl;
	cout << "Driver: " << arg.driver << endl;
	cout << "Card: " << arg.card << endl;
	cout << "Bus: "  << arg.bus_info << endl;
	cout << "Version: " << arg.version << endl;
	cout << "-----------------------------------------" << endl;

	//specific capabilites of the camera
	cout << "\n---------- Camera capabilities ----------" << endl;

	if (arg.capabilities & V4L2_CAP_VIDEO_CAPTURE)
		cout << "Single Plane API video capture" << endl;

	if (arg.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE)
		cout << "Multi Plane API video capture" << endl;

	cout << "-----------------------------------------" << endl << endl;
}

int main()
{
	struct v4l2_capability vCap;
	int index, fd;

	/*
	Open video device
	*/
	if ((fd = open("/dev/video0", O_RDONLY)) == -1)
		cout << "Cannot open video device." << endl;
	else
		cout << "Device opened! FD: " << fd <<  endl;

	/*
	Set the capability struct to 0
	then get the capabilities
	*/
	memset(&vCap, 0, sizeof(vCap));

	GetCapabilites(fd, VIDIOC_QUERYCAP, vCap);

	/*
	Close video device
	*/
	if (close(fd) == 0)
		cout << "Device closed! FD: " << fd << endl;

	return 0;
}
