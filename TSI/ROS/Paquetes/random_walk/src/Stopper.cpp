/*
 * Stopper.cpp
 *
 *  Created on: Oct 27, 2016
 *      Author: viki
 */

#include "Stopper.h"
#include "geometry_msgs/Twist.h"
#include <iostream>

Stopper::Stopper()
{
    // Coger el parámetro del fichero launch
    if (node.hasParam("MIN_DIST_FROM_OBSTACLE")){
		node.getParam("MIN_DIST_FROM_OBSTACLE", MIN_DIST_FROM_OBSTACLE);
		if (MIN_DIST_FROM_OBSTACLE < 0)
			MIN_DIST_FROM_OBSTACLE = 0.8;
	}

    closest = 9999.0;
    farthest = 0.0;
    keepMoving = true;

    // Advertise a new publisher for the robot's velocity command topic
    commandPub = node.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 10);

    // Subscribe to the simulated robot's laser scan topic
    laserSub = node.subscribe("scan", 1, &Stopper::scanCallback, this);
}

// Send a velocity command
void Stopper::moveForward() {
    geometry_msgs::Twist msg; // The default constructor will set all commands to 0
    msg.linear.x = FORWARD_SPEED;
    commandPub.publish(msg);
}

// Process the incoming laser scan message
void Stopper::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    // Find the closest range between the defined minimum and maximum angles
    int minIndex = ceil((MIN_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);
    int maxIndex = floor((MAX_SCAN_ANGLE - scan->angle_min) / scan->angle_increment);
    cantidad_angulos = maxIndex - minIndex;
    angulo = scan->angle_increment;
    closest = 9999.0;
    farthest = 0.0;

    posicion_farthest = minIndex;

    for (int currIndex = minIndex + 1; currIndex <= maxIndex; currIndex++) {
        if (scan->ranges[currIndex] <= closest) {
            closest = scan->ranges[currIndex];
            //std::cout << "CLOSEST: scan->ranges[currIndex] " << scan->ranges[currIndex] << " closest " << closest << " currIndex " << currIndex << std::endl;
        }
        if(scan->ranges[currIndex] < 10){
            if(scan->ranges[currIndex] >= farthest){
                farthest = scan->ranges[currIndex];
                posicion_farthest = currIndex;
                //std::cout << "FARTHEST: scan->ranges[currIndex] " << scan->ranges[currIndex] << " farthest " << farthest << " currIndex " << currIndex << std::endl;
            }
        } else {
            farthest = scan->ranges[currIndex];
            posicion_farthest = currIndex;
        }
    }
}

void Stopper::girar(){
    ros::Rate rate(10);
    geometry_msgs::Twist msg;
    msg.linear.x = 0;
    if(posicion_farthest <= cantidad_angulos/2)
        msg.angular.z = -ANGULAR_SPEED;
    else
        msg.angular.z = ANGULAR_SPEED;
    ros::Time start2 = ros::Time::now();
    while(ros::Time::now() - start2 < ros::Duration((posicion_farthest*angulo)/45.0)){
      commandPub.publish(msg);
      ros::spinOnce();
      rate.sleep();
    }
}

void Stopper::startMoving()
{
    ros::Rate rate(10);
    ROS_INFO("Start moving");

    // Keep spinning loop until user presses Ctrl+C or the robot got too close to an obstacle
    while (ros::ok()) {
        if (closest < MIN_DIST_FROM_OBSTACLE) {
            girar();
        } else {
            moveForward();
        }
        ros::spinOnce(); // Need to call this function often to allow ROS to process incoming messages
        rate.sleep();
    }
}
