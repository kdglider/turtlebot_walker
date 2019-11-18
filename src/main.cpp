/**
 * Copyright (c) 2019   Hao Da (Kevin) Dong
 * @file       main.cpp
 * @date       2019/11/16
 * @brief      Main file for the TurtleBot random walker
 * @license    This project is released under the BSD-3-Clause License. See full details in LICENSE.
 */

#include <walker.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "talker");

    // Record publishing rate input from user (Hz)
    int pubRate = atoi(argv[1]);

    // Log warnings or errors if the publishing rate is too fast or negative
    if (pubRate > 1000) {
        ROS_ERROR_STREAM("Publishing rate over 1000 Hz detected (WAY too fast)");
    } else if (pubRate > 100) {
        ROS_WARN_STREAM("Publishing rate over 100 Hz detected (may be too fast)");
    } else if (pubRate <= 0) {
        ROS_FATAL_STREAM("Negative publishing rate detected");
    }

    // Create node handle and publisher to publish to chatter topic
    ros::NodeHandle n;
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

    // Set publishing rate
    ros::Rate loop_rate(pubRate);

    // Counter to keep track of the number of published messages
    int count = 0;

    while (ros::ok()) {
        // Create String message to publish
        std_msgs::String msg;
        std::stringstream ss;

        // Update stringstream and String msg objects
        ss << serviceMsg << ", Count: " << count;
        msg.data = ss.str();

        // Print message string to terminal
        ROS_INFO_STREAM("Published by talker: [" << msg.data.c_str() << "]");

        // Publish message
        chatter_pub.publish(msg);

        // Broadcast talk transform
        tfbr.sendTransform(tf::StampedTransform(talk, ros::Time::now(), "world", "talk"));

        ros::spinOnce();

        // Pause the program until it is time to publish again
        loop_rate.sleep();
        count++;
    }

    return 0;
}
