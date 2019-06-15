/*
 * Stopper.h
 *
 *  Created on: Oct 27, 2016
 *      Author: viki
 */

#ifndef WANDER_BOT_SRC_STOPPER_H_
#define WANDER_BOT_SRC_STOPPER_H_
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

class Stopper {
public:
    // Tunable parameters
    const static double FORWARD_SPEED = 0.3;
    const static double MIN_SCAN_ANGLE = -30.0/180*M_PI;
    const static double MAX_SCAN_ANGLE = +30.0/180*M_PI;
    const static double ANGULAR_SPEED = 45*2*3.1415926535897/360;

    Stopper();
    void startMoving();

private:
    ros::NodeHandle node;
    ros::Publisher commandPub; // Publisher to the robot's velocity command topic
    ros::Subscriber laserSub; // Subscriber to the robot's laser scan topic
    bool keepMoving; // Indicates whether the robot should continue moving
    double closest, farthest, angulo;
    int posicion_farthest, cantidad_angulos;
    double MIN_DIST_FROM_OBSTACLE = 0.8; // Should be smaller than sensor_msgs::LaserScan::range_max

    void moveForward();
    void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan);
    void girar();
};

#endif /* WANDER_BOT_SRC_STOPPER_H_ */
