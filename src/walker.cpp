/**
 * Copyright (c) 2019   Hao Da (Kevin) Dong
 * @file       walker.cpp
 * @date       2019/11/16
 * @brief      Implementations for the Walker class
 * @license    This project is released under the BSD-3-Clause License. See full details in LICENSE.
 */

#include <walker.h>

Walker::Walker() {
    robotVelocity.linear.x = defaultLinearSpeed;
	robotVelocity.angular.z = 0;

    vel_pub.publish(robotVelocity);
}

void Walker::laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg) {
    // Number of array elements in laser field of view
    int laserSize = (msg->angle_max - msg->angle_min)/msg->angle_increment;

    //Check LIDAR array for any readings below safeDistance
    for(int i = 1 ; i < laserSize ; i++) {
        // Reject corrupt readings
        if (std::isnan(msg->ranges[i]) == false) {
            if (msg->ranges[i] < safeDistance) {
                randomTurn();
                break;
            }
        }
    }

    // If no obstacle is closer than safeDistance, continue to move forward
    vel_pub.publish(robotVelocity);
}


void Walker::randomTurn() {	
    // Create and start a timer
	std::chrono::time_point<std::chrono::system_clock> start;
	start = std::chrono::system_clock::now();
    uint64_t secondsElapsed = 0;

    // Random time (between 1-5 seconds) to turn for
    int randomSeconds = rand() % 5 + 1;
    
    // Change velcity profile to turning
    robotVelocity.linear.x = 0;
	robotVelocity.angular.z = defaultAngularSpeed;

    // Keep turning until the random time is reached
	while (secondsElapsed <= randomSeconds) {
		vel_pub.publish(robotVelocity);
		//ros::spinOnce();
		secondsElapsed = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now()-start).count();
	}

    // Change velocity profile back to moving forward
    robotVelocity.linear.x = defaultLinearSpeed;
	robotVelocity.angular.z = 0;
    vel_pub.publish(robotVelocity);
	//ros::spinOnce();
}

