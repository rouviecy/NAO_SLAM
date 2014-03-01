// Aldebaran includes
#include <alproxies/alvideodeviceproxy.h>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>
#include <alerror/alerror.h>

// Opencv includes
#include <opencv2/core/core.hpp>

// Common includes
#include <iostream>
#include <string>

using namespace AL;

void recup_images(){
	ALVideoDeviceProxy camProxy("127.0.0.1", 9559);
	const std::string clientName = camProxy.subscribe("test", kQVGA, kBGRColorSpace, 30);
	cv::Mat img_brute = cv::Mat(cv::Size(320, 240), CV_8UC3);
	while ((char) cv::waitKey(30) != 27){
		ALValue img = camProxy.getImageRemote(clientName);
		img_brute.data = (uchar*) img[6].GetBinary();
		camProxy.releaseImage(clientName);
	}
	camProxy.unsubscribe(clientName);
}

int main(){
	try{
		recup_images;
	}catch (const AL::ALError& e){
		std::cerr << "Caught exception " << e.what() << std::endl;
	}

	return 0;
}

