#include <stdio.h>
#include <stdlib.h>
#include <linux/gpio.h>
#include <fcntl.h>

#define EXIT_SUCCESS 0

int main(int argc, char *argv[]){
	int fd0 = open("/dev/gpiochip0",O_RDWR); // open file descriptor
	struct gpiochip_info cinfo;
	ioctl(fd0,GPIO_GET_CHIPINFO_IOCTL,&cinfo); // ioctl = IO control equest
	printf("GPIO chip 0: %s, \"%s\", %u lines\n",cinfo.name,cinfo.label,cinfo.lines);
	
	struct gpiohandle_request req; // Green and yellow
	struct gpiohandle_data data; // Data bit
	struct gpiohandle_request req_pb;
	struct gpiohandle_data data_pb;
	// outputs
	req.lines = 3; // 2 pins in this handler
	req.lineoffsets[0] = 4; // pin 4 - green
	req.lineoffsets[1] = 17; // pin 17 - yellow
	req.lineoffsets[2] = 27; //red
	req.flags = GPIOHANDLE_REQUEST_OUTPUT; // Declare as output
	// inputs
	req_pb.lines = 1;
	req_pb.lineoffsets[0] = 11; // GPIO 11 as input
	req_pb.flags = GPIOHANDLE_REQUEST_INPUT;
		
	data.values[0] = 1;   
	data.values[1] = 0; // set their initial values ,4=on, 17=off
	data.values[2] = 0;
	data_pb.values[0] = 0;
	ioctl(fd0,GPIO_GET_LINEHANDLE_IOCTL, &req); // Get the line handler
	ioctl(fd0,GPIO_GET_LINEHANDLE_IOCTL, &req_pb);

	while(1){
	int ret = ioctl(req_pb.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data_pb);
 	ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data); // output data bits
	usleep(500000); //sleep for 1 second
 	data.values[0] = !data.values[0]; // toggle
 	data.values[1] = !data.values[1];
	if(data_pb.values[0] == 1)
		data.values[2] = 1;
		printf("Button pushed");
	else
		data.values[2] = 0;
 	} //for
	close(req.fd); // release line
	close(fd0); // close the file
	exit(EXIT_SUCCESS);


}
