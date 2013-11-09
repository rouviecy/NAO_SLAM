NAO_SLAM
========

NAO_VISIO
---------

1. Requirements

    * >=cmake-2.8.3
    * python-2.7
    * qiBuild

http://www.aldebaran-robotics.com/documentation/dev/cpp/install_guide.html#cpp-install-guide

2. Setup

    * Create a worktree in an empty folder :  
      `qibuild init`  
      `qitoolchain create mytoolchain /path/to/cpp/sdk/toolchain.xml --default`  
    * Come back to this folder in order to compile :   
      `qibuild configure nao_visio`  
      `qibuild make nao_visio`  