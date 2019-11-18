/**
 * Copyright (c) 2019   Hao Da (Kevin) Dong
 * @file       walker.h
 * @date       2019/11/16
 * @brief      Declarations for the Walker class
 * @license    This project is released under the BSD-3-Clause License. See full details in LICENSE.
 */

#include <chrono>
#include <sstream>
#include <cmath>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

/**
 * @brief printString service callback function that returns a sentence with the name given in the request
 * @param req Service request
 * @param res Service response
 * @return None
 */
class Walker {
    public:
        ros::NodeHandle nh;

        // Subscriber for 2D LIDAR scan
        ros::Subscriber laser_sub = nh.subscribe("scan", 10, &Walker::laserCallback, this);

        // Publisher for mobile base velocity
        ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 1);

        //Robot velocity message to be published
        geometry_msgs::Twist robotVelocity;

        // Default linear and turn speeds
        double defaultLinearSpeed = 0.15;      // m/s
	    double defaultAngularSpeed = 0.5;     // rad/s

        // LIDAR distance within which the robot will execute a random turn
        double safeDistance = 1;        // m

        Walker();

        void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg);

        void randomTurn();
    
};