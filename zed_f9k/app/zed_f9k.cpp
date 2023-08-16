#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>

class YourNode
{
public:
    YourNode() : nh("~")
    {
        // 订阅两个话题
        sub1 = nh.subscribe("/gps/fix", 10, &YourNode::callback1, this);
        sub2 = nh.subscribe("/gps/fix_velocity", 10, &YourNode::callback2, this);

        // 创建发布者
        pub = nh.advertise<std_msgs::Float32MultiArray>("/zed_f9k", 10);

        // 设置发布频率为10Hz
        rate = ros::Rate(10);
    }

    // 回调函数处理第一个话题
    void callback1(const sensor_msgs::NavSatFix::ConstPtr& msg)
    {
        // 处理 msg 数据
        // 在这里你可以使用 msg-> 字段获取 NavSatFix 的数据

        // 创建要发布的消息
        std_msgs::Float32MultiArray output_msg;

        // 填充消息数据，例如：
        output_msg.data.push_back(msg->latitude);
        output_msg.data.push_back(msg->longitude);
        output_msg.data.push_back(msg->altitude);

        // 发布处理后的数据
        pub.publish(output_msg);
    }

    // 回调函数处理第二个话题
    void callback2(const geometry_msgs::TwistWithCovarianceStamped::ConstPtr& msg)
    {
        // 处理 msg 数据
        // 在这里你可以使用 msg->twist.twist.linear.x 等字段获取 TwistWithCovarianceStamped 的数据

        // 创建要发布的消息
        std_msgs::Float32MultiArray output_msg;

        // 填充消息数据，例如：
        output_msg.data.push_back(msg->twist.twist.linear.x);
        output_msg.data.push_back(msg->twist.twist.linear.y);
        output_msg.data.push_back(msg->twist.twist.linear.z);

        // 发布处理后的数据
        pub.publish(output_msg);
    }

private:
    ros::NodeHandle nh;
    ros::Subscriber sub1, sub2;
    ros::Publisher pub;
    ros::Rate rate; // 发布频率控制器
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "your_node_name");
    YourNode node;
    
    while (ros::ok()) {
        // 在这里处理你的发布逻辑
        // 例如，在这里可以发布一些固定的数据，或者根据你的逻辑进行数据的处理和发布
        // ...

        // 等待，以控制发布频率
        ros::spinOnce();
        node.rate.sleep();
    }

    return 0;
}
