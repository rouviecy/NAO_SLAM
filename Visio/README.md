NAO_SLAM
========

Computer Vision (by Cyril)
--------------------------

1. Demo :  
Launch nao_grab_cam.py in SSH session ; NAO will track and follow red objects (JOGs, other NAOs, tomatoes, ...)

2. Image processing :  
Folder "processing" contains OOP code to track blobs after HSV segmentation.  
Run `make` to compile, and `./naqahdah` to execute. Be sure you have already installed OpenCV !  
Parameters are chosen and images are displayed in a GUI. It will use your camera `/dev/video0`. You can choose :  
    * Hue (minimum and maximum)
    * Saturation (minimum and maximum)
    * Brightness (minimum and maximum)
    * Area of blobs (minimum)  
Hold 'c' key pressed while you are changing these values to avoid the mouse from being caught !  
Tape 'q' key to quit.