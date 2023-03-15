# autonomous-mobile-robot

## Introduction
This project was done for my Masters disseration. The project aims to use ROS (Robot Operating System) for path finding in an unknown environment using low cost sensors such as kinect. The development and tests are done in a simulated world using Gazebo. The project compares different available path-finding and SLAM packages avaialble in ROS and their performace in different lightining scenario.  

This project was developed in ROS Noetic, therefore hasn't been tested for other ROS versions.

This project requires OpenCV 4.2 to be built from source with NON-FREE modules.

Find-Object2d and Vision_opencv should be built from source once opencv is installed.

## To run the project:

Step 1:
```
roslaunch mapping gazebo_robot_world.launch world:= <pass the world to run>
```

Step 2:

The project is configured to look for a Coke can model. This model can be found in the Gazebo Models.
Add the coke can in the scene, can be found in gazebo models.

Step 3:
```
roslaunch mapping rtab_and_exploration.launch
```

Step 4:
```
roslaunch recog_findobject.launch 
```

The findobject might need configuration as it wasn't tested on a fresh ubuntu installtion
